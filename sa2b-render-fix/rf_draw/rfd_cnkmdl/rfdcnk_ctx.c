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
#include <rf_gx.h>          /* rf gx                                                */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source Constants    */
/************************/
/****** Shifted FST *****************************************************************/
#define CNK_FST_UA              (NJD_FST_UA>>NJD_FST_SHIFT) /* use alpha            */

#define CnkSetTextureList       DATA_ARY(TEXTURE_INFO, 0x01934768, [8])

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
ArgbToBgra(const NJS_ARGB* restrict pArgb, NJS_BGRA* restrict pBgra)
{
    pBgra->a = (u8)( CLAMP(pArgb->a, 0.f, 1.f) * 255.f );
    pBgra->r = (u8)( CLAMP(pArgb->r, 0.f, 1.f) * 255.f );
    pBgra->g = (u8)( CLAMP(pArgb->g, 0.f, 1.f) * 255.f );
    pBgra->b = (u8)( CLAMP(pArgb->b, 0.f, 1.f) * 255.f );
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
BgraToGx(const NJS_BGRA* restrict pBgra, GXS_COLOR* restrict pGxCol)
{
    pGxCol->a = pBgra->a;
    pGxCol->r = pBgra->r;
    pGxCol->g = pBgra->g;
    pGxCol->b = pBgra->b;
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
    EXTERN NJS_TEXLIST texlist_rf_texerr[];

    if ( !(pCtx->flag & CTXFLG_CTX_TINY) )
        return;

    /** get context **/

    const Uint16 headbits = pCtx->tiny.headbits;
    const Uint16 texbits  = pCtx->tiny.texbits;

    /** get texture **/

    const s32 texid = texbits & NJD_TID_MASK;

    const NJS_TEXLIST* p_tls = njGetCurrentTexList();

    if (texid >= (s32)p_tls->nbTexture)
    {
    TEX_ERR:
        int* texaddr = (int*) texlist_rf_texerr->textures[0].texaddr;

        const int* texparambuf = (int*) texaddr[3];

        const bool flg_tes5 = texparambuf[7] >> 31;

        pTexSurface = (int*) &texparambuf[1];

        TEXTURE_INFO* p_tinfo = &CnkSetTextureList[0];

        p_tinfo->texp       = (void*) texparambuf[8];
        p_tinfo->min_filter = 0;
        p_tinfo->mag_filter = 0;
        p_tinfo->address_u = 1;
        p_tinfo->address_v = 1;
        p_tinfo->palette = -1;

        p_tinfo->tes5 = flg_tes5 != 0;

        RX_SetTexture(p_tinfo, 0);
        return;
        /** purposefully don't unset CTX_TINY flag **/
    }

    const int* texaddr = (int*) p_tls->textures[texid].texaddr;

    if (!texaddr)
        goto TEX_ERR;

    const int* texparambuf = (int*) texaddr[3];

    if (!texparambuf)
        goto TEX_ERR;

    pTexSurface = (int*) &texparambuf[1];

    /** texture info start **/

    TEXTURE_INFO* p_tinfo = &CnkSetTextureList[0];

    /** texture pointer and palette **/

    if (texparambuf[7] & 0x8000)
    {
        p_tinfo->texp    = (void*) texparambuf[8];
        p_tinfo->palette = texaddr[2];
    }
    else
    {
        p_tinfo->texp    = (void*) texparambuf[8];
        p_tinfo->palette = -1;
    }

    /** texture filtering **/

    switch ( (texbits & NJD_FFM_MASK) >> NJD_FFM_SHIFT )
    {
        case 0: // point
        {
            p_tinfo->min_filter = 0;
            p_tinfo->mag_filter = 0;
            break;
        }
        case 1: // bilinear (default)
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
        case 2: // trilinear A
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
        case 3: // trilinear B
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
    }

    /** texture wrapping **/

    if (headbits & NJD_FCL_U) // CLamp
    {
        p_tinfo->address_u = 0;
    }
    else if (headbits & NJD_FFL_U) // FLip (mirror)
    {
        p_tinfo->address_u = 2;
    }
    else
        p_tinfo->address_u = 1; // repeat

    if (headbits & NJD_FCL_V) // CLamp
    {
        p_tinfo->address_v = 0;
    }
    else if (headbits & NJD_FFL_V) // FLip (mirror)
    {
        p_tinfo->address_v = 2;
    }
    else
        p_tinfo->address_v = 1; // repeat

    /** tes5 **/

    p_tinfo->tes5 = (texparambuf[7] >> 31) != 0;

    /** set texture **/

    RX_SetTexture(p_tinfo, 0);

    /** texture info end **/

    pCtx->flag &= ~CTXFLG_CTX_TINY;
}

static void
rjCnkContextDiff(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_DIFF) )
        return;

    const Uint32 nj3dflag = _nj_control_3d_flag_;

    NJS_BGRA color;

    /** Get initial material color **/
    {
        if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_MATERIAL )
        {
            ArgbToBgra(&_nj_constant_material_, &color);
        }
        else if ( nj3dflag & NJD_CONTROL_3D_OFFSET_MATERIAL )
        {
            NJS_ARGB argb;

            BgraToArgb(&pCtx->diff, &argb);

            argb.a += _nj_constant_material_.a;
            argb.r += _nj_constant_material_.r;
            argb.g += _nj_constant_material_.g;
            argb.b += _nj_constant_material_.b;

            ArgbToBgra(&argb, &color);
        }
        else
            color = pCtx->diff;
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
                /** AND Normal OR SimpleMulti OR not CnkS type **/
                if ( funcmd == RFRS_CNKFUNCMD_NORMAL || funcmd & RFRS_CNKFUNCMD_MULTIBIT || !(ctxflg & CTXFLG_STRIP_NOUVS) )
                {
                    color.r = 0xFF;
                    color.g = 0xFF;
                    color.b = 0xFF;
                }
            }
        }
    }

    /** apply diffuse **/

    GXS_COLOR gxcolor;

    BgraToGx(&color, &gxcolor);

    GX_SetChanMatColor(0, gxcolor);

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

        if ( (fst & NJD_FST_NAT)        // IF NoAlphaTest flag
            || bld_src == NJD_FBS_ONE   // OR src is ONE
            || bld_dst == NJD_FBD_ONE   // OR dst is ONE
            || notex                    // OR no texture
            || (pTexSurface && *pTexSurface != 14) ) // OR no alpha test tex flag
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
