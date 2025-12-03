#include <samt/core.h>
#include <samt/memory.h>
#include <samt/writemem.h>
#include <samt/writeop.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/camera.h>
#include <samt/sonic/njctrl.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_samdl.h>
#include <rf_ninja.h>
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_mdlutil.h>

/** RF Util **/
#include <rfu_draw.h>

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

#define SQR(x)          ((x)*(x))

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

    if (fchk > SQR(5000.f))
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    bool alt;

    const NJS_POINT3* p_pos;

    if ( cwp->is_player )
    {
        const int chnum = PlayerCartSelected[cwp->player_num];

        alt = (chnum < 0);

        p_pos = &cwp->pos;
    }
    else
    {
        alt = false;

        p_pos = &tp->twp->pos;
    }

    njPushMatrixEx();

    njTranslate(NULL, p_pos->x, p_pos->y + 0.01f - 2.0f, p_pos->z);

    njRotateZ(NULL, cwp->ang.z);
    njRotateX(NULL, cwp->ang.x);
    njRotateY(NULL, cwp->ang.y + cwp->angSlide - 0x8000);

    njRotateZ(NULL, cwp->ang2.z + cwp->ang3.z);
    njRotateX(NULL, cwp->ang2.x + cwp->ang3.x);
    njRotateY(NULL, cwp->ang2.y + cwp->ang3.y);

    NJS_CNK_OBJECT* const p_obj = CartObjectList[cwp->character][alt];

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

static mt_hookinfo HookInfoCourseDisplayDisplayer[1];
static void
courseDisplayDisplayerHook(task* tp)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    FuncHookCall( HookInfoCourseDisplayDisplayer, courseDisplayDisplayer(tp) );

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

void* CreateNoStencilTexture(void);

#define ARY_X2(a, b)         ((a*2)+b)

void
CHS_CartInit(void)
{
    WriteJump(0x0061CB80, cartDisplayerMod);
    WriteCall(0x0061C60F, CreateNoStencilTexture);

    FuncHook(HookInfoCourseDisplayDisplayer, courseDisplayDisplayer, courseDisplayDisplayerHook);

    RFS_SAMDL mdl_list[8 * 2] =
    {
        { .puInPath = "cart/cart_tails_big_mod.sa2mdl" },
        { .puInPath = nullptr },

        { .puInPath = "cart/cart_rouge_big_mod.sa2mdl" },
        { .puInPath = nullptr },

        { .puInPath = "cart/cart_sonic_mod.sa2mdl" },
        { .puInPath = "cart/cart_sonic_alt_mod.sa2mdl" },

        { .puInPath = "cart/cart_knuckles_mod.sa2mdl" },
        { .puInPath = "cart/cart_knuckles_alt_mod.sa2mdl" },

        { .puInPath = "cart/cart_tails_mod.sa2mdl" },
        { .puInPath = "cart/cart_chao_mod.sa2mdl" },

        { .puInPath = "cart/cart_eggman_mod.sa2mdl" },
        { .puInPath = "cart/cart_eggman_alt_mod.sa2mdl" },

        { .puInPath = "cart/cart_shadow_mod.sa2mdl" },
        { .puInPath = "cart/cart_shadow_alt_mod.sa2mdl" },

        { .puInPath = "cart/cart_rouge_mod.sa2mdl" },
        { .puInPath = "cart/cart_eggrobo_mod.sa2mdl" },
    };

    RF_GetSAModelList( mdl_list, ARYLEN(mdl_list), SAMDL_CHUNK );

#pragma warning(push)
#pragma warning(disable : 6011) // annoying warning

    /** Models **/
    CartObjectList[0][0] = mdl_list[ARY_X2(0, 0)].pOutSamdl->pChunk;
//  CartObjectList[0][1] = mdl_list[ARY_X2(0, 1)].pOutSamdl->pChunk;

    CartObjectList[1][0] = mdl_list[ARY_X2(1, 0)].pOutSamdl->pChunk;
//  CartObjectList[1][1] = mdl_list[ARY_X2(1, 0)].pOutSamdl->pChunk;

    CartObjectList[2][0] = mdl_list[ARY_X2(2, 0)].pOutSamdl->pChunk;
    CartObjectList[2][1] = mdl_list[ARY_X2(2, 1)].pOutSamdl->pChunk;

    CartObjectList[3][0] = mdl_list[ARY_X2(3, 0)].pOutSamdl->pChunk;
    CartObjectList[3][1] = mdl_list[ARY_X2(3, 1)].pOutSamdl->pChunk;

    CartObjectList[4][0] = mdl_list[ARY_X2(4, 0)].pOutSamdl->pChunk;
    CartObjectList[4][1] = mdl_list[ARY_X2(4, 1)].pOutSamdl->pChunk;

    CartObjectList[5][0] = mdl_list[ARY_X2(5, 0)].pOutSamdl->pChunk;
    CartObjectList[5][1] = mdl_list[ARY_X2(5, 1)].pOutSamdl->pChunk;

    CartObjectList[6][0] = mdl_list[ARY_X2(6, 0)].pOutSamdl->pChunk;
    CartObjectList[6][1] = mdl_list[ARY_X2(6, 1)].pOutSamdl->pChunk;

    CartObjectList[7][0] = mdl_list[ARY_X2(7, 0)].pOutSamdl->pChunk;
    CartObjectList[7][1] = mdl_list[ARY_X2(7, 1)].pOutSamdl->pChunk;

#pragma warning(pop)
}
