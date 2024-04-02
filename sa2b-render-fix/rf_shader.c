#include <sa2b/core.h>
#include <sa2b/funchook.h>
#include <sa2b/config.h>
#include <sa2b/dx9ctrl.h>

/** Source **/
#define SAMT_INCL_FUNCPTRS
#include <sa2b/src/shaders.h>
#undef  SAMT_INCL_FUNCPTRS

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_usermsg.h>

/** Self **/
#include <rf_shader.h>

/** Constants **/
#define SHADER_PATH     "shader"

/** Globals **/
static d3d_vtx_shader* ShaderVtxEntries[13];
static d3d_pxl_shader* ShaderPxlEntries[13];

/** Functions **/
static void
RF_ShaderError(const char* fpath)
{
    char buf[128];

    snprintf(buf, sizeof(buf), "Failed to load shader %s", fpath);

    RF_Alert("Shader Error", buf);
}

d3d_vtx_shader*
RF_LoadVtxShader(const utf8* fname)
{
    utf8 buf[260];

    snprintf(buf, 260, "%s/" SHADER_PATH "/%s.fxc", GetModPath(), fname);

    d3d_vtx_shader* vshader = DX9_LoadVtxShader(buf);

    if (!vshader)
        RF_ShaderError(buf);

    return vshader;
}

d3d_pxl_shader*
RF_LoadPxlShader(const utf8* fname)
{
    utf8 buf[260];

    snprintf(buf, 260, "%s/" SHADER_PATH "/%s.fxc", GetModPath(), fname);

    d3d_pxl_shader* pshader = DX9_LoadPxlShader(buf);

    if (!pshader)
        RF_ShaderError(buf);

    return pshader;
}

static hook_info* HookInfoSetAndLoadShader;

static void __stdcall
SetAndLoadShaderHook(int shader)
{
    FuncHookCall( HookInfoSetAndLoadShader, SetAndLoadShader(shader) );

    if (ShaderVtxEntries[shader])
        DX9_SetVtxShader(ShaderVtxEntries[shader]);

    if (ShaderPxlEntries[shader])
        DX9_SetPxlShader(ShaderPxlEntries[shader]);
}

void
RF_ReplaceVtxShader(int index, d3d_vtx_shader* pVtxShader)
{
    if (index < 0 || index > 12)
        return;

    if (!HookInfoSetAndLoadShader)
        HookInfoSetAndLoadShader = FuncHook(SetAndLoadShader_p, SetAndLoadShaderHook);

    ShaderVtxEntries[index] = pVtxShader;
}

void
RF_ReplacePxlShader(int index, d3d_pxl_shader* pPxlShader)
{
    if (index < 0 || index > 12)
        return;

    if (!HookInfoSetAndLoadShader)
        HookInfoSetAndLoadShader = FuncHook(SetAndLoadShader_p, SetAndLoadShaderHook);

    ShaderPxlEntries[index] = pPxlShader;
}
