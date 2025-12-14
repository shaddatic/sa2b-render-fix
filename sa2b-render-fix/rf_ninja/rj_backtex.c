/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */
#include <samt/funchook.h>          /* function hook                                            */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* display ratio                                            */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_util.h>                /* utility                                                  */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Back Texture ****************************************************************************/
#define FadeColor                   DATA_REF(NJS_COLOR, 0x0171CDA0)

/********************************/
/*  Enums                       */
/********************************/
/****** Back Vertex *****************************************************************************/
typedef enum
{
    RJ_BACK_HI_L,
    RJ_BACK_LO_L,
    RJ_BACK_HI_R,
    RJ_BACK_LO_R,

    RJ_NB_BACK_NUM
}
RJ_BACK_NUM;

/********************************/
/*  Structures                  */
/********************************/
/****** Back Vertex *****************************************************************************/
typedef struct
{
    Float  u, v;
    Uint32 bcol;
    Uint32 ocol;
}
RJS_BACK_VTX;

/********************************/
/*  Variables                   */
/********************************/
/****** Back Texture ****************************************************************************/
static NJS_TEXSURFACE* _rj_back_surface_;

/****** Vertex **********************************************************************************/
static RJS_BACK_VTX _rj_back_vtx_[RJ_NB_BACK_NUM];

/********************************/
/*  Source                      */
/********************************/
/****** Draw Backtex ****************************************************************************/
static void
DrawBackTextureSub(Float depth)
{
    _nj_curr_ctx_->texture = _rj_back_surface_;

    rjSetTexture2D(FALSE);

    NJS_TEXTUREH_VTX vtx[4];

    const Float ratio = (GetDisplayRatio() - 1.0f);

    const Float pos_off = ratio * (640.0f / 2.f);
    const Float uvh_off = ratio * ((_rj_back_vtx_[RJ_BACK_HI_R].u - _rj_back_vtx_[RJ_BACK_HI_L].u) / 2.f);
    const Float uvl_off = ratio * ((_rj_back_vtx_[RJ_BACK_LO_R].u - _rj_back_vtx_[RJ_BACK_LO_L].u) / 2.f);

    vtx[0].x    = 0.0f - pos_off;
    vtx[0].y    = 0.0f;
    vtx[0].z    = depth;
    vtx[0].u    = _rj_back_vtx_[RJ_BACK_HI_L].u - uvh_off;
    vtx[0].v    = _rj_back_vtx_[RJ_BACK_HI_L].v;
    vtx[0].bcol = _rj_back_vtx_[RJ_BACK_HI_L].bcol;
    vtx[0].ocol = _rj_back_vtx_[RJ_BACK_HI_L].ocol;

    vtx[1].x    = 0.0f - pos_off;
    vtx[1].y    = 480.0f;
    vtx[1].z    = depth;
    vtx[1].u    = _rj_back_vtx_[RJ_BACK_LO_L].u - uvh_off;
    vtx[1].v    = _rj_back_vtx_[RJ_BACK_LO_L].v;
    vtx[1].bcol = _rj_back_vtx_[RJ_BACK_LO_L].bcol;
    vtx[1].ocol = _rj_back_vtx_[RJ_BACK_LO_L].ocol;

    vtx[2].x    = 640.0f + pos_off;
    vtx[2].y    = 0.0f;
    vtx[2].z    = depth;
    vtx[2].u    = _rj_back_vtx_[RJ_BACK_HI_R].u + uvh_off;
    vtx[2].v    = _rj_back_vtx_[RJ_BACK_HI_R].v;
    vtx[2].bcol = _rj_back_vtx_[RJ_BACK_HI_R].bcol;
    vtx[2].ocol = _rj_back_vtx_[RJ_BACK_HI_R].ocol;

    vtx[3].x    = 640.0f + pos_off;
    vtx[3].y    = 480.0f;
    vtx[3].z    = depth;
    vtx[3].u    = _rj_back_vtx_[RJ_BACK_LO_R].u + uvh_off;
    vtx[3].v    = _rj_back_vtx_[RJ_BACK_LO_R].v;
    vtx[3].bcol = _rj_back_vtx_[RJ_BACK_LO_R].bcol;
    vtx[3].ocol = _rj_back_vtx_[RJ_BACK_LO_R].ocol;

    rjDrawTextureHEx(vtx, 4, FALSE);
}

static void
DrawBackColorSub(Float depth)
{
    NJS_POLYGON_VTX vtx[4];

    const f32 pos_off = (GetDisplayRatio() - 1.0f) * 320.0f;

    vtx[0].x   = 0.0f - pos_off;
    vtx[0].y   = 0.0f;
    vtx[0].z   = depth;
    vtx[0].col = _rj_back_vtx_[RJ_BACK_HI_L].bcol;

    vtx[1].x   = 0.0f - pos_off;
    vtx[1].y   = 480.0f;
    vtx[1].z   = depth;
    vtx[1].col = _rj_back_vtx_[RJ_BACK_LO_L].bcol;

    vtx[2].x   = 640.0f + pos_off;
    vtx[2].y   = 0.0f;
    vtx[2].z   = depth;
    vtx[2].col = _rj_back_vtx_[RJ_BACK_HI_R].bcol;

    vtx[3].x   = 640.0f + pos_off;
    vtx[3].y   = 480.0f;
    vtx[3].z   = depth;
    vtx[3].col = _rj_back_vtx_[RJ_BACK_LO_R].bcol;

    rjDrawPolygon(vtx, 4, FALSE);
}

static void
DrawBackTexture(void)
{
    if (FadeColor.argb.a == 0xFF)
    {
        return;
    }

    const Float depth = 0.f;

    if ( _rj_back_surface_ )
    {
        DrawBackTextureSub(depth);
    }
    else
    {
        DrawBackColorSub(depth);
    }
}

/****** Other Func ******************************************************************************/
static void
SetBackColor(uint32_t b, uint32_t g, uint32_t r)
{
    NJS_COLOR col;

    col.argb.r = r;
    col.argb.g = g;
    col.argb.b = b;

    rjSetBackColor(col.color, col.color, col.color);
}

/****** Usercall Hook ***************************************************************************/
const void* const RendererClear_p = (void*)0x00867B20;

#pragma optimize("", off)

__declspec(naked)
static void
___RendererClearHook(void)
{
    /** 1. Re-push stack objects for OG func call
        2. Call original function, which cleans the new stack
        3. Call DrawBackColor to draw on the cleared buffer
        4. return while pushing adding 0x10 to the stack ptr **/

    __asm
    {
        push[esp + 10h]
        push[esp + 10h]
        push[esp + 10h]
        push[esp + 10h]

        call RendererClear_p

        call DrawBackTexture

        retn 10h
    }
}

__declspec(naked)
static void
___SetBackColor(void)
{
    __asm
    {
        push eax
        push[esp + 12]
        push[esp + 12]
        call rjSetBackColor
        add esp, 8
        pop eax
        retn
    }
}

#pragma warning( push )
#pragma warning( disable : 4409 )
__declspec(naked)
static void
___SetBackColorSingle(void)
{
    __asm
    {
        push eax
        push ecx
        push edx
        push esi

        movzx esi, dl
        push esi
        movzx esi, al
        push esi
        movzx esi, cl
        push esi

        call SetBackColor

        add esp, 12

        pop esi
        pop edx
        pop ecx
        pop eax
        retn
    }
}
#pragma warning( pop )

#pragma optimize("", on)

#define UnloadRELFile       FUNC_PTR(void, __cdecl, (void), 0x00454CC0)

static mt_hookinfo HookInfoUnloadRELFile[1];
static void
UnloadRELFileHook(void)
{
    FuncHookCall( HookInfoUnloadRELFile, UnloadRELFile() );

    rjSetBackColor(0, 0, 0);
}

/****** Set Backtex *****************************************************************************/
void
rjSetBackColor(Uint32 color1, Uint32 color2, Uint32 color3)
{
    _rj_back_surface_ = nullptr;

    _rj_back_vtx_[RJ_BACK_HI_L].bcol = color1;
    _rj_back_vtx_[RJ_BACK_HI_R].bcol = color2;
    _rj_back_vtx_[RJ_BACK_LO_L].bcol = color3;
    _rj_back_vtx_[RJ_BACK_LO_R].bcol = color3;
}

void
rjSetBackTexture(const NJS_TEXTUREH_VTX vtx[3])
{
    _rj_back_surface_ = _nj_curr_ctx_->texture;

    _rj_back_vtx_[RJ_BACK_HI_L].u    = vtx[0].u;
    _rj_back_vtx_[RJ_BACK_HI_L].v    = vtx[0].v;
    _rj_back_vtx_[RJ_BACK_HI_L].bcol = vtx[0].bcol;
    _rj_back_vtx_[RJ_BACK_HI_L].ocol = vtx[0].ocol;

    _rj_back_vtx_[RJ_BACK_HI_R].u    = vtx[1].u;
    _rj_back_vtx_[RJ_BACK_HI_R].v    = vtx[1].v;
    _rj_back_vtx_[RJ_BACK_HI_R].bcol = vtx[1].bcol;
    _rj_back_vtx_[RJ_BACK_HI_R].ocol = vtx[1].ocol;

    _rj_back_vtx_[RJ_BACK_LO_L].u    = vtx[2].u;
    _rj_back_vtx_[RJ_BACK_LO_L].v    = vtx[2].v;
    _rj_back_vtx_[RJ_BACK_LO_L].bcol = vtx[2].bcol;
    _rj_back_vtx_[RJ_BACK_LO_L].ocol = vtx[2].ocol;

    const Float gen_u = vtx[1].u + (vtx[2].u - vtx[0].u);
    const Float gen_v = vtx[1].v + (vtx[2].v - vtx[0].v);

    _rj_back_vtx_[RJ_BACK_LO_R].u    = gen_u;
    _rj_back_vtx_[RJ_BACK_LO_R].v    = gen_v;
    _rj_back_vtx_[RJ_BACK_LO_R].bcol = vtx[2].bcol;
    _rj_back_vtx_[RJ_BACK_LO_R].ocol = vtx[2].ocol;
}

/****** Init ************************************************************************************/
void
RJ_BackTextureInit(void)
{
    WritePointer(0x008B6FDC, ___RendererClearHook);

    WriteJump(0x00426540, ___SetBackColor);
    WriteJump(0x00426620, ___SetBackColorSingle);

    /** SOC SetBackColor calls **/
    KillCall(0x0043AA73); // King Boom Boo
    KillCall(0x0043AC81); // ^
    KillCall(0x0043BACF); // Wild Canyon
    KillCall(0x0043B4A7); // ^
    KillCall(0x0043AE09); // Pause
    KillCall(0x0043B2C4); // Unpause
    KillCall(0x0043B146); // Unk Menu

    /** Always reset back color on level exit **/
    FuncHook(HookInfoUnloadRELFile, UnloadRELFile, UnloadRELFileHook);

    // stop clearing render target (optimization)
    WriteNOP(0x00867B2B, 0x00867B30);
}
