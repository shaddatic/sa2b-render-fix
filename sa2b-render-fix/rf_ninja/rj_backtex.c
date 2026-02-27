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

/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* dx9ctrl                                                  */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** Back Texture ****************************************************************************/
#define BACK_DEPTH                  (0.f)         /* back texture/color z value                 */

/****** DX9 Flags *******************************************************************************/
#define DX9_CLEAR_SURFACE           (0x00000001)  /* clear the surface colors                   */
#define DX9_CLEAR_ZBUFFER           (0x00000002)  /* clear target z buffer                      */
#define DX9_CLEAR_STENCIL           (0x00000004)  /* clear stencil buffer                       */

/****** Clear Defaults **************************************************************************/
#define CLR_COLOR                   (0x00000000)  /* clear surface color                        */
#define CLR_DEPTH                   (0.f)         /* clear depth                                */
#define CLR_STENCIL                 (0x00)        /* clear stencil value                        */

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
/****** Magic Thiscall **************************************************************************/
#pragma optimize("", off)
static void
MagicClear(void* self, u32 flag, u32 color, f32 depth, u32 stencil)
{
    const pint fptr = 0x00867B20;

    __asm
    {
        push        [stencil]
        push        [depth]
        push        [color]
        push        [flag]
        mov ecx,    [self]

        call fptr
    }
}
#pragma optimize("", on)

/****** Draw Backtex ****************************************************************************/
static void
DrawBackTextureSub(void)
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
    vtx[0].z    = BACK_DEPTH;
    vtx[0].u    = _rj_back_vtx_[RJ_BACK_HI_L].u - uvh_off;
    vtx[0].v    = _rj_back_vtx_[RJ_BACK_HI_L].v;
    vtx[0].bcol = _rj_back_vtx_[RJ_BACK_HI_L].bcol;
    vtx[0].ocol = _rj_back_vtx_[RJ_BACK_HI_L].ocol;

    vtx[1].x    = 0.0f - pos_off;
    vtx[1].y    = 480.0f;
    vtx[1].z    = BACK_DEPTH;
    vtx[1].u    = _rj_back_vtx_[RJ_BACK_LO_L].u - uvh_off;
    vtx[1].v    = _rj_back_vtx_[RJ_BACK_LO_L].v;
    vtx[1].bcol = _rj_back_vtx_[RJ_BACK_LO_L].bcol;
    vtx[1].ocol = _rj_back_vtx_[RJ_BACK_LO_L].ocol;

    vtx[2].x    = 640.0f + pos_off;
    vtx[2].y    = 0.0f;
    vtx[2].z    = BACK_DEPTH;
    vtx[2].u    = _rj_back_vtx_[RJ_BACK_HI_R].u + uvh_off;
    vtx[2].v    = _rj_back_vtx_[RJ_BACK_HI_R].v;
    vtx[2].bcol = _rj_back_vtx_[RJ_BACK_HI_R].bcol;
    vtx[2].ocol = _rj_back_vtx_[RJ_BACK_HI_R].ocol;

    vtx[3].x    = 640.0f + pos_off;
    vtx[3].y    = 480.0f;
    vtx[3].z    = BACK_DEPTH;
    vtx[3].u    = _rj_back_vtx_[RJ_BACK_LO_R].u + uvh_off;
    vtx[3].v    = _rj_back_vtx_[RJ_BACK_LO_R].v;
    vtx[3].bcol = _rj_back_vtx_[RJ_BACK_LO_R].bcol;
    vtx[3].ocol = _rj_back_vtx_[RJ_BACK_LO_R].ocol;

    rjDrawTextureHEx(vtx, 4, FALSE);
}

static void
DrawBackColorSub(void)
{
    NJS_POLYGON_VTX vtx[4];

    const f32 pos_off = (GetDisplayRatio() - 1.0f) * 320.0f;

    vtx[0].x   = 0.0f - pos_off;
    vtx[0].y   = 0.0f;
    vtx[0].z   = BACK_DEPTH;
    vtx[0].col = _rj_back_vtx_[RJ_BACK_HI_L].bcol;

    vtx[1].x   = 0.0f - pos_off;
    vtx[1].y   = 480.0f;
    vtx[1].z   = BACK_DEPTH;
    vtx[1].col = _rj_back_vtx_[RJ_BACK_LO_L].bcol;

    vtx[2].x   = 640.0f + pos_off;
    vtx[2].y   = 0.0f;
    vtx[2].z   = BACK_DEPTH;
    vtx[2].col = _rj_back_vtx_[RJ_BACK_HI_R].bcol;

    vtx[3].x   = 640.0f + pos_off;
    vtx[3].y   = 480.0f;
    vtx[3].z   = BACK_DEPTH;
    vtx[3].col = _rj_back_vtx_[RJ_BACK_LO_R].bcol;

    rjDrawPolygon(vtx, 4, FALSE);
}

static void
ClearFrameHook(void)
{
    void* const rendev = *( (void**)0x01A557C0 );

    /** If the screen is fully faded out, just use black to stop a flicker **/
    if (FadeColor.argb.a == 0xFF)
    {
        MagicClear(rendev, DX9_CLEAR_SURFACE|DX9_CLEAR_ZBUFFER|DX9_CLEAR_STENCIL, CLR_COLOR, CLR_DEPTH, CLR_STENCIL);
        return;
    }

    /** If just a back color, and all the colors match, then use GPU clear as it's faster **/
    if ( !_rj_back_surface_ )
    {
        const u32 chk_color = _rj_back_vtx_[RJ_BACK_HI_L].bcol;

        if ( chk_color == _rj_back_vtx_[RJ_BACK_HI_R].bcol
        &&   chk_color == _rj_back_vtx_[RJ_BACK_LO_L].bcol )
        {
            MagicClear(rendev, DX9_CLEAR_SURFACE|DX9_CLEAR_ZBUFFER|DX9_CLEAR_STENCIL, chk_color,  CLR_DEPTH, CLR_STENCIL);
            return;
        }
    }

    /** Otherwise clear everything except the screen color, and apply back texture/color **/
    MagicClear(rendev, DX9_CLEAR_ZBUFFER|DX9_CLEAR_STENCIL, CLR_COLOR, CLR_DEPTH, CLR_STENCIL);

    DX9_SetZEnable(FALSE);
    DX9_SetZWrite(FALSE);

    if ( _rj_back_surface_ )
    {
        DrawBackTextureSub();
    }
    else
    {
        DrawBackColorSub();
    }

    DX9_SetZWrite(TRUE);
    DX9_SetZEnable(TRUE);
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
#pragma optimize("", off)
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
    mtHookInfoCall( HookInfoUnloadRELFile, UnloadRELFile() );

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

/****** Set Hooks *******************************************************************************/
static void
SetBackColor_WildCanyon(void)
{
    rjSetBackColor(0x3232AA, 0x3232AA, 0x3232AA);
}

/****** Init ************************************************************************************/
void
RJ_BackTextureInit(void)
{
    WriteNOP( 0x00433F58, 0x00433F74);
    WriteCall(0x00433F58, ClearFrameHook);

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
    mtHookFunc(HookInfoUnloadRELFile, UnloadRELFile, UnloadRELFileHook);

    // Add missing 'njSetBackColor' calls (inlined)
    WriteNOP( 0x006A2462, 0x006A2481);
    WriteCall(0x006A2462, SetBackColor_WildCanyon);
}
