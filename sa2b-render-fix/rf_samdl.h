/*
*   SA2 Render Fix - '/rf_samdl.h'
*
*   Description:
*     Render Fix Font module.
*/
#ifndef H_RF_SAMDL
#define H_RF_SAMDL

/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/samdl.h>             /* samdl/lvl                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** List Load *******************************************************************************/
typedef struct rfsamdl
{
    const c8*       puInPath;       /* local file path                                          */
    mt_samdl*       pOutSamdl;      /* loaded samdl file                                        */
}
RFS_SAMDL;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Get SAModel File ************************************************************************/
/*
*   Description:
*     Get an SAModel file from either Render Fix's private 'model' directory, or - if a file
*   isn't found there - the public 'RFMDL' directory.
*
*   Parameters:
*     - puPath      : local path to file
*     - flag        : samdl load flags
*
*   Returns:
*     Loaded SAModel file; or 'nullptr' on failure.
*/
mt_samdl* RF_GetSAModel( const c8* puPath, s32 flag );
/*
*   Description:
*     Free a loaded SAModel file.
*
*   Parameters:
*     - pSamdl      : samdl
*/
void    RF_FreeSAModel( mt_samdl* pSamdl );

/****** Load List *******************************************************************************/
/*
*   Description:
*     Get a list of SAModel files, and free any duplicate models in the list to save memory.
*
*   Parameters:
*     - pSamdls     : samdl entry list
*     - nbSamdl     : number of samdl entries
*     - flag        : samdl flags
*
*   Returns:
*     Number of unique files loaded.
*/
size    RF_GetSAModelList( RFS_SAMDL* restrict pSamdls, size nbSamdl, s32 flag );

/****** Get Model *******************************************************************************/
/*
*   Description:
*     Get a Ninja object file from either RF's private directory, or the public one.
*
*   Parameters:
*     - puPath      : local path to file
*
*   Returns:
*     Loaded object; or 'nullptr' on failure.
*/
NJS_CNK_OBJECT* RF_GetCnkObject( const c8* puPath );
GJS_OBJECT*     RF_GetGjsObject( const c8* puPath );
/*
*   Description:
*     Get a Ninja model file from either RF's private directory, or the public one.
*
*   Parameters:
*     - puPath      : local path to file
*
*   Returns:
*     Loaded model; or 'nullptr' on failure.
*/
NJS_CNK_MODEL* RF_GetCnkModel( const c8* puPath );
GJS_MODEL*     RF_GetGjsModel( const c8* puPath );

EXTERN_END

#endif/*H_RF_SAMDL*/
