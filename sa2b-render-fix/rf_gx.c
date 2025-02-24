/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */
#include <samt/writeop.h>   /* writejump                                            */

/****** Game ************************************************************************/
#include <samt/sonic/shaders.h> /* setshader                                        */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_magic.h>       /* magic                                                */

/****** Self ************************************************************************/
#include <rf_gx.h>          /* self                                                 */

/************************/
/*  Game Data           */
/************************/
/****** Override Flags **************************************************************/
#define TexOverrideFlags            DATA_REF(int, 0x01A557A4)

#define TexOverrideAddrU            DATA_REF(int, 0x01A557A8)
#define TexOverrideAddrV            DATA_REF(int, 0x01A557AC)
#define TexOverrideMinFilter        DATA_REF(int, 0x01A557B0)
#define TexOverrideMagFilter        DATA_REF(int, 0x01A557B4)

/****** Palette *********************************************************************/
#define PaletteTexMemory            DATA_REF(void**, 0x01A55790)

/****** Struc_36 ********************************************************************/
#define struc_36                    DATA_REF(char*, 0x01A557BC)

#define STRUC_36_DATA(type, offset)     ( *((type*) &struc_36[offset]) )

#define struc_36SamplerData         STRUC_36_DATA(RF_MAGICSAMPLER, 0x620)
#define struc_36LastTexture         STRUC_36_DATA(void*          , 0x63C)
#define struc_36Material1           STRUC_36_DATA(RF_MAGICCOLOR  , 0x308)
#define struc_36Material2           STRUC_36_DATA(RF_MAGICCOLOR  , 0x318)
#define struc_36Ambient             STRUC_36_DATA(RF_MAGICCOLOR  , 0x2E8)

/************************/
/*  Source              */
/************************/
/****** Usercall ********************************************************************/
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

/****** Extern **********************************************************************/
void
RX_SetTexture(const TEXTURE_INFO* restrict pTex, int index)
{
    static const int s_GxToDxAddr[]   = { 2, 0, 1 };
    static const int s_GxToDxFilter[] = { 1, 2, 2, 2, 2, 2 };
    
    RF_MAGICSAMPLER msample;

    msample.MinFilter = s_GxToDxFilter[pTex->min_filter];
    msample.MagFilter = s_GxToDxFilter[pTex->mag_filter];

    msample.MipFilter = 2;

    msample.AddressU = s_GxToDxAddr[pTex->address_u];
    msample.AddressV = s_GxToDxAddr[pTex->address_v];

    msample.AddressW  = 2;

    msample.BorderColor = 0;

    RF_MagicSetShaderConstantTexture(MAGIC_SHADER_PIXEL, index, pTex->surface, &msample);

    /** update struc thing **/

//  struc_36SamplerData = msample;
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

        const int shdrmd = ShaderMode;

        if (shdrmd != (shdrmd & ~SHADERMODE_PALLETE))
        {
            ShaderMode &= ~SHADERMODE_PALLETE;

            SetShaders(1);
            SetShaders(ShaderLast);
        }
    }
}

void
RX_SetChanMatColor_Direct(int nbChan, float r, float g, float b, float a)
{
    RF_MAGICCOLOR rgba;

    if (nbChan == 1)
    {
        rgba.r = r;
        rgba.g = g;
        rgba.b = b;
        rgba.a = 0.f;
    }
    else
    {
        rgba.r = r;
        rgba.g = g;
        rgba.b = b;
        rgba.a = a;
    }

    RF_MagicSetShaderConstantColor(MAGIC_SHADER_VERTEX, 66 + (nbChan == 1), &rgba);
}

void
RX_SetChanAmbColor_Direct(float r, float g, float b)
{
    RF_MAGICCOLOR rgba;

    rgba.r = r;
    rgba.g = g;
    rgba.b = b;
    rgba.a = 1.f;

    //struc_36Ambient = rgba;

    RF_MagicSetShaderConstantColor(MAGIC_SHADER_VERTEX, 68, &rgba);
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

        call RX_SetTexture

        add esp, 8
        retn
    }
}

/****** Init ************************************************************************/
void
RF_GxInit(void)
{
    WriteJump(0x0041FA60, ___SetTexture);
}
