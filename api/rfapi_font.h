/*
*   SA2 Render Fix - '/rfapi_font.h'
*
*   Description:
*     The 'Font' API module is for loading and modifying the in-game text fonts.
* 
*   Version History:
*     - v1.3.0.0        : Version 0, initial release
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_FONT
#define H_RFAPI_FONT

/********************************/
/*  Opaque Types                */
/********************************/
/****** Font ************************************************************************************/
typedef struct rfs_font             RFS_FONT; /* font object                                    */

/********************************/
/*  Enums                       */
/********************************/
/****** Font Enums ******************************************************************************/
typedef enum // font language
{
    FONT_LANG_JAP,                  /* japanese                                                 */
    FONT_LANG_ENG,                  /* english                                                  */
    FONT_LANG_GER,                  /* german                                                   */
    FONT_LANG_FRE,                  /* french                                                   */
    FONT_LANG_SPA,                  /* spanish                                                  */
    FONT_LANG_ITA,                  /* italian                                                  */

    NB_FONT_LANG,                   /* count                                                    */
}
RFE_FONT_LANG;

typedef enum // font color format type
{
    FONT_FTYPE_RGBA_KANJI,          /* 32bit RGBA & contains Kanji & Kana               [SA2PC] */
    FONT_FTYPE_RGBA_ASCII,          /* 32bit RGBA & contains ASCII                      [SA2PC] */

    FONT_FTYPE_1BPP_KANJI,          /* 1bpp & contains Kanji & Kana              [SA1,SADX,SA2] */
    FONT_FTYPE_1BPP_ASCII,          /* 1bpp & contains ASCII                     [SA1,SADX,SA2] */

    NB_FONT_FTYPE,                  /* count                                                    */
}
RFE_FONT_FTYPE;

typedef enum // font script type
{
    FONT_TYPE_KANJI,                /* kanji font page                                          */
    FONT_TYPE_ASCII,                /* ascii font page                                          */

    NB_FONT_TYPE,                   /* count                                                    */
}
RFE_FONT_TYPE;

/********************************/
/*  API Structures              */
/********************************/
/****** Font API ********************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Font **********************************************/
    /*
    *   Load a game font file. Character width and space width are automatically
    *   calculated and respect user-settings.
    *
    *   Parameters:
    *     - fpath       : full path to font file
    *     - ftype       : file type of font
    *
    *   Returns:
    *       Pointer to the created font object, or nullptr if there was an error
    */
    RFS_FONT* (__cdecl* LoadFontFile)( const c8* fpath, RFE_FONT_FTYPE ftype );
    /*
    *   Description:
    *     Half the current space character width. Japanese ASCII spaces use half the width of
    *   their Latin counterpart; Render Fix doesn't know what is ASCII & what is ASCII_J, so
    *   only applies regular ASCII space widths. Use this to fix your Japanese ASCII fonts.
    *
    *   Parameters:
    *     - pFont       : pointer to font object
    */
    void (__cdecl* HalfSpaceWidth)( RFS_FONT* pFont );

    /**** Advanced Font *************************************/
    /*
    *   Set a custom character width list. (optional)
    *
    *   The width list is made up of unsigned int8's, with each character in the
    *   font getting an entry defining how wide it is in pixels. You must ensure
    *   the width list has enough entries to cover every character. If this is not
    *   the case, it will lead to undefined behavior.
    *
    *   Parameters:
    *     - pFont       : pointer to font object
    *     - pWidths     : pointer to u8 array with at least as many entries as there are characters in the font
    */
    void (__cdecl* SetWidthList)( RFS_FONT* pFont, uint8_t* pWidths );

    /**** Font State ****************************************/
    /*
    *   Replace a font in the vanilla game by language and type.
    *
    *   Parameters:
    *     - language    : language to apply the font to
    *     - type        : type of the font to replace
    *     - pFont       : pointer to font object to replace with
    */
    void (__cdecl* SetFont)( RFE_FONT_LANG language, RFE_FONT_TYPE type, RFS_FONT* pFont );
    /*
    *   Get current font by language and type. This can be used to temporarily
    *   replace a font for drawing, then re-applying the original font once you're
    *   done.
    *
    *   Parameters:
    *     - language    : language to get the font from
    *     - type        : type of the font to get
    *
    *   Returns:
    *     The current font being used for that language and font type
    */
    RFS_FONT* (__cdecl* GetFont)( RFE_FONT_LANG language, RFE_FONT_TYPE type );
    /*
    *   Replace a font in Chao World by type.
    *
    *   Parameters:
    *     - type        : type of the font to replace
    *     - pFont       : pointer to font object to replace with
    */
    void (__cdecl* SetChaoFont)( RFE_FONT_TYPE type, RFS_FONT* pFont );
    /*
    *   Get current font in Chao World by type. This can be used to temporarily 
    *   replace a font for drawing, then re-applying the original font once you're
    *   done.
    *
    *   Parameters:
    *     - type        : type of the font to get
    * 
    *   Returns:
    *     The current font being used for that font type
    */
    RFS_FONT* (__cdecl* GetChaoFont)( RFE_FONT_TYPE type );
}
RFAPI_FONT;

#endif/*H_RFAPI_FONT*/
