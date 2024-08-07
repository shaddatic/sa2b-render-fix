/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/gjdraw.h'
*
*   Description:
*       Ginja draw module.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _GJ_DRAW_H_
#define _GJ_DRAW_H_

/************************/
/*  Includes            */
/************************/
/****** System **********************************************************************/
#include <sa2b/shinobi/sg_xpt.h>

/****** Ginja ***********************************************************************/
#include <sa2b/ninja/gjmodel.h>

EXTERN_START

/************************/
/*  Flags               */
/************************/
/****** Render Mode *****************************************************************/
#define GJD_DRAW_SOLID          (0x01)
#define GJD_DRAW_TRANS          (0x02)

/************************/
/*  Draw                */
/************************/
/****** Render Mode *****************************************************************/
#define _gj_render_mode_            DATA_REF(Sint32, 0x025EFEE0)

/** Set render mode **/
void    gjSetRenderMode( Sint32 mode );

/****** Transform *******************************************************************/
void    gjTransformObject( GJS_OBJECT* object, int(__cdecl* callback)(GJS_MODEL*) );

/****** Model ***********************************************************************/
/** Begin Draw Ginja Models **/
void    gjBeginDrawModel( void );

/** Draw model **/
void    gjDrawModel( GJS_MODEL* model );

/****** Motion **********************************************************************/
#define _gj_motion_callback_        (*(void(__cdecl**)(GJS_OBJECT*))0x01D19C48)

/** Set Ginja motion callback **/
void    gjSetMotionCallback( void (*func)(GJS_OBJECT* gjsobj) );

/** Draw Ginja Motion **/
void    gjDrawMotion(     GJS_OBJECT* object, NJS_MOTION*      motion,     Float frame );
void    gjDrawMotionLink( GJS_OBJECT* object, NJS_MOTION_LINK* motionlink, Float frame );

/****** Ginja Chunk *****************************************************************/
/** Begin draw chunk models **/
void    gjBeginDrawCnkModel( void );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define gjTransformObject_p         FUNC_PTR(void, __cdecl, (GJS_OBJECT*, int(__cdecl*)(GJS_MODEL*)), 0x0042DC20)
#   define gjBeginDrawCnkModel_p       FUNC_PTR(void, __cdecl, (void)                                  , 0x0042D340)
#   define gjBeginDrawModel_p          FUNC_PTR(void, __cdecl, (void)                                  , 0x0042BFF0)
#   define gjDrawObject_p              FUNC_PTR(void, __cdecl, (GJS_OBJECT*)                           , 0x0042B530)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*_GJ_DRAW_H_*/
