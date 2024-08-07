/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/chdraw.h'
*
*   Description:
*       'ch' functions were used in Chao World in the GameCube
*   ports to fill in the gaps in Ginja's Chunk implimentation,
*   such as back-face culling.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_CHDRAW_H_
#define _SA2B_CHAO_CHDRAW_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Data                */
/************************/
#define CnkOffsetAlpha      DATA_REF(f32      , 0x01AED2D0)

#define RareColorTable      DATA_ARY(int32_t, 0x01298448, [13])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   Param
*/
void    chSetRareMaterial(int32_t jewel, int32_t color, b32 multi, b32 nontex, NJS_CNK_MODEL* pModel);
void    chCnkSetOffsetAlpha(f32 alpha);

/*
*   Egg Draw
*/
void    chRareEggDrawModel(NJS_CNK_MODEL* pModel, int32_t Color);
void    chRareEggDrawObject(NJS_CNK_OBJECT* pObject, int32_t Color);
void    chRareEggDrawMotion(NJS_CNK_OBJECT* pObject, int32_t Color, NJS_MOTION* pMotion, f32 frame);

/*
*   Chunk Draw
*/
void    chBeginDrawCnkModel(void);

void    chCnkDrawModel(NJS_CNK_MODEL* model);
void    chCnkDrawObject(NJS_CNK_OBJECT* object);

/** Internal functions **/
int32_t _chCnkDrawModel(NJS_CNK_MODEL* model);
void    _chCnkDrawObject(NJS_CNK_OBJECT* object);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define chBeginDrawCnkModel_p        FUNC_PTR(void  , __cdecl, (void)           , 0x0056E0B0)
#   define chCnkDrawModel_p             FUNC_PTR(void  , __cdecl, (NJS_CNK_MODEL*) , 0x0056E1E0)
#   define _chCnkDrawModel_p            FUNC_PTR(int32_t, __cdecl, (NJS_CNK_MODEL*) , 0x0056E1E0)
#   define _chCnkDrawObject_p           FUNC_PTR(void  , __cdecl, (NJS_CNK_OBJECT*), 0x0056DF50)

/** User-Function ptrs **/
#   define chSetRareMaterial_p          ((void*)0x0056D470)
#   define chRareEggDrawModel_p         ((void*)0x0056D540)
#   define chRareEggDrawObject_p        ((void*)0x0056D590)
#   define chRareEggDrawMotion_p        ((void*)0x0056D600)
#   define chCnkDrawObject_p            ((void*)0x0056E210)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_CHDRAW_H_*/
