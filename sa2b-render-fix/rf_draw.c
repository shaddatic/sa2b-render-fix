/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writemem.h>      /* WriteData, WriteJump, WritePointer               */
#include <samt/writeop.h>       /* WriteJump, WriteCall                             */

#define SAMT_INCL_INTERNAL

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

#undef SAMT_INCL_INTERNAL

/****** Utility *********************************************************************/
#include <samt/util/anyobj.h>   /* ANY_OBJECT                                       */

/****** Game ************************************************************************/
#include <samt/sonic/motion.h>  /* MOTION_CTRL                                      */
#include <samt/sonic/texture.h> /* texload                                          */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_mod.h>             /* RFMOD_PushPolygon                                */
#include <rf_gx.h>              /* render fix gx                                    */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* ninja chunk draw                                 */

/****** Self ************************************************************************/
#include <rf_draw.h>              /* self                                           */
#include <rf_draw/rfd_internal.h> /* children                                       */

/************************/
/*  Constants           */
/************************/
/****** DrawTextureEx ***************************************************************/
#define TexExCount          DATA_REF(int32_t, 0x0077F6BF)

/****** DrawPolygon2D ***************************************************************/
#define Poly2DN             DATA_REF(int32_t, 0x00490FA8)

/************************/
/*  Source              */
/************************/
int 
njCnkNullDrawModel(const NJS_CNK_MODEL* model)
{
    return 0;
}

void
njCnkNullDrawObject(const NJS_CNK_OBJECT* object)
{
    njCnkTransformObject(object, njCnkNullDrawModel);
}

void
njCnkAnimateMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    njDrawMotion(object, motion, frame, njCnkNullDrawModel);
}

void
njCnkAnimateMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame)
{
    njDrawMotionLink(object, motion_link, frame, njCnkNullDrawModel);
}

void
AnimateMotion(const ANY_OBJECT* pObject, const MOTION_CTRL* pMtnCtrl)
{
    if (pMtnCtrl->flag & 0x02)
    {
        NJS_MOTION_LINK motion_link;

        motion_link.motion[0] = pMtnCtrl->minfo[0].pMotion;
        motion_link.frame[0]  = pMtnCtrl->minfo[0].frame;

        motion_link.motion[1] = pMtnCtrl->minfo[1].pMotion;
        motion_link.frame[1]  = pMtnCtrl->minfo[1].frame;
        
        njCnkAnimateMotionLink(pObject, &motion_link, pMtnCtrl->ratio);
    }
    else
        njCnkAnimateMotion(pObject, pMtnCtrl->minfo[0].pMotion, pMtnCtrl->minfo[0].frame);
}

void
rjDrawTextureEx(const NJS_TEXTURE_VTX* polygon, Int count, Int trans)
{
    TexExCount = count;
    njDrawTextureEx(polygon, 4, trans);
    TexExCount = 4;
}

void
rjDrawPolygon2D(const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr)
{
    Poly2DN = n;
    njDrawPolygon2D(p, 4, pri, attr);
    Poly2DN = 4;
}

void
rjSetCheapShadowMode(Int mode)
{
    if (mode < 0 || mode > 256)
        return;

    RFMOD_SetAlpha( 1.f - ( (Float)mode * (1.f/256.f) ) );
}

/****** Set Tex (Draw) **************************************************************/
#define SocTexOverrideFlags     DATA_REF(s32, 0x01A557A4)

#define SocTexOverrideAddrU     DATA_REF(s32, 0x01A557A8)
#define SocTexOverrideAddrV     DATA_REF(s32, 0x01A557AC)

#define TexInfoDraw             DATA_REF(TEXTURE_INFO, 0x019341A0)

static void
SetTexForDraw(void)
{
    NJS_TEXSURFACE* p_texsurface = _nj_curr_ctx_->texsurface;

    const Uint32 texmode = _nj_curr_ctx_->texmode;

    /** clamp/flip **/

    if ( texmode & NJD_TEXTURECLAMP_CLAMP_U )
    {
        TexInfoDraw.address_u = 0;
    }
    else if ( texmode & NJD_TEXTUREFLIP_FLIP_U )
    {
        TexInfoDraw.address_u = 2;
    }
    else
        TexInfoDraw.address_u = 1;

    if ( texmode & NJD_TEXTURECLAMP_CLAMP_V )
    {
        TexInfoDraw.address_v = 0;
    }
    else if ( texmode & NJD_TEXTUREFLIP_FLIP_V )
    {
        TexInfoDraw.address_v = 2;
    }
    else
        TexInfoDraw.address_v = 1;

    /** filter mode **/

    switch ( (texmode & NJD_TEXTUREFILTER_TRILINEAR_B) >> 13 )
    {
        case 0: // point
        {
            TexInfoDraw.min_filter = 0;
            TexInfoDraw.mag_filter = 0;
            break;
        }
        case 1: // bilinear (default)
        {
            TexInfoDraw.min_filter = 1;
            TexInfoDraw.mag_filter = 1;
            break;
        }
        case 2: // trilinear A
        {
            TexInfoDraw.min_filter = 1;
            TexInfoDraw.mag_filter = 1;
            break;
        }
        case 3: // trilinear B
        {
            TexInfoDraw.min_filter = 1;
            TexInfoDraw.mag_filter = 1;
            break;
        }
    }

    if ( RFRS_GetSocTexHackMode() == RFRS_SOCTEXHACKMD_ENABLED )
    {
        if ( SocTexOverrideFlags & (1<<0) )
        {
            TexInfoDraw.address_u = SocTexOverrideAddrU;
        }

        if ( SocTexOverrideFlags & (1<<1) )
        {
            TexInfoDraw.address_v = SocTexOverrideAddrV;
        }
    }

    /** palette **/

    const Uint32 sflag = p_texsurface->fSurfaceFlags;

    TexInfoDraw.palette = (sflag & NJD_SURFACEFLAGS_PALETTIZED) ? _nj_curr_ctx_->bank : -1;

    TexInfoDraw.mip_level = (sflag & NJD_SURFACEFLAGS_MIPMAPED) ? 1 : 0;

    TexInfoDraw.surface = p_texsurface->pSurface;

    RX_SetTexture(&TexInfoDraw, 0);
}

static void
EasyDrawObject(NJS_CNK_OBJECT* object, void* fn)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    njCnkTransformObject(object, _rjCnkDrawModel);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
MenuScreenEffectFix(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    const int nj3dflag = _nj_control_3d_flag_;

    _nj_control_3d_flag_ &= ~NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL;

    njCnkSimpleDrawMotion(object, motion, frame);

    _nj_control_3d_flag_ = nj3dflag;
}

__declspec(naked)
static void
___MenuScreenEffectFix(void)
{
    __asm
    {
        push        [esp+8]  // frame
        push        ecx      // motion
        push        [esp+12] // object
        call        MenuScreenEffectFix
        add esp,    12
        retn
    }
}

/****** Init ************************************************************************/
void
RF_DrawInit(void)
{
    /** Allow 'count' argument to be writeable **/
    WriteData(&TexExCount, 4, int32_t);

    /** Allow 'n' argument to be writeable **/
    WriteData(&Poly2DN, 4, int32_t);

    /** RF Chunk draw functions **/
    WriteJump(0x0042D340, rjCnkBeginDrawModel);
    WriteJump(0x0042D500, rjCnkDrawModelSub);

    /** Fix shape motion not calling MotionCallback **/
    WriteJump(0x00784890, rjCnkPushPopShape);
    WriteJump(0x00784E70, rjCnkPushPopShapeLink);

    /** Fix chCnk and Ginja using the wrong multiplication value to convert 0~256
        integer UVs to 0~1. In vanilla, it uses (1/255) **/

    static const f64 s_NewUvMul = (1.0/256.0);

    WritePointer(0x005A563C, &s_NewUvMul); // chCnk // NJD_CV_D8
    WritePointer(0x005A591C, &s_NewUvMul); // chCnk // NJD_CV_VN
    WritePointer(0x005A5C1C, &s_NewUvMul); // chCnk // NJD_CV_VN_D8
    WritePointer(0x0041BCC3, &s_NewUvMul); // Ginja

    EXTERN NJS_TEXLIST texlist_rf_texerr[];

    texLoadTexturePrsFile("RF_TEXERR", texlist_rf_texerr);

    WriteJump(0x004291B0, SetTexForDraw);

    /** Set default context **/

    njTextureFilterMode(NJD_TEXTUREFILTER_BILINEAR);

    njTextureClampMode(NJD_TEXTURECLAMP_NOCLAMP);

    njTextureFlipMode(NJD_TEXTUREFLIP_NOFLIP);

    njPolygonCullingMode(NJD_POLYGON_CULLINGSMALL);

//  njPolygonCullingSize(0.05f);

    /** Fix draw function issues **/

    WriteCall(0x00756A2E, EasyDrawObject);         // Jump Aura (bfc issue)
    WriteCall(0x00756D77, EasyDrawObject);         // Other Aura
    WriteCall(0x007561FF, EasyDrawObject);         // Spindash Aura

    WriteCall(0x0066838C, ___MenuScreenEffectFix); // DC menu screen effect text too bright
}
