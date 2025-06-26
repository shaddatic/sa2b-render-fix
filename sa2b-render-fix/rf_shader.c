/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/funchook.h>          /* funchook                                                 */
#include <samt/memory.h>            /* memcopy                                                  */
#include <samt/string.h>            /* strformat                                                */

/****** Game ************************************************************************************/
#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/shaders.h>     /* setshader                                                */
#undef  SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_usermsg.h>             /* alert                                                    */

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
static dx9_vtx_shader* ShaderVtxEntries[13]; /* replacement vertex shaders                      */
static dx9_pxl_shader* ShaderPxlEntries[13]; /* replacement pixel  shaders                      */

/****** Func Hook *******************************************************************************/
static bool      IsHookedSetAndLoadShader;    /* hook active                                    */
static hook_info HookInfoSetAndLoadShader[1]; /* hook info                                      */

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
dx9_vtx_shader*
RF_DirectLoadVtxShader(const c8* fpath)
{
    dx9_vtx_shader* vshader = DX9_LoadVtxShader(fpath);

    if (!vshader)
    {
        RF_ShaderError(fpath);
    }


    return vshader;
}

dx9_pxl_shader*
RF_DirectLoadPxlShader(const c8* fpath)
{
    dx9_pxl_shader* vshader = DX9_LoadPxlShader(fpath);

    if (!vshader)
    {
        RF_ShaderError(fpath);
    }

    return vshader;
}

/****** Load Render Fix *************************************************************************/
dx9_vtx_shader*
RF_LoadVtxShader(const c8* fname)
{
    c8 buf[260];

    mtStrFormat(buf, 260, "%s/" SHADER_DIR "/%s.fxc", mtGetModPath(), fname);

    return RF_DirectLoadVtxShader(buf);
}

dx9_pxl_shader*
RF_LoadPxlShader(const c8* fname)
{
    c8 buf[260];

    mtStrFormat(buf, 260, "%s/" SHADER_DIR "/%s.fxc", mtGetModPath(), fname);

    return RF_DirectLoadPxlShader(buf);
}

/************************************************************************************************/
/*
*   Compile Shader Source File
*/
/****** Direct **********************************************************************************/
dx9_vtx_shader*
RF_DirectCompileVtxShader(const c8* puSrcPath, const dx9_macro* pMacroList)
{
    dx9_vtx_shader* const p_vshader = DX9_CompileVtxShader(puSrcPath, pMacroList);

    if ( !p_vshader )
    {
        CompileError(puSrcPath);
    }

    return p_vshader;
}

dx9_pxl_shader*
RF_DirectCompilePxlShader(const c8* puSrcPath, const dx9_macro* pMacroList)
{
    dx9_pxl_shader* const p_pshader = DX9_CompilePxlShader(puSrcPath, pMacroList);

    if ( !p_pshader )
    {
        CompileError(puSrcPath);
    }

    return p_pshader;
}

/****** Compile Render Fix **********************************************************************/
dx9_vtx_shader*
RF_CompileVtxShader(const c8* puSrcName, const dx9_macro* pMacroList)
{
    c8 buf[256];
    mtStrFormat(buf, 256, "%s/" SHADER_DIR "/%s.hlsl", mtGetModPath(), puSrcName);

    return RF_DirectCompileVtxShader(buf, pMacroList);
}

dx9_pxl_shader*
RF_CompilePxlShader(const c8* puSrcName, const dx9_macro* pMacroList)
{
    c8 buf[256];
    mtStrFormat(buf, 256, "%s/" SHADER_DIR "/%s.hlsl", mtGetModPath(), puSrcName);

    return RF_DirectCompilePxlShader(buf, pMacroList);
}

/************************************************************************************************/
/*
*   Replace Game Shaders
*/
/****** Hook Func *******************************************************************************/
static void __stdcall
SetAndLoadShaderHook(int shader)
{
    FuncHookCall( HookInfoSetAndLoadShader, SetAndLoadShader(shader) );

    if (ShaderVtxEntries[shader])
        DX9_SetVtxShader(ShaderVtxEntries[shader]);

    if (ShaderPxlEntries[shader])
        DX9_SetPxlShader(ShaderPxlEntries[shader]);
}

/****** Replace Shader **************************************************************************/
void
RF_ReplaceVtxShader(int index, dx9_vtx_shader* pVtxShader)
{
    if (index < 0 || index > 12)
        return;

    if (!IsHookedSetAndLoadShader)
    {
        FuncHook(HookInfoSetAndLoadShader, SetAndLoadShader_p, SetAndLoadShaderHook);
        IsHookedSetAndLoadShader = true;
    }

    ShaderVtxEntries[index] = pVtxShader;
}

void
RF_ReplacePxlShader(int index, dx9_pxl_shader* pPxlShader)
{
    if (index < 0 || index > 12)
        return;

    if (!IsHookedSetAndLoadShader)
    {
        FuncHook(HookInfoSetAndLoadShader, SetAndLoadShader_p, SetAndLoadShaderHook);
        IsHookedSetAndLoadShader = true;
    }

    ShaderPxlEntries[index] = pPxlShader;
}
