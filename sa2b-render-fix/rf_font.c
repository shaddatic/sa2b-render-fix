/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/memutil.h>   /* WriteRetn                                            */
#include <sa2b/memory.h>    /* MemFree, mAlloc, mCalloc                             */
#include <sa2b/file.h>      /* uFileLoad                                            */

/****** Mod Loader ******************************************************************/
#include <sa2b/modloader.h>     /* ML_GetReplaceablePath                            */

/****** System **********************************************************************/
#include <sa2b/shinobi/sg_maloc.h>  /* syFree                                       */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* RF_ConfigGet                                     */

/****** Self ************************************************************************/
#include <rf_font.h>           /* self                                              */

/************************/
/*  Constants           */
/************************/
/****** Symbol Count *****************************************************************/
#define KANJI_SYM_COUNT     (3423)
#define ASCIIS_SYM_COUNT    ( 224)
#define ASCIIE_SYM_COUNT    (  96)

/****** File Sizes ******************************************************************/
#define KANJI_32_SIZE       ((24*(24*sizeof(u32)))*KANJI_SYM_COUNT)  /* 7'886'592   */
#define KANJI_01_SIZE       ((24*(24/8))          *KANJI_SYM_COUNT)  /*   246'456   */
#define ASCII_32_SIZE       ((24*(24*sizeof(u32)))*ASCIIS_SYM_COUNT) /*   516'096   */
#define ASCII_S1_SIZE       ((24*(24/8))          *ASCIIS_SYM_COUNT) /*    16'128   */
#define ASCII_E1_SIZE       ((24*(24/8))          *ASCIIE_SYM_COUNT) /*     6'912   */

/****** Buffer Sizes ****************************************************************/
#define KANJI_BUF_SIZE      (KANJI_32_SIZE)
#define ASCII_BUF_SIZE      (ASCII_32_SIZE)

/************************/
/*  Types               */
/************************/
typedef enum
{
    FONT_FILE_KANJI,    /* Japanese font                                            */
    FONT_FILE_ASCII_S,  /* international font                                       */
    FONT_FILE_ASCII_E,  /* Japanese ASCII font                                      */

    NB_FONT_FILE,       /* count                                                    */
}
eFONT_FILE;

typedef union
{
    struct {
        uint8_t r, g, b, a;
    };
    uint32_t col;
}
FONT_COLOR;

typedef struct
{
    FONT_COLOR p[24][24];   /* fonts are 24x24, 32bit RGBA                          */
}
FONT_CHAR;

typedef struct
{
    uint8_t p[24][3];       /* SADX fonts are 24x24, 1bit alpha                     */
}
FONT_1_CHAR;

typedef struct
{
    uint8_t*    pLeft;  /* left padding                                             */
    FONT_CHAR*  pBuff;  /* pixel buffer                                             */
    eFONT_FILE   type;  /* font type                                                */
}
FONT_ASCII;

typedef struct
{
    uint8_t*    pLeft;      /* left padding                                         */
    FONT_CHAR*  pBuff;      /* pixel buffer                                         */
    eFONT_FILE  type;       /* font type                                            */
    uint8_t     sjis_shift; /* Shift-JIS stuff                                      */
    uint8_t     sjis_limit; /* ^                                                    */
}
FONT_KANJI;

typedef struct
{
    int        offset;  /* always 0, no idea what it's for                          */
    FONT_ASCII Ascii;   /* ASCII font                                               */
    FONT_KANJI Kanji;   /* Kanji font                                               */
}
FONT_LANGUAGE;

typedef struct
{
    const char*  name;
    FONT_CHAR*  pBuff;
    uint8_t*    pLeft;
}
FONT_CHAO;

typedef struct rfs_font
{
    uint8_t*      pLeft;   /* left padding                                          */
    FONT_CHAR*    pBuff;   /* pixel buffer                                          */
    RFE_FONT_TYPE type;   /* font type                                             */
}
RFS_FONT;

/************************/
/*  External Variables  */
/************************/
#define FontBuffers         DataAry(FONT_LANGUAGE, 0x00B5D658, [NB_FONT_LANG])
#define FontChBuffers       DataAry(FONT_CHAO    , 0x012E9BC4, [NB_FONT_TYPE])

#define ga_InputWay         DataAry(int32_t      , 0x0174B5FC, [4]           )

/************************/
/*  File Variables      */
/************************/
static const size_t LeftSizes[NB_FONT_TYPE] = { KANJI_SYM_COUNT, ASCIIS_SYM_COUNT };

static const size_t SpaceWidths[NB_CNFE_FONT_SPACE]  = { 0, 6, 9, 12, 24 };

static int FontPadding;
static int SpacePadding;

/************************/
/*  Source              */
/************************/
static uint8_t*
CalculateFontLeft(FONT_CHAR* pFont, RFE_FONT_TYPE type)
{
    const size_t left_size = LeftSizes[type];

    uint8_t* const leftp = mCalloc(uint8_t, left_size);

    leftp[0] = SpacePadding; // Spacing

    for (size_t i = 1; i < left_size; ++i)
    {
        int left_new = 0;

        FONT_CHAR* const p = &pFont[i];

        /** Iterate through every pixel to find the most
            right, non-empty pixel **/
        for (int y = 0; y < 24; ++y)
        {
            for (int x = 0; x < 24; ++x)
            {
                if (left_new < x && p->p[y][x].a)
                    left_new = x;
            }
        }

        /** Only add padding if the left value is non-zero **/
        leftp[i] = (uint8_t)(left_new ? (left_new + FontPadding) : 0);
    }

    return leftp;
}

static FONT_CHAR*
___Font1ToFont32(FONT_1_CHAR* pBuff, const int nbChar, size_t szBuf)
{
    FONT_CHAR* const charp = MemCalloc(szBuf, 1);

    for (int i = 0; i < nbChar; ++i)
    {
        for (int y = 0; y < 24; ++y)
        {
            /** This is awful, but making it a loop would only make it more confusing.
                Converts 1 bit alpha to 32bit RGBA **/
            charp[i].p[y][ 0].col = (pBuff[i].p[y][0] & 0b00000001) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 1].col = (pBuff[i].p[y][0] & 0b00000010) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 2].col = (pBuff[i].p[y][0] & 0b00000100) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 3].col = (pBuff[i].p[y][0] & 0b00001000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 4].col = (pBuff[i].p[y][0] & 0b00010000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 5].col = (pBuff[i].p[y][0] & 0b00100000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 6].col = (pBuff[i].p[y][0] & 0b01000000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 7].col = (pBuff[i].p[y][0] & 0b10000000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 8].col = (pBuff[i].p[y][1] & 0b00000001) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][ 9].col = (pBuff[i].p[y][1] & 0b00000010) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][10].col = (pBuff[i].p[y][1] & 0b00000100) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][11].col = (pBuff[i].p[y][1] & 0b00001000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][12].col = (pBuff[i].p[y][1] & 0b00010000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][13].col = (pBuff[i].p[y][1] & 0b00100000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][14].col = (pBuff[i].p[y][1] & 0b01000000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][15].col = (pBuff[i].p[y][1] & 0b10000000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][16].col = (pBuff[i].p[y][2] & 0b00000001) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][17].col = (pBuff[i].p[y][2] & 0b00000010) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][18].col = (pBuff[i].p[y][2] & 0b00000100) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][19].col = (pBuff[i].p[y][2] & 0b00001000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][20].col = (pBuff[i].p[y][2] & 0b00010000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][21].col = (pBuff[i].p[y][2] & 0b00100000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][22].col = (pBuff[i].p[y][2] & 0b01000000) ? 0xFFFFFFFF : 0x00FFFFFF;
            charp[i].p[y][23].col = (pBuff[i].p[y][2] & 0b10000000) ? 0xFFFFFFFF : 0x00FFFFFF;
        }
    }

    /** Free original SADX buffer **/
    MemFree(pBuff);

    return charp;
}

static FONT_CHAR*
Font1ToFont32_K(FONT_1_CHAR* pBuff)
{
    return ___Font1ToFont32(pBuff, KANJI_SYM_COUNT, KANJI_BUF_SIZE);
}

static FONT_CHAR*
Font1ToFont32_E(FONT_1_CHAR* pBuff)
{
    return ___Font1ToFont32(pBuff, ASCIIE_SYM_COUNT, ASCII_BUF_SIZE);
}

static FONT_CHAR*
Font1ToFont32_S(FONT_1_CHAR* pBuff)
{
    return ___Font1ToFont32(pBuff, ASCIIS_SYM_COUNT, ASCII_BUF_SIZE);
}

RFS_FONT*
RF_FontLoadFile(const utf8* fpath, RFE_FONT_FTYPE ftype)
{
    size_t fsize;
    void* const file = uFileLoad(fpath, &fsize);

    if (!file)
    {
        OutputString("Render Fix: Font file not found, aborting load!");
        return nullptr;
    }

    RFE_FONT_TYPE font_rf_type;

    FONT_CHAR* charp;

    switch (ftype) {
    case FONT_FTYPE_RGBA_KANJI:

        if (fsize < KANJI_32_SIZE)
        {
            OutputString("Render Fix: Kanji RGBA font file is too small, aborting load!");
            MemFree(file);
            return nullptr;
        }

        charp = file;

        font_rf_type = FONT_TYPE_KANJI;
        break; 

    case FONT_FTYPE_RGBA_ASCII:

        if (fsize < ASCII_32_SIZE)
        {
            OutputString("Render Fix: ASCII RGBA font file is too small, aborting load!");
            MemFree(file);
            return nullptr;
        }

        charp = file; // No conversion needed

        font_rf_type = FONT_TYPE_ASCII;
        break;

    case FONT_FTYPE_1BPP_KANJI:

        if (fsize < KANJI_01_SIZE)
        {
            OutputString("Render Fix: Kanji SADX font file is too small, aborting load!");
            MemFree(file);
            return nullptr;
        }

        charp = Font1ToFont32_K(file);

        font_rf_type = FONT_TYPE_KANJI;
        break;

    case FONT_FTYPE_1BPP_ASCII:

        if (fsize >= ASCII_S1_SIZE)         // International
        {
            charp = Font1ToFont32_S(file);
        }
        else if (fsize >= ASCII_E1_SIZE)    // Japanese
        {
            charp = Font1ToFont32_E(file);
        }
        else
        {
            OutputString("Render Fix: ASCII SADX font file is too small, aborting load!");
            MemFree(file);
            return nullptr;
        }

        font_rf_type = FONT_TYPE_ASCII;
        break;

    default: // Incorrect type
        OutputString("Render Fix: Incorrect font type, aborting load!");
        MemFree(file);
        return nullptr;
    }

    RFS_FONT* const fontp = mAlloc(RFS_FONT, 1);

    fontp->pBuff = charp;
    fontp->pLeft = CalculateFontLeft(charp, font_rf_type);
    fontp->type = font_rf_type;

    return fontp;
}

void
RF_FontSetLeft(RFS_FONT* pFont, uint8_t* pLeft)
{
    if (!pFont || pLeft)
        return;

    if (pFont->pLeft)
        MemFree(pFont->pLeft);

    pFont->pLeft = pLeft;
}

void
RF_FontSetSpace(RFS_FONT* pFont, size_t szSpace)
{
    if (!pFont)
        return;

    pFont->pLeft[0] = (uint8_t)szSpace;
}

void
RF_FontHalfSpace(RFS_FONT* pFont)
{
    if (!pFont)
        return;

    const f64 flt = (f64)pFont->pLeft[0];

    pFont->pLeft[0] = (u8)(flt * 0.5);
}

void
RF_FontSetWhiteWithColor(FONT_CHAR* pChar, size_t szFile)
{
    const size_t nb_char = (szFile/4)/(24*24);

    for (size_t i = 0; i < nb_char; ++i)
    {
        bool has_color = false;

        OutputInt(i);

        for (int y = 0; y < 24 && !has_color; ++y)
        {
            for (int x = 0; x < 24 && !has_color; ++x)
            {
                if (pChar[i].p[y][x].r != pChar[i].p[y][x].g &&
                    pChar[i].p[y][x].g != pChar[i].p[y][x].b &&
                    pChar[i].p[y][x].b != pChar[i].p[y][x].a)
                {
                    has_color = true;
                }
            }
        }

        if (has_color)
            continue;

        for (int y = 0; y < 24 && !has_color; ++y)
        {
            for (int x = 0; x < 24 && !has_color; ++x)
            {
                pChar[i].p[y][x].col |= 0x00FFFFFF;
            }
        }
    }
}

static RFS_FONT* CurrentFonts[NB_FONT_LANG][NB_FONT_TYPE];

void
RF_FontReplace(RFE_FONT_LANG language, RFE_FONT_TYPE type, RFS_FONT* pFont)
{
    if (!pFont || type != pFont->type)
        return;

    if (type == FONT_TYPE_KANJI)
    {
        FontBuffers[language].Kanji.pBuff = pFont->pBuff;
        FontBuffers[language].Kanji.pLeft = pFont->pLeft;

        CurrentFonts[language][FONT_TYPE_KANJI] = pFont;
    }
    else // FONT_TYPE_ASCII
    {
        FontBuffers[language].Ascii.pBuff = pFont->pBuff;
        FontBuffers[language].Ascii.pLeft = pFont->pLeft;

        CurrentFonts[language][FONT_TYPE_ASCII] = pFont;
    }
}

RFS_FONT*
RF_FontGet(RFE_FONT_LANG language, RFE_FONT_TYPE type)
{
    return CurrentFonts[language][type];
}

static RFS_FONT* CurrentChaoFonts[NB_FONT_TYPE];

void
RF_FontChaoReplace(RFE_FONT_TYPE type, RFS_FONT* pFont)
{
    if (!pFont || type != pFont->type)
        return;

    if (type == FONT_TYPE_KANJI)
    {
        FontChBuffers[FONT_FILE_KANJI].pBuff = pFont->pBuff;
        FontChBuffers[FONT_FILE_KANJI].pLeft = pFont->pLeft;

        CurrentChaoFonts[FONT_TYPE_KANJI] = pFont;
    }
    else // FONT_TYPE_ASCII
    {
        FontChBuffers[FONT_FILE_ASCII_S].pBuff = pFont->pBuff;
        FontChBuffers[FONT_FILE_ASCII_S].pLeft = pFont->pLeft;

        FontChBuffers[FONT_FILE_ASCII_E].pBuff = pFont->pBuff;
        FontChBuffers[FONT_FILE_ASCII_E].pLeft = pFont->pLeft;

        CurrentChaoFonts[FONT_TYPE_ASCII] = pFont;
    }
}

RFS_FONT*
RF_FontChaoGet(RFE_FONT_TYPE type)
{
    return CurrentChaoFonts[type];
}

static RFS_FONT*
LoadReplaceableFont(const utf8* fpath, RFE_FONT_FTYPE ftype)
{
    return RF_FontLoadFile(ML_GetReplaceablePath(fpath), ftype);
}

static RFS_FONT*
LoadLocalFont(const utf8* fname, RFE_FONT_FTYPE ftype)
{
    char buf[260];

    snprintf(buf, sizeof(buf), "./%s/font/%s", GetModPath(), fname);

    OutputString(buf);

    return RF_FontLoadFile(buf, ftype);
}

void
RF_FontInit(void)
{
    WriteRetn(0x006B6130); // FontInit
    WriteRetn(0x006B62C0); // FontFree

    WriteRetn(0x00543AA0); // AL_MsgFontCreate
    WriteRetn(0x00543AF0); // AL_MsgFontFree

    syFree(FontBuffers[FONT_LANG_JAP].Ascii.pBuff); // ASCII24E
    syFree(FontBuffers[FONT_LANG_JAP].Kanji.pBuff); // KANJI24
    syFree(FontBuffers[FONT_LANG_ENG].Ascii.pBuff); // ASCII24S

    /****** Load Settings ******/
    /** Character width **/
    FontPadding = RF_ConfigGetInt(CNF_FONT_WIDTH);

    /** Space width **/
    SpacePadding = SpaceWidths[ RF_ConfigGetInt(CNF_FONT_SPACE) ];

    /****** Load Fonts ******/
    RFS_FONT* p_kanji;      // Japanese Font
    RFS_FONT* p_ascii;      // Latin Font
    RFS_FONT* p_ascii_j;    // Japanese ASCII font

    const int font_opt_kanji = RF_ConfigGetInt(CNF_FONT_KANJI);
    const int font_opt_ascii = RF_ConfigGetInt(CNF_FONT_ASCII);

    switch (font_opt_kanji) {
    case CNFE_FONT_KANJI_VANILLA: default:
        /** Load the vanilla font, or custom font if it's been replaced **/
        p_kanji = LoadReplaceableFont("./resource/gd_PC/EFMSGFONT_KANJI24.BIN", FONT_FTYPE_RGBA_KANJI);
        break;
    case CNFE_FONT_KANJI_CLASSIC:
        /** Load the local SA2 font file **/
        p_kanji = LoadLocalFont("EFMSGFONT_KANJI24.BIN", FONT_FTYPE_1BPP_KANJI);
        break;
    }

    switch (font_opt_ascii) {
    case CNFE_FONT_ASCII_VANILLA: default:
        /** Load the vanilla font, or custom font if it's been replaced **/
        p_ascii   = LoadReplaceableFont("./resource/gd_PC/EFMSGFONT_ASCII24S.BIN", FONT_FTYPE_RGBA_ASCII);
        p_ascii_j = LoadReplaceableFont("./resource/gd_PC/EFMSGFONT_ASCII24E.BIN", FONT_FTYPE_RGBA_ASCII);
        break;
    case CNFE_FONT_ASCII_IMPRESS:
        /** Load the local SA2 font file (Impress) **/
        p_ascii   = LoadLocalFont("EFMSGFONT_ASCII24_IP.BIN"  , FONT_FTYPE_1BPP_ASCII);
        p_ascii_j = LoadLocalFont("EFMSGFONT_ASCII24_J_IP.BIN", FONT_FTYPE_1BPP_ASCII);
        break;
    case CNFE_FONT_ASCII_COMICSANS:
        /** Load the local SA2 font file (Comic Sans) **/
        p_ascii   = LoadLocalFont("EFMSGFONT_ASCII24_CS.BIN"  , FONT_FTYPE_1BPP_ASCII);
        p_ascii_j = LoadLocalFont("EFMSGFONT_ASCII24_J_CS.BIN", FONT_FTYPE_1BPP_ASCII);
        break;
    }

    /** Spacing is half for JAP ASCII **/
    RF_FontHalfSpace(p_ascii_j);

    /** Set default fonts **/
    RF_FontReplace(FONT_LANG_JAP, FONT_TYPE_ASCII, p_ascii_j);  // Japanese // vv ASCII24E vv
    RF_FontReplace(FONT_LANG_JAP, FONT_TYPE_KANJI, p_kanji);
    RF_FontReplace(FONT_LANG_ENG, FONT_TYPE_ASCII, p_ascii);    // English  // vv ASCII24S vv
    RF_FontReplace(FONT_LANG_ENG, FONT_TYPE_KANJI, p_kanji);
    RF_FontReplace(FONT_LANG_GER, FONT_TYPE_ASCII, p_ascii);    // German
    RF_FontReplace(FONT_LANG_GER, FONT_TYPE_KANJI, p_kanji);
    RF_FontReplace(FONT_LANG_FRE, FONT_TYPE_ASCII, p_ascii);    // French
    RF_FontReplace(FONT_LANG_FRE, FONT_TYPE_KANJI, p_kanji);
    RF_FontReplace(FONT_LANG_SPA, FONT_TYPE_ASCII, p_ascii);    // Spanish
    RF_FontReplace(FONT_LANG_SPA, FONT_TYPE_KANJI, p_kanji);
    RF_FontReplace(FONT_LANG_ITA, FONT_TYPE_ASCII, p_ascii);    // Italian
    RF_FontReplace(FONT_LANG_ITA, FONT_TYPE_KANJI, p_kanji);

    /** Set Chao fonts **/
    RF_FontChaoReplace(FONT_TYPE_KANJI, p_kanji);
    RF_FontChaoReplace(FONT_TYPE_ASCII, p_ascii);

    /** Disable keyboard messages **/
    if (RF_ConfigGetInt(CNF_FONT_NOKEY))
    {
        ga_InputWay[0] = 1;
        ga_InputWay[1] = 1;
        ga_InputWay[2] = 1;
        ga_InputWay[3] = 1;
    }
}
