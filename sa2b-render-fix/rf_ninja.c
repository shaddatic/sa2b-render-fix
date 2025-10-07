/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writemem.h>      /* WriteData, WriteJump, WritePointer               */
#include <samt/writeop.h>       /* WriteJump, WriteCall                             */
#include <samt/funchook.h>      /* hookinfo                                         */

#define SAMT_INCL_INTERNAL

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

#undef SAMT_INCL_INTERNAL

/****** Soc *************************************************************************/
#include <samt/soc/shader.h>    /* setshader                                        */

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

/****** RF Utility ******************************************************************/
#include <rfu_float.h>          /* replaceflaot                                     */

/****** Self ************************************************************************/
#include <rf_ninja.h>             /* self                                           */
#include <rf_ninja/rj_internal.h> /* children                                       */

/************************/
/*  Game Data           */
/************************/
/****** DrawTextureEx ***************************************************************/
#define TexExCount          DATA_REF(int32_t, 0x0077F6BF)

/****** DrawPolygon2D ***************************************************************/
#define Poly2DN             DATA_REF(int32_t, 0x00490FA8)

/************************/
/*  Data                */
/************************/
/****** Depth Queue *****************************************************************/
Float _rj_depth_queue_near_;
Float _rj_depth_queue_far_;

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
rjSetCheapShadowMode(Int mode)
{
    if (mode < 0 || mode > 256)
        return;

    RFMOD_SetAlpha( 1.f - ( (Float)mode * (1.f/256.f) ) );
}

void
rjSetCheapShadowColor(Float r, Float g, Float b)
{
    RFMOD_SetColor( r, g, b );
}

void
rjSetDepthQueue(Float near, Float far)
{
    _rj_depth_queue_near_ = near;
    _rj_depth_queue_far_  = far;
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

    if ( SocTexOverrideFlags & (1<<0) )
    {
        TexInfoDraw.address_u = SocTexOverrideAddrU;
    }

    if ( SocTexOverrideFlags & (1<<1) )
    {
        TexInfoDraw.address_v = SocTexOverrideAddrV;
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

    njCnkTransformObject(object, rjCnkDrawModel);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
MenuScreenEffectFix(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    const u32 nj3dflag = _nj_control_3d_flag_;

    _nj_control_3d_flag_ = nj3dflag & ~NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL;

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

__declspec(naked)
static void
___njCnkEasyDrawModel(void)
{
    __asm
    {
        push        eax
        call        njCnkEasyDrawModel
        add esp,    4
        retn
    }
}

__declspec(naked)
static void
___SetScreenHook(void)
{
    __asm
    {
        push        eax
        call        njSetScreen // SAMT
        add esp,    4
        retn
    }
}

/****** Chao Shader *****************************************************************/

#define chCnkPList_p                FUNC_PTR(void, __cdecl, (Sint16*, Uint16), 0x0056D7C0)
#define chAttrPList_p               FUNC_PTR(void, __cdecl, (Sint16*, Uint16), 0x0056D9F0)

static void
chCnkPListHook(Sint16* plist, Uint16 vtype)
{
    SetShaderType( SHADER_TYPE_MDL );

    chCnkPList_p(plist, vtype);
}

static void
chAttrPListHook(Sint16* plist, Uint16 vtype)
{
    SetShaderType( SHADER_TYPE_MDL );

    chAttrPList_p(plist, vtype);
}

#define ChaoUIElemStart_p           FUNC_PTR(void, __cdecl, (void), 0x00543CE0)

static mt_hookinfo ChaoUIElemStartHookInfo[1];
static void
ChaoUIElemStartHook(void)
{
    SetShaderType( SHADER_TYPE_UI ); // not a typo, just weird

    mtHookInfoCall( ChaoUIElemStartHookInfo, ChaoUIElemStart_p() );
}

#define ChaoUIElemStart2_p          FUNC_PTR(void, __cdecl, (void), 0x00583C60)

static mt_hookinfo ChaoUIElemStart2HookInfo[1];
static void
ChaoUIElemStart2Hook(void)
{
    SetShaderType( SHADER_TYPE_MDL ); // not a typo, just weird

    mtHookInfoCall( ChaoUIElemStart2HookInfo, ChaoUIElemStart2_p() );
}

/****** Init ************************************************************************/
void
RF_DrawInit(void)
{
    RFD_CoreInit();
    RFD_ChunkInit();
    RFD_TexerrInit();
    RFD_PolygonInit();
    RFD_SpriteInit();
    RFD_AlphaBlendInit();

    /** Allow 'count' argument to be writeable **/
    WriteData(&TexExCount, 4, int32_t);

    /** Allow 'n' argument to be writeable **/
    WriteData(&Poly2DN, 4, int32_t);

    /** Replace game's `njSetScreen` with SAMT version **/
    WriteJump(0x0077E980, ___SetScreenHook);

    /** Fix chCnk and Ginja using the wrong multiplication value to convert 0~256
        integer UVs to 0~1. In vanilla, it uses (1/255) **/

    const f64 uvmul_new = (1.0/256.0);

    RFU_ReplaceFloat(0x005A563A, uvmul_new); // chCnk // NJD_CV_D8
    RFU_ReplaceFloat(0x005A591A, uvmul_new); // chCnk // NJD_CV_VN
    RFU_ReplaceFloat(0x005A5C1A, uvmul_new); // chCnk // NJD_CV_VN_D8
    RFU_ReplaceFloat(0x0041BCC1, uvmul_new); // Ginja

    const f64 farclip = 65536.0;

    RFU_ReplaceFloat(0x00458FC5, farclip);
    RFU_ReplaceFloat(0x004EE20A, farclip);
    RFU_ReplaceFloat(0x004EE329, farclip);
    RFU_ReplaceFloat(0x0067C829, farclip);
    RFU_ReplaceFloat(0x006B5BAE, farclip);
    RFU_ReplaceFloat(0x006B602F, farclip);
    RFU_ReplaceFloat(0x00458E63, farclip);
    RFU_ReplaceFloat(0x0044BBD0, farclip);

    /** 2D draw params **/

    WriteJump(0x004291B0, SetTexForDraw);

    /** Set default context **/

    njTextureFilterMode(NJD_TEXTUREFILTER_BILINEAR);

    njTextureClampMode(NJD_TEXTURECLAMP_NOCLAMP);

    njTextureFlipMode(NJD_TEXTUREFLIP_NOFLIP);

    njPolygonCullingMode(NJD_POLYGON_CULLINGSMALL);

    rjSetDepthQueue(-1800.f, -2000.f);

//  njPolygonCullingSize(0.05f);

    /** Fix draw function issues **/

    WriteCall(0x00756A2E, EasyDrawObject);         // Jump Aura (bfc issue)
    WriteCall(0x00756D77, EasyDrawObject);         // Other Aura
    WriteCall(0x007561FF, EasyDrawObject);         // Spindash Aura

    WriteCall(0x0066838C, ___MenuScreenEffectFix); // DC menu screen effect text too bright

    WriteCall(0x0055D53E, EasyDrawObject);         // ALO ball

    WriteCall(0x006D9F51, ___njCnkEasyDrawModel);  // Savepoint
    WriteCall(0x006D9FFE, ___njCnkEasyDrawModel);
    WriteCall(0x006DA08A, ___njCnkEasyDrawModel);

    WriteCall(0x00656B3A, ___njCnkEasyDrawModel); // Sand Ocean: Moon

    /** Fix shader issues (mostly Chao world) **/

    WriteCall( 0x0056DF29, chCnkPListHook );
    WriteCall( 0x0056DF13, chAttrPListHook );

    mtHookFunc( ChaoUIElemStartHookInfo , ChaoUIElemStart_p , ChaoUIElemStartHook );
    mtHookFunc( ChaoUIElemStart2HookInfo, ChaoUIElemStart2_p, ChaoUIElemStart2Hook );
}
