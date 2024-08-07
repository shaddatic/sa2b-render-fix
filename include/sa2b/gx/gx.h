/*
*   Sonic Adventure Mod Tools (SA2B) - '/gx/gx.h'
*
*   Description:
*       GX is the rendering library used by the GameCube & Wii.
*   Although the devs never actually directly interacted with
*   it, Ginja and updated Ninja calls did. Many calls to it,
*   and for it, still exist in the game, although converted to
*   comparable DirectX calls.
*       Other than the name of the library, everything else was
*   found and named via testing and context.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _GX_H_
#define _GX_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/gx/gxlight.h>
#include <sa2b/gx/gxstate.h>

/************************/
/*  Constants           */
/************************/
/** Primitive Types **/
#define GXD_PRIM_TRIANGLE       (0x90)
#define GXD_PRIM_TRISTRIP       (0x98)
#define GXD_PRIM_TRIFAN         (0xA0)
#define GXD_PRIM_LINE           (0xA8)
#define GXD_PRIM_LINESTRIP      (0xB0)
#define GXD_PRIM_POINT          (0xB8)

/************************/
/*  Data                */
/************************/
#define _gx_nb_vtx_                 DATA_REF(int32_t , 0x01933F04)
#define _gx_prim_type_              DATA_REF(int32_t , 0x01933EFC)

/** Buffer poiners **/
#define _gx_vtx_buf_base_           DATA_REF(uint32_t, 0x01933EF8)
#define _gx_vtx_buf_offset_         DATA_REF(uint32_t, 0x01933F0C)
#define _gx_vtx_buf_offset_cpy_     DATA_REF(uint32_t, 0x01933F10)
#define _gx_vtx_buf_start_          DATA_REF(uint32_t, 0x01933F08)

#define _gx_cull_                   DATA_REF(int32_t , 0x01933F14) // ??

#define _gx_unused_                 DATA_REF(int32_t , 0x01933F00) // ???

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Sets everything up at launch **/
void    GX_Startup(void);

/** Populates buffers with Ginja model data **/
void    GX_PushDisplayList(uint8_t* pPrim, uint32_t nbPrim);

/** Draws and clears buffer **/
void    GX_End(void);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptr **/
#   define GX_Startup_p                 FUNC_PTR(void, __cdecl   , (void)              , 0x004205E0)
#   define GX_PushDisplayList_p         FUNC_PTR(void, __cdecl   , (uint8_t*, uint32_t), 0x0041C9B0)
#   define GX_End_p                     FUNC_PTR(void, __cdecl   , (void)              , 0x0041C070)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_GX_H_*/
