/*
*   SA2 Render Fix - '/rfu_texture.h'
*
*   Description:
*     Texture utility functions.
*/
#ifndef H_RFU_TEXTURE
#define H_RFU_TEXTURE

/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Create Texlist **************************************************************************/

/*
*   Description:
*     Create a new texlist from a loaded pvm file.
*
*   Parameters:
*     - fname       : pvm file name, no extension
*
*   Returns:
*     Created texlist; or 'nullptr' on failure.
*/
NJS_TEXLIST*    RFU_CreateTexlist( const c7* fname );
/*
*   Description:
*     Free textures and created texlist.
*
*   Parameters:
*     - ptlo        : texlist
*/
void    RFU_FreeTexlist( NJS_TEXLIST* ptlo );

EXTERN_END

#endif/*H_RFU_TEXTURE*/
