/*
*   SA2 Render Fix - '/rf_model.h'
*
*   Description:
*     For loading model binary files located in either the private 'model' directory, or the
*   public 'RFMDL' directory.
*/
#ifndef H_RF_MODEL
#define H_RF_MODEL

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** List Load *******************************************************************************/
typedef struct rfmdlfile
{
    const c8*       puPath;         /* local file path                                          */
    NJS_CNK_OBJECT* pObject;        /* loaded object                                            */
}
RFS_OBJFILE;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Load List *******************************************************************************/
/*
*   Description:
*     Get a list of SAModel files, and free any duplicate models in the list to save memory.
*
*   Parameters:
*     - pObjs       : object file list
*     - nbObjs      : number of object files
*
*   Returns:
*     Number of unique files loaded.
*/
isize   RF_GetCnkObjectList( RFS_OBJFILE* restrict pObjs, isize nbObj );

/****** Get Model *******************************************************************************/
/*
*   Description:
*     Get a Ninja object file from either RF's private directory, or the public one.
*
*   Notes:
*     - The file path must exclude the extension for the function to operate correctly.
*     - Model files in the private directly have precidence over public ones.
*
*   Parameters:
*     - puPath      : local path to file
*
*   Returns:
*     Loaded object; or 'nullptr' on failure.
*/
NJS_OBJECT*     RF_GetBscObject( const c8* puPath );
NJS_CNK_OBJECT* RF_GetCnkObject( const c8* puPath );
GJS_OBJECT*     RF_GetGjsObject( const c8* puPath );
/*
*   Description:
*     Get a Ninja model file from either RF's private directory, or the public one.
*
*   Notes:
*     - The file path must exclude the extension for the function to operate correctly.
*     - Model files in the private directly have precidence over public ones.
*     - The address returned from these functions cannot be freed, as the memory is allocated
*       from the head object. If you wish to free the memory, use the Object variant instead.
*
*   Parameters:
*     - puPath      : local path to file
*
*   Returns:
*     Loaded model; or 'nullptr' on failure.
*/
NJS_MODEL*     RF_GetBscModel( const c8* puPath );
NJS_CNK_MODEL* RF_GetCnkModel( const c8* puPath );
GJS_MODEL*     RF_GetGjsModel( const c8* puPath );

EXTERN_END

#endif/*H_RF_MODEL*/
