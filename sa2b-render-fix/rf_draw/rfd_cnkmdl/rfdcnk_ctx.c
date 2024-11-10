/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source Constants    */
/************************/
/****** Shifted FST *****************************************************************/
#define CNK_FST_UA              (NJD_FST_UA>>NJD_FST_SHIFT) /* use alpha            */

/************************/
/*  Structures          */
/************************/
/****** GX **************************************************************************/
typedef union
{
    struct {
        Uint8 r, g, b, a;
    };
    Uint32 color;
}
GXS_COLOR;

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
GX_SetChanMatColor(s32 chan, GXS_COLOR color)
{
    static const uintptr_t fptr = 0x0041F4E0;

    __asm
    {
        push [color]
        mov eax, [chan]
        call fptr
        add esp, 4
    }
}

static void
ArgbToGx(const NJS_ARGB* restrict pArgb, GXS_COLOR* restrict pGxCol)
{
    pGxCol->a = (u8)( CLAMP(pArgb->a, 0.f, 1.f) * 255.f );
    pGxCol->r = (u8)( CLAMP(pArgb->r, 0.f, 1.f) * 255.f );
    pGxCol->g = (u8)( CLAMP(pArgb->g, 0.f, 1.f) * 255.f );
    pGxCol->b = (u8)( CLAMP(pArgb->b, 0.f, 1.f) * 255.f );
}

static void
BgraToArgb(const NJS_BGRA* restrict pBgra, NJS_ARGB* restrict pArgb)
{
    pArgb->a = ( (f32)pBgra->a * (1.f/255.f) );
    pArgb->r = ( (f32)pBgra->r * (1.f/255.f) );
    pArgb->g = ( (f32)pBgra->g * (1.f/255.f) );
    pArgb->b = ( (f32)pBgra->b * (1.f/255.f) );
}

static void
rjCnkContextBlend(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_BLEND) )
        return;

    if ( !(_nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_BLEND_MODE) )
    {
        _nj_cnk_blend_mode_ = pCtx->blend;
    }

    pCtx->flag &= ~CTXFLG_CTX_BLEND;
}

static void
rjCnkContextTiny(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_TINY) )
        return;

    CnkParseTinyData_Ext(pCtx->tiny.flag, pCtx->tiny.id);

    pCtx->flag &= ~CTXFLG_CTX_TINY;
}

static void
rjCnkContextDiff(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_DIFF) )
        return;

    const Uint32 nj3dflag = _nj_control_3d_flag_;

    GXS_COLOR color;

    /** Get initial material color **/
    {
        if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_MATERIAL )
        {
            ArgbToGx(&_nj_constant_material_, &color);
        }
        else if ( nj3dflag & NJD_CONTROL_3D_OFFSET_MATERIAL )
        {
            NJS_ARGB argb;

            BgraToArgb(&pCtx->diff, &argb);

            argb.a += _nj_constant_material_.a;
            argb.r += _nj_constant_material_.r;
            argb.g += _nj_constant_material_.g;
            argb.b += _nj_constant_material_.b;

            ArgbToGx(&argb, &color);
        }
        else // use material color
        {
            const NJS_BGRA matcol = pCtx->diff;

            color.a = matcol.a;
            color.r = matcol.r;
            color.g = matcol.g;
            color.b = matcol.b;
        }
    }

    /** Adjust diffuse depending on Ninja, draw function, and strip context **/
    {
        const s32 funcmd = RFRS_GetCnkFuncMode();

        const u32 ctxflg = pCtx->flag;

        /** If using texture AND is not DirectDraw, ELSE keep diffuse **/
        if ( !(ctxflg & CTXFLG_STRIP_NOTEX) && !(funcmd & RFRS_CNKFUNCMD_DIRECTBIT) )
        {
            /** If EasyDraw/EasyMultiDraw **/
            if ( funcmd & RFRS_CNKFUNCMD_EASYBIT )
            {
                color.r = 0xFF;
                color.g = 0xFF;
                color.b = 0xFF;
            }
            /** Constant Texture Material flag, SimpleDraw is implied here **/
            else if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL )
            {
                /** AND SimpleMulti OR not CnkS type **/
                if ( funcmd & RFRS_CNKFUNCMD_MULTIBIT || !(ctxflg & CTXFLG_STRIP_NOUVS) )
                {
                    color.r = 0xFF;
                    color.g = 0xFF;
                    color.b = 0xFF;
                }
            }
        }
    }

    GX_SetChanMatColor(0, color);

    pCtx->flag &= ~CTXFLG_CTX_DIFF;
}

static void
rjCnkContextAmbi(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_AMBI) )
        return;

    pCtx->flag &= ~CTXFLG_CTX_AMBI;
}

static void
rjCnkContextSpec(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_SPEC) )
        return;

    pCtx->flag &= ~CTXFLG_CTX_SPEC;
}

static void
SetBlendMode(s32 src, s32 dst, bool ua)
{
    GX_SetBlendMode((src>>NJD_FBS_SHIFT), (dst>>NJD_FBD_SHIFT), ua);
}

static void
rjCnkContextStrip(CNK_CTX* restrict pCtx)
{
    const Sint16 fst = pCtx->fst;

    const bool fst_ua  = ( fst & (NJD_FST_UA|NJD_FST_NAT) );

    const s32 bld = _nj_cnk_blend_mode_;

    const s32 bld_src = (bld & NJD_FBS_MASK);
    const s32 bld_dst = (bld & NJD_FBD_MASK);

    SetBlendMode(bld_src, bld_dst, fst_ua);

    if (fst_ua)
    {
        const bool notex = (pCtx->flag & CTXFLG_STRIP_NOTEX);

        if ( (fst & NJD_FST_NAT)   ||     // IF NoAlphaTest flag
            bld_src == NJD_FBS_ONE ||     // OR src is ONE
            bld_dst == NJD_FBD_ONE ||     // OR dst is ONE
            notex || *pTexSurface != 14 ) // OR no alpha test tex flag
        {
            SetTransparentDraw();
        }
        else
            SetAlphaTestDraw();
    } 
    else
        SetOpaqueDraw();
}

static void
rjCnkContextLight(const CNK_CTX* restrict pCtx)
{
    const int fst_8 = (pCtx->fst >> 8);

    const int light_flag = _nj_cnk_strip_flags_ | (_nj_cnk_last_strip_flags_ ^ fst_8);

    _nj_cnk_last_strip_flags_ = fst_8;

    if (light_flag & 1)
        CnkSetupLights_Ext(fst_8);
}

/****** Extern **********************************************************************/
void
rjCnkSetBlend(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->blend = plist[0] & (NJD_FBS_MASK|NJD_FBD_MASK);

    pCtx->flag |= CTXFLG_CTX_BLEND;
}

void
rjCnkSetMaterial(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    rjCnkSetBlend(pCtx, plist);

    const int flag = ((u8*)plist)[0] & 0x7;

    s32 mat_index = 2;

    if (flag & 1)
    {
        pCtx->diff = *(NJS_BGRA*)(&plist[mat_index]);

        mat_index += 2;
    }
    if (flag & 2)
    {
        pCtx->ambi = *(NJS_BGRA*)(&plist[mat_index]);

        mat_index += 2;
    }
    if (flag & 4)
    {
        pCtx->spec = *(CNK_SPEC*)(&plist[mat_index]);
    }

    pCtx->flag |= ( flag << CTXFLG_SHIFT_MAT );
}

void
rjCnkSetTexture(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->tiny = *(CNK_TINY*)(&plist[0]);

    pCtx->flag |= CTXFLG_CTX_TINY;
}

Sint16
GetCnkStripFlags(const Sint16* plist)
{
    Sint16 fst = plist[0];

    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR )
    {
        fst = (fst & _nj_constant_attr_and_) | _nj_constant_attr_or_;
    }

    const s32 funcmd = RFRS_GetCnkFuncMode();

    if (funcmd & RFRS_CNKFUNCMD_EASYBIT)
    {
        fst |=  (NJD_FST_DB);
        fst &= ~(NJD_FST_IL|NJD_FST_IA|NJD_FST_ENV);
    }
    else if (funcmd & RFRS_CNKFUNCMD_DIRECTBIT)
    {
        fst |=  (NJD_FST_DB);
        fst &= ~(NJD_FST_IL|NJD_FST_IA);
    }

    if (RFRS_GetCullMode() == RFRS_CULLMD_NONE)
    {
        fst |= (NJD_FST_DB);
    }

    return fst & NJD_FST_MASK;
}

void
rjCnkSetStrip(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->fst = GetCnkStripFlags(plist);
}

void
rjCnkContext(CNK_CTX* restrict pCtx)
{
    rjCnkContextBlend(pCtx);
    rjCnkContextTiny(pCtx);
    rjCnkContextDiff(pCtx);
    rjCnkContextAmbi(pCtx);
    rjCnkContextSpec(pCtx);
    rjCnkContextStrip(pCtx);
    rjCnkContextLight(pCtx);
}
