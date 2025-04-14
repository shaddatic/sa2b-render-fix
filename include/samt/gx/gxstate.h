/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/gx/gxstate.h'
*
*   Description:
*       GX state controls and definitions.
*/
#ifndef _GX_STATE_H_
#define _GX_STATE_H_

EXTERN_START

/************************/
/*  Constants           */
/************************/
/** Cull Modes **/
#define GXD_CULLMODE_NONE       (0) /* don't cull any triangles                     */
#define GXD_CULLMODE_CW         (1) /* cull clockwise triangles                     */
#define GXD_CULLMODE_CCW        (2) /* cull counter-clockwise triangles             */
#define GXD_CULLMODE_ALL        (3) /* cull all triangles                           */

/** Blend Modes **/
#define GXD_BLENDMODE_ZERO      (0)
#define GXD_BLENDMODE_ONE       (1)
#define GXD_BLENDMODE_OC        (2)
#define GXD_BLENDMODE_IOC       (3)
#define GXD_BLENDMODE_SA        (4)
#define GXD_BLENDMODE_ISA       (5)
#define GXD_BLENDMODE_DA        (6)
#define GXD_BLENDMODE_IDA       (7)

/************************/
/*  Functions           */
/************************/
/** Sets back-face culling mode **/
void    GX_SetCullMode(int32_t mode);

/** Sets transparency blending mode **/
void    GX_SetBlendMode(int32_t mdSrc, int32_t mdDst, b32 bAlphaBlend);

/** Set size of point primitives in pixels **/
void    GX_SetPointSize(uint8_t pxSize);

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define GX_SetCullMode_p             FUNC_PTR(void, __fastcall, (int32_t), 0x00420440)

/** User-function ptrs **/
#   define GX_SetBlendMode_p            ((void*)0x00420480)
#   define GX_SetPointSize_p            ((void*)0x004203F0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*_GX_STATE_H_*/
