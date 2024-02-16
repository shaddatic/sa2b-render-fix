/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/chdraw.h'
*
*   Contains 'ch' data and draw functions used in Chao World.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
#define CnkOffsetAlpha      DataRef(float32_t, 0x01AED2D0)

#define RareColorTable      DataAry(int32_t, 0x01298448, [13])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   Param
*/
void    chSetRareMaterial(int32_t jewel, int32_t color, bool32_t multi, bool32_t nontex, NJS_CNK_MODEL* pModel);
void    chCnkSetOffsetAlpha(float32_t alpha);

/*
*   Egg Draw
*/
void    chRareEggDrawModel(NJS_CNK_MODEL* pModel, int32_t Color);
void    chRareEggDrawObject(NJS_CNK_OBJECT* pObject, int32_t Color);
void    chRareEggDrawMotion(NJS_CNK_OBJECT* pObject, int32_t Color, NJS_MOTION* pMotion, float32_t frame);

/*
*   Chunk Draw
*/
void    chBeginDrawCnkModel(void);

void    chCnkDrawModel(NJS_CNK_MODEL* model);
void    chCnkDrawObject(NJS_CNK_OBJECT* object);

/** Internal functions **/
int32_t  _chCnkDrawModel(NJS_CNK_MODEL* model);
void    _chCnkDrawObject(NJS_CNK_OBJECT* object);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define chBeginDrawCnkModel_p       FuncPtr(void  , __cdecl, (void)           , 0x0056E0B0)
#define chCnkDrawModel_p            FuncPtr(void  , __cdecl, (NJS_CNK_MODEL*) , 0x0056E1E0)
#define _chCnkDrawModel_p           FuncPtr(int32_t, __cdecl, (NJS_CNK_MODEL*) , 0x0056E1E0)
#define _chCnkDrawObject_p          FuncPtr(void  , __cdecl, (NJS_CNK_OBJECT*), 0x0056DF50)

/** User-Function ptrs **/
EXTERN const void* const chSetRareMaterial_p;
EXTERN const void* const chRareEggDrawModel_p;
EXTERN const void* const chRareEggDrawObject_p;
EXTERN const void* const chRareEggDrawMotion_p;
EXTERN const void* const chCnkDrawObject_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_CHDRAW_H_ */
