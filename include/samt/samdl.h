/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/samdl.h'
*
*   Description:
*     For loading and freeing the community made Model, LandTable, and Motion files
*   (sa1mdl, sa2mdl, sa2bmdl, sa1lvl, sa2lvl, sa2blvl, and saanim)
*
*   Notes:
*     - All data is alloc'd into the same memory heap, labels though are loaded
*       into a seperate heap, meaning it can be released using a single 'free' call
*       (or 2 if labels exist). This also helps with memory locality and correct
*       padding widths between data segments is always ensured.
* 
*     - Due to using flexable arrays '[]', using 'sizeof' will lead to odd behavior
*       when using the MSVC compilier. Please use the defined 'SIZEOF_#' constants
*       instead.
*/
#ifndef H_SAMT_SAMDL
#define H_SAMT_SAMDL

/************************/
/*  External Headers    */
/************************/
/****** Ninja ***********************************************************************/
#include <samt/ninja/njbasic.h> /* basic model                                      */
#include <samt/ninja/njchunk.h> /* chunk model                                      */
#include <samt/ninja/gjmodel.h> /* ginja model                                      */

/****** Utility *********************************************************************/
#include <samt/util/std_land.h> /* standard landtable defs               (SA1, SA2) */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Structure Sizes *************************************************************/
#define SIZEOF_SAMDL            (sizeof(s32)*3) /* sizeof(mt_samdl)                 */
#define SIZEOF_SALVL            (sizeof(s32)*3) /* sizeof(mt_salvl)                 */
#define SIZEOF_SAANIM           (sizeof(s32)*4) /* sizeof(mt_saanim)                */
#define SIZEOF_SALABEL          (sizeof(s32)*4) /* sizeof(mt_salabel)               */

/****** SAModel Flags ***************************************************************/
#define SAMDL_NOFLAG            (0)     /* no flags                                 */
#define SAMDL_LABELS            (1<<0)  /* load samdl label data                    */
#define SAMDL_RETURNERR         (1<<1)  /* error in 'type', over 'nullptr'          */

#define SAMDL_BASIC             (1<<4)  /* basic format only                        */
#define SAMDL_CHUNK             (1<<5)  /* chunk format only                        */
#define SAMDL_GINJA             (1<<6)  /* ginja format only                        */
#define SAMDL_MODEL             (1<<7)  /* only model and basic root object         */

#define SAMDL_NOMODEL           (1<<8)  /* exclude models, only object data         */

/****** SALevel Flags ***************************************************************/
#define SALVL_NOFLAG            (0)     /* no flags                                 */
#define SALVL_LABELS            (1<<0)  /* load label data                          */
#define SALVL_RETURNERR         (1<<1)  /* error in 'type', over 'nullptr'          */

#define SALVL_BASIC             (1<<4)  /* basic format only                        */
#define SALVL_CHUNK             (1<<5)  /* chunk format only                        */
#define SALVL_GINJA             (1<<6)  /* ginja format only                        */

#define SALVL_NOTEX             (1<<8)  /* exclude pvm name and tls pointer         */
#define SALVL_NOMOT             (1<<9)  /* exclude 'OBJ_MOTLANDENTRY' data          */

/****** SAAnim Flags ****************************************************************/
#define SAANIM_NOFLAG           (0)     /* no flags                                 */
#define SAANIM_LABELS           (1<<0)  /* load label data                          */
#define SAANIM_RETURNERR        (1<<1)  /* error in 'type', over 'nullptr'          */

/************************/
/*  Enums               */
/************************/
/****** SAModel *********************************************************************/
typedef enum mt_samdl_type
{
    SAMDL_ERROR_NOFILE      = -1,   /* file couldn't be loaded                      */
    SAMDL_ERROR_FILESIZE    = -2,   /* file too small                               */
    SAMDL_ERROR_FILEMAGIC   = -3,   /* incorrect file magic                         */
    SAMDL_ERROR_FILEVER     = -4,   /* unsupported file version                     */
    SAMDL_ERROR_FORMAT      = -8,   /* file contained excluded format               */
    SAMDL_ERROR_NOMODEL     = -9,   /* no model when using 'SAMDL_MODEL'            */

    SAMDL_TYPE_BASIC        = 0,    /* basic object                                 */
    SAMDL_TYPE_CHUNK,               /* chunk object                                 */
    SAMDL_TYPE_GINJA,               /* ginja object                                 */
}
mt_samdl_type;

/****** SALevel *********************************************************************/
typedef enum mt_salvl_type
{
    SALVL_ERROR_NOFILE      = -1,   /* file couldn't be loaded                      */
    SALVL_ERROR_FILESIZE    = -2,   /* file too small                               */
    SALVL_ERROR_FILEMAGIC   = -3,   /* incorrect file magic                         */
    SALVL_ERROR_FILEVER     = -4,   /* unsupported file version                     */
    SALVL_ERROR_FORMAT      = -8,   /* file contained excluded format               */

    SALVL_TYPE_BASIC        = 4,    /* basic landtable: for SA1/DX                  */
    SALVL_TYPE_CHUNK,               /* chunk landtable: for SA2/B                   */
    SALVL_TYPE_GINJA,               /* ginja landtable: for SA2/B                   */
}
mt_salvl_type;

/****** SAAnimation *****************************************************************/
typedef enum mt_saanim_type
{
    SAANIM_ERROR_NOFILE     = -1,   /* file couldn't be loaded                      */
    SAANIM_ERROR_FILESIZE   = -2,   /* file too small                               */
    SAANIM_ERROR_FILEMAGIC  = -3,   /* incorrect file magic                         */
    SAANIM_ERROR_FILEVER    = -4,   /* unsupported file version                     */

    SAANIM_TYPE_MOTION      = 8,    /* ninja motion                                 */
    SAANIM_TYPE_CHAO,               /* chao motion                         (sangle) */
}
mt_saanim_type;

/************************/
/*  Structures          */
/************************/
/****** SALabel *********************************************************************/
typedef struct mt_salabel_entry
{
    const void*  pData;             /* pointer to data the label represents         */
    const char* pcLabel;            /* label string                                 */
}
mt_salabel_entry;

typedef struct mt_salabel
{
    const char* pcAuthor;           /* author of the model                          */
    const char* pcTool;             /* tool the model was edited/created in         */
    const char* pcDescription;      /* model description                            */

    size_t          nbLabel;        /* number of data labels                        */
    mt_salabel_entry pLabels[];     /* data label array                             */
}
mt_salabel;

/****** SAModel *********************************************************************/
typedef struct mt_samdl
{
    mt_samdl_type type;             /* structure format type, or error code         */
    size_t        size;             /* size of model buffer segment                 */

    mt_salabel* pLabels;            /* model label data                             */

    union {
        NJS_OBJECT     pBasic[];    /* basic object head                            */
        NJS_CNK_OBJECT pChunk[];    /* chunk object head                            */
        GJS_OBJECT     pGinja[];    /* ginja object head                            */
    };
}
mt_samdl;

/****** SALevel *********************************************************************/
typedef struct mt_salvl
{
    mt_salvl_type type;             /* structure format type, or error code         */
    size_t        size;             /* size of landtable buffer segment             */

    mt_salabel* pLabels;            /* landtable label data                         */

    union {
        SA1_LANDTABLE pSa1Land[];   /* sa1 landtable head                   (basic) */
        SA2_LANDTABLE pSa2Land[];   /* sa2 landtable head            (chunk, ginja) */
    };
}
mt_salvl;

/****** SAAnimation *****************************************************************/
typedef struct mt_saanim
{
    mt_saanim_type type;            /* structure format type, or error code         */
    size_t         size;            /* size of landtable buffer segment             */

    mt_salabel* pLabels;            /* motion label data                            */

    size_t    nbNode;               /* number of motion nodes                       */
    NJS_MOTION pMotion[];           /* motion head                                  */
}
mt_saanim;

/************************/
/*  Prototypes          */
/************************/
/****** SAModel File ****************************************************************/
/*
*   Description:
*     Load an sa1mdl, sa2mdl, or sa2bmdl file. Model labels can also be loaded by
*   using the 'SAMDL_LABELS' flag, but are otherwise omitted.
*
*   Notes:
*     - When using the 'SAMDL_RETURNERR' flag, if an error occurs the returned
*       pointer does NOT need to be free'd. It uses an internal, constant buffer.
*
*   Parameters:
*     - pcPath      : file path to the samdl file
*     - flag        : samdl load flags
* 
*   Returns:
*     A new samodel structure loaded from the file; or 'nullptr' on error; or, if
*   'RETURNERR' flag is set, an samdl structure with an error code in the 'type'
*   member.
*/
mt_samdl* mtSAModelLoad( const c8* pcPath, const s32 flag );
/*
*   Description:
*     Free a samodel structure, and its labels if any were loaded.
*/
void    mtSAModelFree( mt_samdl* pSamdl );

/****** SALevel File ****************************************************************/
/*
*   Description:
*     Load an sa1lvl, sa2lvl, or sa2blvl file. LandTable labels can also be loaded
*   by using the 'SALVL_LABELS' flag, but are otherwise omitted.
*
*   Notes:
*     - When using the 'SALVL_RETURNERR' flag, if an error occurs the returned
*       pointer does NOT need to be free'd. It uses an internal, constant buffer.
*
*   Parameters:
*     - pcPath      : file path to the salvl file
*     - flag        : salvl load flags
* 
*   Returns:
*     A new salevel structure loaded from the file; or 'nullptr' on error; or, if
*   'RETURNERR' flag is set, an salvl structure with an error code in the 'type'
*   member.
*/
mt_salvl* mtSALevelLoad( const c8* pcPath, const s32 flag );
/*
*   Description:
*     Free a salevel structure, and its labels if any were loaded.
*/
void    mtSALevelFree( mt_salvl* pSalvl);

/****** SAAnimation File ************************************************************/
/*
*   Description:
*     Load an saanim file. Motion labels can also be loaded by using the
*   'SAANIM_LABELS' flag, but are otherwise omitted.
*
*   Notes:
*     - When using the 'SAANIM_RETURNERR' flag, if an error occurs the returned
*       pointer does NOT need to be free'd. It uses an internal, constant buffer.
*
*   Parameters:
*     - pcPath      : file path to the saanim file
*     - flag        : saanim load flags
* 
*   Returns:
*     A new saanim structure loaded from the file; or 'nullptr' on error; or, if
*   'RETURNERR' flag is set, an saanim structure with an error code in the 'type'
*   member.
*/
mt_saanim* mtSAAnimLoad( const c8* pcPath, const s32 flag );
/*
*   Description:
*     Free a saanim structure, and its labels if any were loaded.
*/
void    mtSAAnimFree( mt_saanim* pSaanim );

EXTERN_END

#endif/*H_SAMT_SAMDL*/
