/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/funchook.h>          /* funchook                                                 */
#include <samt/memory.h>            /* memcopy                                                  */
#include <samt/string.h>            /* strformat                                                */

#define SAMT_INCL_FUNCPTRS

/****** SOC *************************************************************************************/
#include <samt/soc/shader.h>     /* setshader                                                   */
#undef  SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_usermsg.h>             /* alert                                                    */
#include <rf_magic.h>               /* magic                                                    */

/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* dx9ctrl                                                  */

/****** Self ************************************************************************************/
#include <rf_shader.h>              /* self                                                     */

/********************************/
/*  Includes                    */
/********************************/
/****** Strings *********************************************************************************/
#define SHADER_DIR                  "shader" /* shader source directory                         */

/********************************/
/*  Data                        */
/********************************/
/****** Shader Replace **************************************************************************/
static RFS_VSHADER* ShaderVtxEntries[13]; /* replacement vertex shaders                         */
static RFS_PSHADER* ShaderPxlEntries[13]; /* replacement pixel  shaders                         */

/********************************/
/*  Source                      */
/********************************/
/****** Error ***********************************************************************************/
static void
RF_ShaderError(const char* fpath)
{
    char buf[128];

    mtStrFormat(buf, sizeof(buf), "Failed to load shader %s", fpath);

    RF_Alert("Shader Error", buf);
}

static void
CompileError(const char* fpath)
{
    char buf[128];

    mtStrFormat(buf, sizeof(buf), "Failed to compile shader %s", fpath);

    RF_Alert("Shader Error", buf);
}

/************************************************************************************************/
/*
*   Load Pre-Compiled Shader File
*/
/****** Direct **********************************************************************************/
RFS_VSHADER*
RF_DirectLoadVShader(const c8* fpath)
{
    dx9_vtx_shader* vshader = DX9_LoadVtxShader(fpath);

    if (!vshader)
    {
        RF_ShaderError(fpath);
    }

    return (RFS_VSHADER*) vshader;
}

RFS_PSHADER*
RF_DirectLoadPShader(const c8* fpath)
{
    dx9_pxl_shader* vshader = DX9_LoadPxlShader(fpath);

    if (!vshader)
    {
        RF_ShaderError(fpath);
    }

    return (RFS_PSHADER*) vshader;
}

/****** Load Render Fix *************************************************************************/
RFS_VSHADER*
RF_LoadVShader(const c8* fname)
{
    c8 buf[260];

    mtStrFormat(buf, 260, "%s/" SHADER_DIR "/%s.fxc", mtGetModPath(), fname);

    return RF_DirectLoadVShader(buf);
}

RFS_PSHADER*
RF_LoadPShader(const c8* fname)
{
    c8 buf[260];

    mtStrFormat(buf, 260, "%s/" SHADER_DIR "/%s.fxc", mtGetModPath(), fname);

    return RF_DirectLoadPShader(buf);
}

/************************************************************************************************/
/*
*   Compile Shader Source File
*/
/****** Direct **********************************************************************************/
RFS_VSHADER*
RF_DirectCompileVShader(const c8* puSrcPath, const RFS_MACRO* pMacroList)
{
    dx9_vtx_shader* const p_vshader = DX9_CompileVtxShader(puSrcPath, (dx9_macro*) pMacroList);

    if ( !p_vshader )
    {
        CompileError(puSrcPath);
    }

    return (RFS_VSHADER*) p_vshader;
}

RFS_PSHADER*
RF_DirectCompilePShader(const c8* puSrcPath, const RFS_MACRO* pMacroList)
{
    dx9_pxl_shader* const p_pshader = DX9_CompilePxlShader(puSrcPath, (dx9_macro*) pMacroList);

    if ( !p_pshader )
    {
        CompileError(puSrcPath);
    }

    return (RFS_PSHADER*) p_pshader;
}

/****** Compile Render Fix **********************************************************************/
RFS_VSHADER*
RF_CompileVShader(const c8* puSrcName, const RFS_MACRO* pMacroList)
{
    c8 buf[256];
    mtStrFormat(buf, 256, "%s/" SHADER_DIR "/%s.hlsl", mtGetModPath(), puSrcName);

    return RF_DirectCompileVShader(buf, pMacroList);
}

RFS_PSHADER*
RF_CompilePShader(const c8* puSrcName, const RFS_MACRO* pMacroList)
{
    c8 buf[256];
    mtStrFormat(buf, 256, "%s/" SHADER_DIR "/%s.hlsl", mtGetModPath(), puSrcName);

    return RF_DirectCompilePShader(buf, pMacroList);
}

/************************************************************************************************/
/*
*   Set Shaders
*/
/****** Hook Func *******************************************************************************/
void
RF_DirectSetVShader(RFS_VSHADER* pVShader)
{
    RF_MAGIC_SHADERCACHE* restrict p_cache = RF_MagicGetStateCache()->shader;

    if ( p_cache->vshader != pVShader )
    {
        DX9_SetVtxShader( (dx9_vtx_shader*) pVShader );

        p_cache->vshader = pVShader;
    }
}

void
RF_DirectSetPShader(RFS_PSHADER* pPShader)
{
    RF_MAGIC_SHADERCACHE* restrict p_cache = RF_MagicGetStateCache()->shader;

    if ( p_cache->pshader != pPShader )
    {
        DX9_SetPxlShader( (dx9_pxl_shader*) pPShader );

        p_cache->pshader = pPShader;
    }
}

/************************************************************************************************/
/*
*   Replace Game Shaders
*/
/****** Hook Func *******************************************************************************/
static mt_hookinfo SetShaderIndexHookInfo[1];   /* hook info                                    */

static void __stdcall
SetShaderIndexHook(int shader)
{
    RFS_VSHADER* const p_vshader = ShaderVtxEntries[shader];
    RFS_PSHADER* const p_pshader = ShaderPxlEntries[shader];

    if ( !p_pshader || !p_vshader )
    {
        mtHookInfoCall( SetShaderIndexHookInfo, SetShaderIndex(shader) );
    }

    if ( p_vshader ) RF_DirectSetVShader(p_vshader);
    if ( p_pshader ) RF_DirectSetPShader(p_pshader);
}

/****** Replace Shader **************************************************************************/
void
RF_SetGameVShader(RFE_SHADERIX ixShader, RFS_VSHADER* pVShader)
{
    ShaderVtxEntries[ixShader] = pVShader;
}

void
RF_SetGamePShader(RFE_SHADERIX ixShader, RFS_PSHADER* pPShader)
{
    ShaderPxlEntries[ixShader] = pPShader;
}

RFS_VSHADER*
RF_GetGameVShader(RFE_SHADERIX ixShader)
{
    return ShaderVtxEntries[ixShader];
}

RFS_PSHADER*
RF_GetGamePShader(RFE_SHADERIX ixShader)
{
    return ShaderPxlEntries[ixShader];
}

/****** Init ************************************************************************************/
void
RF_ShaderInit(void)
{
    mtHookFunc(SetShaderIndexHookInfo, SetShaderIndex_p, SetShaderIndexHook);

    RFS_VSHADER* p_sonicvs = RF_CompileVShader("sonicvs", nullptr);

    RF_SetGameVShader(RFE_SHADERIX_MDL_NONE, p_sonicvs);
    RF_SetGameVShader(RFE_SHADERIX_MDL_S   , p_sonicvs); 
    RF_SetGameVShader(RFE_SHADERIX_MDL_F   , p_sonicvs);
    RF_SetGameVShader(RFE_SHADERIX_MDL_FS  , p_sonicvs);
    RF_SetGameVShader(RFE_SHADERIX_MDL_P   , p_sonicvs);
    RF_SetGameVShader(RFE_SHADERIX_MDL_PS  , p_sonicvs);
    RF_SetGameVShader(RFE_SHADERIX_MDL_PF  , p_sonicvs);
    RF_SetGameVShader(RFE_SHADERIX_MDL_PFS , p_sonicvs);
}
