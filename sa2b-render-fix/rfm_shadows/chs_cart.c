#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/camera.h>
#include <sa2b/sonic/njctrl.h>
#include <sa2b/sonic/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>
#include <rf_mdlutil.h>

#define GET_CARTWK(_tp)     ((CARTWK*)_tp->mwp)

typedef struct
{
    char gap0[8];
    Angle3 ang;
    NJS_POINT3 pos;
    char gap2[20];
    NJS_CNK_OBJECT* pObject;
    NJS_CNK_OBJECT* pFarObject;
    NJS_TEXLIST*    pTexlist;
    int headlights;
    b32 is_player;
    int character;
    int player_num;
    void* ptr1;
    char gap4[20];
    Angle angSlide;
    char gap5[132];
    Angle3 ang3;
    Angle3 ang2;
    char gap6[412];
    void* texp;
    int address_u;
    int address_v;
    int tes5;
    int min_filter;
    int mag_filter;
    int bank;
    __int32 stencil_data[1];
    void* stencil_tex;
    char gap7[28];
}
CARTWK;

#define PlayerCartSelected      DATA_ARY(s8, 0x0174B021, [2])

static NJS_CNK_OBJECT* CartObjectList[8][2];

static void
cartDisplayerMod(task* tp)
{
    CARTWK* const cwp = GET_CARTWK(tp);

    camcontwk* const camwk = cameraCurrentWork;

    NJS_POINT3 rel_pos = {
        .x = cwp->pos.x - camwk->pos.x,
        .y = cwp->pos.y - camwk->pos.y,
        .z = cwp->pos.z - camwk->pos.z,
    };

    const float fchk = (rel_pos.x * rel_pos.x) + (rel_pos.y * rel_pos.y) + (rel_pos.z * rel_pos.z);

    if (fchk > 25000000.0f)
        return;

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    njTranslate(NULL, cwp->pos.x, cwp->pos.y + 0.01f - 2.0f, cwp->pos.z);

    njRotateZ(NULL, cwp->ang.z);
    njRotateX(NULL, cwp->ang.x);
    njRotateY(NULL, cwp->ang.y + cwp->angSlide - 0x8000);

    njRotateZ(NULL, cwp->ang2.z + cwp->ang3.z);
    njRotateX(NULL, cwp->ang2.x + cwp->ang3.x);
    njRotateY(NULL, cwp->ang2.y + cwp->ang3.y);

    bool alt = false;

    if (cwp->is_player)
    {
        const int chnum = PlayerCartSelected[cwp->player_num];

        if (chnum < 0) //
            alt = true;
    }

    const NJS_CNK_OBJECT* const p_obj = CartObjectList[cwp->character][alt];

    switch (cwp->character)
    {
        case 0:
        {
            njRotateY(NULL, 0x4000);
            njCnkModDrawObject(p_obj);
            break;
        }
        case 1:
        case 2: case 3: case 4:
        case 5: case 6: case 7:
        {
            njCnkModDrawObject(p_obj);
            break;
        }
        case 8:
        {
            njScale(NULL, 5.0f, 1.0f, 5.0f);
            DrawBasicShadow();
            break;
        }
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

#define courseDisplayDisplayer      FUNC_PTR(void, __cdecl, (task*), 0x00623E10)

static hook_info HookInfoCourseDisplayDisplayer[1];
static void
courseDisplayDisplayerHook(task* tp)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    FuncHookCall( HookInfoCourseDisplayDisplayer, courseDisplayDisplayer(tp) );

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

void* CreateNoStencilTexture(void);

void
CHS_CartInit(void)
{
    WriteJump(0x0061CB80, cartDisplayerMod);
    WriteCall(0x0061C60F, CreateNoStencilTexture);

    FuncHook(HookInfoCourseDisplayDisplayer, courseDisplayDisplayer, courseDisplayDisplayerHook);

    /** Models **/
    CartObjectList[0][0] = RF_ChunkLoadObjectFile("cart/cart_tails_big_mod");
    CartObjectList[0][1] = CartObjectList[0][0];

    CartObjectList[1][0] = RF_ChunkLoadObjectFile("cart/cart_rouge_big_mod");
    CartObjectList[1][1] = CartObjectList[1][0];

    CartObjectList[2][0] = RF_ChunkLoadObjectFile("cart/cart_sonic_mod");
    CartObjectList[2][1] = RF_ChunkLoadObjectFile("cart/cart_sonic_alt_mod");

    CartObjectList[3][0] = RF_ChunkLoadObjectFile("cart/cart_knuckles_mod");
    CartObjectList[3][1] = RF_ChunkLoadObjectFile("cart/cart_knuckles_alt_mod");

    CartObjectList[4][0] = RF_ChunkLoadObjectFile("cart/cart_tails_mod");
    CartObjectList[4][1] = RF_ChunkLoadObjectFile("cart/cart_chao_mod");

    CartObjectList[5][0] = RF_ChunkLoadObjectFile("cart/cart_eggman_mod");
    CartObjectList[5][1] = RF_ChunkLoadObjectFile("cart/cart_eggman_alt_mod");

    CartObjectList[6][0] = RF_ChunkLoadObjectFile("cart/cart_shadow_mod");
    CartObjectList[6][1] = RF_ChunkLoadObjectFile("cart/cart_shadow_alt_mod");

    CartObjectList[7][0] = RF_ChunkLoadObjectFile("cart/cart_rouge_mod");
    CartObjectList[7][1] = RF_ChunkLoadObjectFile("cart/cart_eggrobo_mod");

    RF_CnkObjectReduceDuplicates((NJS_CNK_OBJECT**)CartObjectList, 8*2);
}
