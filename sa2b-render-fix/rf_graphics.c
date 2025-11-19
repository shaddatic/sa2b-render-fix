/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */

/****** SoC *************************************************************************************/
#include <samt/soc/shader.h>        /* shader                                                   */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core/self                                                */
#include <rf_magic.h>               /* state cache                                              */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** Std *************************************************************************************/
#include <math.h>                   /* fmin                                                     */

/****** Self ************************************************************************************/
#include <rf_graphics.h>            /* self                                                     */

/********************************/
/*  Constants                   */
/********************************/
/****** Sampler Count ***************************************************************************/
#define NB_SAMPLER                  (DX9_SAMPLER_DMAPOFFSET+1)

/****** Float To Uint ***************************************************************************/
#define TO_UINT(f)                  *(dx9_uint*)(&(dx9_float){f})

/****** SoC Render Device ***********************************************************************/
#define STRUC_36_DATA(type, offset) (*((type*)&(*(byte**const)(0x01A557BC))[offset]))

/********************************/
/*  Game Defs                   */
/********************************/
/****** Palette *********************************************************************************/
#define PaletteTexMemory            DATA_REF(void**, 0x01A55790)

/****** Struc_36 ********************************************************************************/
#define struc_36LastTexture         STRUC_36_DATA(void*, 0x63C)

/********************************/
/*  Data                        */
/********************************/
/****** Mipmap 'D' Adjust ***********************************************************************/
static const Float MipDAdjList[16] =
{
    0.f, // invalid setting

    -3.00f,  // 0_25
    -1.00f,  // 0_50
    -0.50f,  // 0_75
     0.00f,  // 1_00
    +0.25f,  // 1_25
    +0.50f,  // 1_50
    +0.75f,  // 1_75
    +1.00f,  // 2_00
    +1.25f,  // 2_25
    +1.50f,  // 2_50
    +1.75f,  // 2_75
    +2.00f,  // 3_00
    +2.25f,  // 3_25
    +2.50f,  // 3_50
    +2.75f,  // 3_75
};

/****** Graphics Settings ***********************************************************************/
static s16      SamplerOverride[NB_SAMPLER];
static dx9_uint MipLodBias;

/********************************/
/*  Source                      */
/********************************/
/****** Set Sampler *****************************************************************************/
void
RFGX_SetSamplerState(int index, dx9_samplerstate state, dx9_uint mode)
{
    if ( state == DX9_SAMPLER_MIPMAPLODBIAS )
    {
        switch ( SamplerOverride[state] )
        {
            case -1: // auto
            {
                break;
            }
            case 0:
            {
                mode = MipLodBias;
                break;
            }
            case 1: // clamp negative
            {
                Float m = *(Float*)(&mode);

                m = fmaxf(m, 0.f);

                mode = *(dx9_uint*)(&m);
                break;
            }
            case 2: // clamp positive
            {
                Float m = *(Float*)(&mode);

                m = fminf(m, 0.f);

                mode = *(dx9_uint*)(&m);
                break;
            }
        }
    }
    else // everything else
    {
        if ( SamplerOverride[state] != -1 )
        {
            mode = (dx9_uint) SamplerOverride[state];
        }
    }

    DX9_SetSamplerState(index, state, mode);
}

/****** Get Mipmap 'D' Adjust *******************************************************************/
dx9_uint
RFGX_GetMipmapDepthAdjust(int mipdadjust)
{
    return *(dx9_uint*)(&MipDAdjList[mipdadjust]);
}

/****** Usercall ********************************************************************************/
static void
SetPaletteShader(void* pTex)
{
    static const uintptr_t fptr = 0x004243F0;

    __asm
    {
        mov edx, [pTex]
        call fptr
    }
}

/****** Texture Info ****************************************************************/
typedef struct
{
    RF_MAGICTEXTURE* surface;
    int   address_u;
    int   address_v;
    int   min_filter;
    int   mag_filter;
    int   mip_level;
    int   palette;
    int   unk;
}
TEXTURE_INFO;


/****** Extern **********************************************************************/
static void
GX_SetTexture_Hook(const TEXTURE_INFO* restrict pTex, int index)
{
    static const s16 s_GxToDxAddr[] =
    {
        DX9_TEXADDR_CLAMP,
        DX9_TEXADDR_WRAP,
        DX9_TEXADDR_MIRROR
    };

    static const s16 s_GxToDxFilter[] =
    {
        DX9_TEXFILTER_POINT,
        DX9_TEXFILTER_LINEAR,
        DX9_TEXFILTER_LINEAR,
        DX9_TEXFILTER_LINEAR,
        DX9_TEXFILTER_LINEAR,
        DX9_TEXFILTER_LINEAR
    };

    RF_MAGICTEXTURE* p_mtex = pTex->surface;

    if ( p_mtex )
    {
        RF_MAGIC_STATECACHE* p_mcache = RF_MagicGetStateCache();

        if ( p_mcache->pstexs[index] != p_mtex->texture )
        {
            DX9_SetTexture(index, p_mtex->texture);

            p_mcache->pstexs[index] = p_mtex->texture;
        }

        RFGX_SetSamplerState(index, DX9_SAMPLER_ADDRESSU     , s_GxToDxAddr[pTex->address_u]);
        RFGX_SetSamplerState(index, DX9_SAMPLER_ADDRESSV     , s_GxToDxAddr[pTex->address_v]);
        RFGX_SetSamplerState(index, DX9_SAMPLER_MAGFILTER    , s_GxToDxFilter[pTex->mag_filter]);
        RFGX_SetSamplerState(index, DX9_SAMPLER_MINFILTER    , s_GxToDxFilter[pTex->min_filter]);
        RFGX_SetSamplerState(index, DX9_SAMPLER_MIPFILTER    , DX9_TEXFILTER_POINT);
        RFGX_SetSamplerState(index, DX9_SAMPLER_MIPMAPLODBIAS, TO_UINT(0.f));
    }

    /** update struc thing **/

    struc_36LastTexture = pTex->surface;

    /** palette **/

    const int palette_id = pTex->palette;

    if (palette_id != -1 && PaletteTexMemory)
    {
        SetPaletteShader( PaletteTexMemory[palette_id] );
    }
    else
    {
        /** CWE replaces this but doesn't check for a 'nullptr', so
        we must remove shader flag manually **/

//      SetPaletteShader( nullptr );

        const int shdrmd = ShaderModelMode;

        if (shdrmd != (shdrmd & ~SHADERMDL_FLAG_PALETTE))
        {
            ShaderModelMode &= ~SHADERMDL_FLAG_PALETTE;

            SetShaderType(SHADER_TYPE_MDL);
            SetShaderType(ShaderTypeLast);
        }
    }
}

/****** Usercall Hook ***************************************************************/
__declspec(naked)
static void
___SetTexture(void)
{
    __asm
    {
        push [esp+4]
        push edi

        call GX_SetTexture_Hook

        add esp, 8
        retn
    }
}

/****** Init ************************************************************************************/
void
RFGX_Init(void)
{
    WriteJump(0x0041FA60, ___SetTexture);

    for ( int i = 0; i < NB_SAMPLER; ++i )
    {
        SamplerOverride[i] = -1;
    }

    switch ( CNF_GetInt( CNF_GFX_TEXFILTER ) )
    {
        case CNFE_GFX_TEXFILTER_AUTO:
        {
            break;
        }
        case CNFE_GFX_TEXFILTER_POINT:
        {
            SamplerOverride[DX9_SAMPLER_MAGFILTER] = DX9_TEXFILTER_POINT;
            SamplerOverride[DX9_SAMPLER_MINFILTER] = DX9_TEXFILTER_POINT;
            SamplerOverride[DX9_SAMPLER_MIPFILTER] = DX9_TEXFILTER_POINT;
            break;
        }
        case CNFE_GFX_TEXFILTER_BILINEAR:
        {
            SamplerOverride[DX9_SAMPLER_MAGFILTER] = DX9_TEXFILTER_LINEAR;
            SamplerOverride[DX9_SAMPLER_MINFILTER] = DX9_TEXFILTER_LINEAR;
            SamplerOverride[DX9_SAMPLER_MIPFILTER] = DX9_TEXFILTER_POINT;
            break;
        }
        case CNFE_GFX_TEXFILTER_TRILINEAR:
        {
            SamplerOverride[DX9_SAMPLER_MAGFILTER] = DX9_TEXFILTER_LINEAR;
            SamplerOverride[DX9_SAMPLER_MINFILTER] = DX9_TEXFILTER_LINEAR;
            SamplerOverride[DX9_SAMPLER_MIPFILTER] = DX9_TEXFILTER_LINEAR;
            break;
        }
    }

    const int mipdadj = CNF_GetInt( CNF_GFX_MIPDADJ );

    switch ( mipdadj )
    {
        case CNFE_GFX_MIPDADJ_AUTO:
        {
            break;
        }
        default:
        {
            SamplerOverride[DX9_SAMPLER_MIPMAPLODBIAS] = 0;
            MipLodBias                                 = RFGX_GetMipmapDepthAdjust(mipdadj);
            break;
        }
        case CNFE_GFX_MIPDADJ_CLAMPPOS:
        {
            SamplerOverride[DX9_SAMPLER_MIPMAPLODBIAS] = 1;
            break;
        }
        case CNFE_GFX_MIPDADJ_CLAMPNEG:
        {
            SamplerOverride[DX9_SAMPLER_MIPMAPLODBIAS] = 2;
            break;
        }
    }

    const int aniso = CNF_GetInt( CNF_GFX_ANISOTROPY );

    if ( aniso != CNFE_GFX_ANISOTROPY_AUTO )
    {
        SamplerOverride[DX9_SAMPLER_MINFILTER]     = DX9_TEXFILTER_ANISOTROPIC;
        SamplerOverride[DX9_SAMPLER_MAXANISOTROPY] = aniso;
    }

    if ( CNF_GetInt( CNF_GFX_MIPMAPS ) != CNFE_BOOL_ENABLED )
    {
        SamplerOverride[DX9_SAMPLER_MIPFILTER] = DX9_TEXFILTER_NONE;
    }

    const int maxmiplev = CNF_GetInt( CNF_DEBUG_MAXMIPLEV );

    for ( int i = 0; i < DX9_TSP_REGISTER_MAX+1; ++i )
    {
        DX9_SetSamplerState(i, DX9_SAMPLER_ADDRESSW     , DX9_TEXADDR_CLAMP);
        DX9_SetSamplerState(i, DX9_SAMPLER_BORDERCOLOR  , 0x00000000);
        DX9_SetSamplerState(i, DX9_SAMPLER_MAXMIPLEVEL  , maxmiplev);
        DX9_SetSamplerState(i, DX9_SAMPLER_MAXANISOTROPY, 4);
    }
}
