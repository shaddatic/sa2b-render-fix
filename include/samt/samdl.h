/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/samdl.h'
*
*   Description:
*     For loading and freeing the community made Model (sa1mdl, sa2mdl, sa2bmdl), LandTable
*   (sa1lvl, sa2lvl, sa2blvl), and Motion files (saanim)
*
*   Notes:
*     - All data is alloc'd into the same memory heap, labels though are loaded into a seperate
*       heap, meaning it can be released using a single 'free' call (or 2 if labels exist).
*       This also helps with memory locality and correct padding widths between data segments
*       is always ensured.
*
*     - When using the 'RETURNERR' load flag, the returned structure when an error occurs is
*       part of a constant buffer and does not need to be freed.
*
*     - When using the 'NOHEAD' load flag, the returned pointer must be cast to the correct
*       structure manually: eg. 'object = (NJS_OBJECT*) mtSAModelLoad(path, SAMDL_NOHEAD)'.
*       Additionally, the returned pointer is to be free'd by you and not mt.
* 
*     - Due to using flexable arrays '[]', using 'sizeof' will lead to odd behavior when using
*       the MSVC compilier. Please use the defined 'SIZEOF_#' constants instead.
*/
#ifndef H_SAMT_SAMDL
#define H_SAMT_SAMDL

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Utility *********************************************************************************/
#include <samt/util/std_land.h>     /* standard landtable defs                       (SA1, SA2) */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Structure Sizes *************************************************************************/
#define SIZEOF_SAMDL                (sizeof(i32)*3) /* sizeof(mt_samdl)                         */
#define SIZEOF_SALVL                (sizeof(i32)*3) /* sizeof(mt_salvl)                         */
#define SIZEOF_SAANIM               (sizeof(i32)*4) /* sizeof(mt_saanim)                        */
#define SIZEOF_SALABEL              (sizeof(i32)*4) /* sizeof(mt_salabel)                       */

/****** SAModel Flags ***************************************************************************/
#define SAMDL_NOFLAG                (0)     /* no flags                                         */
#define SAMDL_LABELS                (1<<0)  /* load samdl label data                            */
#define SAMDL_RETURNERR             (1<<1)  /* error in 'type', over 'nullptr'                  */
#define SAMDL_NOHEAD                (1<<2)  /* don't return header, only object                 */

#define SAMDL_BASIC                 (1<<4)  /* basic format only                                */
#define SAMDL_CHUNK                 (1<<5)  /* chunk format only                                */
#define SAMDL_GINJA                 (1<<6)  /* ginja format only                                */
#define SAMDL_MODEL                 (1<<7)  /* only model and basic root object                 */

#define SAMDL_NOMODEL               (1<<8)  /* exclude models, only object data                 */

/****** SALevel Flags ***************************************************************************/
#define SALVL_NOFLAG                (0)     /* no flags                                         */
#define SALVL_LABELS                (1<<0)  /* load label data                                  */
#define SALVL_RETURNERR             (1<<1)  /* error in 'type', over 'nullptr'                  */
#define SALVL_NOHEAD                (1<<2)  /* don't return header, only landtable              */

#define SALVL_BASIC                 (1<<4)  /* basic format only                                */
#define SALVL_CHUNK                 (1<<5)  /* chunk format only                                */
#define SALVL_GINJA                 (1<<6)  /* ginja format only                                */

#define SALVL_NOTEX                 (1<<8)  /* exclude pvm name and tls pointer                 */
#define SALVL_NOMOT                 (1<<9)  /* exclude 'OBJ_MOTLANDENTRY' data                  */

/****** SAAnim Flags ****************************************************************************/
#define SAANIM_NOFLAG               (0)     /* no flags                                         */
#define SAANIM_LABELS               (1<<0)  /* load label data                                  */
#define SAANIM_RETURNERR            (1<<1)  /* error in 'type', over 'nullptr'                  */
#define SAANIM_NOHEAD               (1<<2)  /* don't return header, only motion                 */

#define SAANIM_NJ2                  (1<<8)  /* ninja2 motion data                               */

/****** SATex Flags *****************************************************************************/
#define SATEX_NOFLAG                (0)     /* no flags                                         */
#define SATEX_LABELS                (1<<0)  /* load label data                                  */
#define SATEX_RETURNERR             (1<<1)  /* error in 'type', over 'nullptr'                  */
#define SATEX_NOHEAD                (1<<2)  /* don't return header, only texlist                */

#define SATEX_NOTEXN                (1<<8)  /* exclude texture names                            */

/********************************/
/*  Enums                       */
/********************************/
/****** SAModel *********************************************************************************/
typedef enum mt_samdl_type
{
    SAMDL_ERROR_NOFILE      = -1,   /* file couldn't be loaded                                  */
    SAMDL_ERROR_FILESIZE    = -2,   /* file too small                                           */
    SAMDL_ERROR_FILEMAGIC   = -3,   /* incorrect file magic                                     */
    SAMDL_ERROR_FILEVER     = -4,   /* unsupported file version                                 */
    SAMDL_ERROR_FORMAT      = -8,   /* file contained excluded format                           */
    SAMDL_ERROR_NOMODEL     = -9,   /* no model when using 'SAMDL_MODEL'                        */

    SAMDL_TYPE_BASIC        = 0,    /* basic object                                             */
    SAMDL_TYPE_CHUNK,               /* chunk object                                             */
    SAMDL_TYPE_GINJA,               /* ginja object                                             */
}
mt_samdl_type;

/****** SALevel *********************************************************************************/
typedef enum mt_salvl_type
{
    SALVL_ERROR_NOFILE      = -1,   /* file couldn't be loaded                                  */
    SALVL_ERROR_FILESIZE    = -2,   /* file too small                                           */
    SALVL_ERROR_FILEMAGIC   = -3,   /* incorrect file magic                                     */
    SALVL_ERROR_FILEVER     = -4,   /* unsupported file version                                 */
    SALVL_ERROR_FORMAT      = -8,   /* file contained excluded format                           */

    SALVL_TYPE_BASIC        = 4,    /* basic landtable: for SA1/DX                              */
    SALVL_TYPE_CHUNK,               /* chunk landtable: for SA2/B                               */
    SALVL_TYPE_GINJA,               /* ginja landtable: for SA2/B                               */
}
mt_salvl_type;

/****** SAAnimation *****************************************************************************/
typedef enum mt_saanim_type
{
    SAANIM_ERROR_NOFILE     = -1,   /* file couldn't be loaded                                  */
    SAANIM_ERROR_FILESIZE   = -2,   /* file too small                                           */
    SAANIM_ERROR_FILEMAGIC  = -3,   /* incorrect file magic                                     */
    SAANIM_ERROR_FILEVER    = -4,   /* unsupported file version                                 */

    SAANIM_TYPE_MOTION      = 8,    /* ninja motion                                             */
    SAANIM_TYPE_CHAO,               /* chao motion                                     (sangle) */
    SAANIM_TYPE_NINJA2              /* ninja2 motion                                            */
}
mt_saanim_type;

/****** SATexture *******************************************************************************/
typedef enum mt_satex_type
{
    SATEX_ERROR_NOFILE     = -1,    /* file couldn't be loaded                                  */
    SATEX_ERROR_FILESIZE   = -2,    /* file too small                                           */
    SATEX_ERROR_FILEMAGIC  = -3,    /* incorrect file magic                                     */
    SATEX_ERROR_FILEVER    = -4,    /* unsupported file version                                 */
    SATEX_ERROR_SIZE       = -8,    /* file size is too small                                   */
    SATEX_ERROR_READ       = -9,    /* failed to read file                                      */
    SATEX_ERROR_NOTLIST    = -10,   /* no texname entry                                         */

    SATEX_TYPE_TEXLIST     = 12,    /* ninja texlist                                            */
}
mt_satex_type;

/********************************/
/*  Structures                  */
/********************************/
/****** SALabel *********************************************************************************/
typedef struct mt_salabel_entry
{
    const void*  pData;             /* pointer to data the label represents                     */
    const char* pcLabel;            /* label string                                             */
}
mt_salabel_entry;

typedef struct mt_salabel
{
    const char* pcAuthor;           /* author of the model                                      */
    const char* pcTool;             /* tool the model was edited/created in                     */
    const char* pcDescription;      /* model description                                        */

    isize           nbLabel;        /* number of data labels                                    */
    mt_salabel_entry pLabels[];     /* data label array                                         */
}
mt_salabel;

/****** SAModel *********************************************************************************/
typedef struct mt_samdl
{
    mt_samdl_type type;             /* structure format type, or error code                     */
    isize         size;             /* size of model buffer segment                             */

    mt_salabel* pLabels;            /* model label data                                         */

    union {
        NJS_OBJECT     pBasic[];    /* basic object head                                        */
        NJS_CNK_OBJECT pChunk[];    /* chunk object head                                        */
        GJS_OBJECT     pGinja[];    /* ginja object head                                        */
    };
}
mt_samdl;

/****** SALevel *********************************************************************************/
typedef struct mt_salvl
{
    mt_salvl_type type;             /* structure format type, or error code                     */
    isize         size;             /* size of landtable buffer segment                         */

    mt_salabel* pLabels;            /* landtable label data                                     */

    union {
        SA1_LANDTABLE pSa1Land[];   /* sa1 landtable head                               (basic) */
        SA2_LANDTABLE pSa2Land[];   /* sa2 landtable head                        (chunk, ginja) */
    };
}
mt_salvl;

/****** SAAnimation *****************************************************************************/
typedef struct mt_saanim
{
    mt_saanim_type type;            /* structure format type, or error code                     */
    isize          size;            /* size of landtable buffer segment                         */

    mt_salabel* pLabels;            /* motion label data                                        */

    isize     nbNode;               /* number of motion nodes                                   */
    NJS_MOTION pMotion[];           /* motion head                                              */
}
mt_saanim;

/****** SATexture *******************************************************************************/
typedef struct mt_satex
{
    mt_satex_type type;             /* structure format type, or error code                     */
    isize         size;             /* size of texlist buffer segment                           */

    mt_salabel* pLabels;            /* texlist label data                                       */

    NJS_TEXLIST pTexlist[];         /* texlist head                                             */
}
mt_satex;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   File Load
*/
/****** SAModel File ****************************************************************************/
/*
*   Description:
*     Load an sa1mdl, sa2mdl, or sa2bmdl file.
*
*   Parameters:
*     - pcPath      : file path to the samdl file
*     - flag        : samdl load flags
* 
*   Returns:
*     An samdl/object structure; or 'nullptr' on error.
*/
mt_samdl* mtSAModelLoad( const c8* pcPath, const u32 flag );
/*
*   Description:
*     Free a samodel structure, and its labels if any were loaded.
*/
void    mtSAModelFree( mt_samdl* pSamdl );

/****** SALevel File ****************************************************************************/
/*
*   Description:
*     Load an sa1lvl, sa2lvl, or sa2blvl file.
*
*   Parameters:
*     - pcPath      : file path to the salvl file
*     - flag        : salvl load flags
* 
*   Returns:
*     An salvl/landtable structure; or 'nullptr' on error.
*/
mt_salvl* mtSALevelLoad( const c8* pcPath, const u32 flag );
/*
*   Description:
*     Free a salevel structure, and its labels if any were loaded.
*/
void    mtSALevelFree( mt_salvl* pSalvl);

/****** SAAnimation File ************************************************************************/
/*
*   Description:
*     Load an saanim file.
*
*   Parameters:
*     - pcPath      : file path to the saanim file
*     - flag        : saanim load flags
* 
*   Returns:
*     An saanim/motion structure; or 'nullptr' on error.
*/
mt_saanim* mtSAAnimLoad( const c8* pcPath, const u32 flag );
/*
*   Description:
*     Free a saanim structure, and its labels if any were loaded.
*/
void    mtSAAnimFree( mt_saanim* pSaanim );

/****** SATexture File **************************************************************************/
/*
*   Description:
*     Load an satex file.
*
*   Parameters:
*     - pcPath      : file path to the satex file
*     - flag        : satex load flags                                               [SATEX_##]
* 
*   Returns:
*     An satex/texlist structure loaded from the file; or 'nullptr' on error.
*/
mt_satex* mtSATexLoad( const c8* pcPath, const u32 flag );
/*
*   Description:
*     Free a satex structure, and its labels if any were loaded.
*/
void    mtSATexFree( mt_satex* pSatex );

/************************************************************************************************/
/*
*   Memory Load
*/
/****** SAModel File ****************************************************************************/
/*
*   Description:
*     Get an samdl structure from a file already in memory.
*
*   Notes:
*     - Other than the source, this is functionally identical to the 'Load' variant.
*     - Managing the input memory after reading is completed is left up to you, not mt.
*     - This should only be called once, as some flags makes changes to the memory that can't
*       be undone.
*
*   Parameters:
*     - pMem        : file in memory
*     - flag        : samdl load flags
*
*   Returns:
*     An samdl/object structure; or 'nullptr' on error.
*/
mt_samdl* mtSAModelMem( void* pMem, usize szMem, u32 flag );

/****** SALevel File ****************************************************************************/
/*
*   Description:
*     Get an salvl structure from a file already in memory.
*
*   Notes:
*     - Other than the source, this is functionally identical to the 'Load' variant.
*     - Managing the input memory after reading is completed is left up to you, not mt.
*     - This should only be called once, as some flags makes changes to the memory that can't
*       be undone.
*
*   Parameters:
*     - pMem        : file in memory
*     - flag        : salvl load flags
*
*   Returns:
*     An salvl/landtable structure; or 'nullptr' on error.
*/
mt_salvl* mtSALevelMem( void* pMem, usize szMem, u32 flag );

/****** SAAnimation File ************************************************************************/
/*
*   Description:
*     Get an saanim structure from a file already in memory.
*
*   Notes:
*     - Other than the source, this is functionally identical to the 'Load' variant.
*     - Managing the input memory after reading is completed is left up to you, not mt.
*
*   Parameters:
*     - pMem        : file in memory
*     - flag        : saanim load flags
*
*   Returns:
*     An saanim/motion structure; or 'nullptr' on error.
*/
mt_saanim* mtSAAnimMem( void* pMem, usize szMem, u32 flag );

/****** SATexture File ************************************************************************/
/*
*   Description:
*     Get an SATex structure from a file already in memory.
*
*   Notes:
*     - Other than the source, this is functionally identical to the 'Load' variant.
*     - Managing the input memory after reading is completed is left up to you, not mt.
*
*   Parameters:
*     - pMem        : file in memory
*     - flag        : satex load flags
*
*   Returns:
*     An satex/texlist structure; or 'nullptr' on error.
*/
mt_satex* mtSATexMem( void* pMem, usize szMem, u32 flag );

EXTERN_END

#endif/*H_SAMT_SAMDL*/
