/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/al_texload.h'
*
*   Description:
*     Chao World's texture loading helper system.
*/
#ifndef H_SA2B_CHAO_TEXLOAD
#define H_SA2B_CHAO_TEXLOAD

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Enums                       */
/********************************/
/****** Texture Level ***************************************************************************/
enum 
{ 
    TEX_LEV_COMMON,                 /* load texture for entire chao world                       */
    TEX_LEV_STAGE,                  /* load texture for just this chao stage                    */
    TEX_LEV_LAND,                   /* load texture for just this land table   [acts as COMMON] */
    TEX_LEV_OTHER,                  /* load texture for other purpose          [acts as COMMON] */

    NB_TEX_LEV,                     /* enum count                                               */
};

/********************************/
/*  Structures                  */
/********************************/
/****** Texture Info ****************************************************************************/
typedef struct 
{
    char*        filename;          /* texture pvm file name                                    */
    NJS_TEXLIST* pTexlist;          /* texture list                                             */
}
LOADED_TEX_INFO;

/********************************/
/*  Data                        */
/********************************/
/****** Texture Entries **************************************************************************/
#define TexEntry                    DATA_ARY(LOADED_TEX_INFO, 0x01DCD600, [4][256])

/********************************/
/*  Functions                   */
/********************************/
/****** Load/Release ****************************************************************************/
/*
*   Description:
*     Load a new texture file at a texture level.
* 
*   Parameters:
*     - lev         : texture level
* 
*   Returns:
*     'TRUE' on success; or 'FALSE' on failure.
*/
i32     AL_LoadTex( const c7* filename, NJS_TEXLIST* pTexlist, u16 lev );
/*
*   Description:
*     Release all textures at the given level.
* 
*   Parameters:
*     - lev         : texture level
*/
void    AL_ReleaseTex( u16 lev );

#ifdef SAMT_INCL_FUNCPTRS

/************************/
/*  Function Ptrs       */
/************************/
/****** Usercall ********************************************************************/
#define AL_LoadTex_p            0x00530280 /* EAX(EAX, STK, EBX)                    */
#define AL_ReleaseTex_p         0x005302D0 /* ###(EAX)                              */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CHAO_TEXLOAD*/
