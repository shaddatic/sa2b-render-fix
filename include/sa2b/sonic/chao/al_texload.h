/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_texload.h'
*
*   Description:
*       Contains enums, structs, data, and functions related to Chao World's texture loading engine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_TEXLOAD_H_
#define _SA2B_CHAO_TEXLOAD_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Enums               */
/************************/
enum 
{ 
    TEX_LEV_COMMON,
    TEX_LEV_STAGE,
    TEX_LEV_LAND,
    TEX_LEV_OTHER,
    NB_TEX_LEV,
};

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    char*        filename;
    NJS_TEXLIST* pTexlist;
}
LOADED_TEX_INFO;

/************************/
/*  Data                */
/************************/
#define TexEntry            DATA_ARY(LOADED_TEX_INFO, 0x01DCD600, [4][256])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Load textures at a given level **/
int32_t    AL_LoadTex( const char* filename, NJS_TEXLIST* pTexlist, uint16_t lev );
/** Release all textures at the given level **/
int32_t    AL_ReleaseTex( uint16_t lev );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** User-Function ptrs **/
#   define AL_LoadTex_p         ((void*)0x00530280)
#   define AL_ReleaseTex_p      ((void*)0x005302D0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_TEXLOAD_H_*/
