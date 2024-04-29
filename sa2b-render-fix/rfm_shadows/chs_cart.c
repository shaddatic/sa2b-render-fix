#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/camera.h>
#include <sa2b/src/njctrl.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>

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
    int unk0;
    bool32_t is_player;
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

NJS_CNK_OBJECT* object_cart_miles_mod;
NJS_CNK_OBJECT* object_cart_rouge_mod;
NJS_CNK_OBJECT* object_cart_mod;

static void
cartDisplayerMod(TASK* tp)
{
    CARTWK* const cwp = GET_CARTWK(tp);

    CAMERA_CONTROL_WORK* const camwk = cameraCurrentWork;

    NJS_POINT3 rel_pos = {
        .x = cwp->pos.x - camwk->campos.x,
        .y = cwp->pos.y - camwk->campos.y,
        .z = cwp->pos.z - camwk->campos.z,
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

    switch (cwp->character) {
    case 0:
        njRotateY(NULL, 0x4000);
        njCnkModDrawObject(object_cart_miles_mod);
        break;

    case 1:
        njCnkModDrawObject(object_cart_rouge_mod);
        break;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        njCnkModDrawObject(object_cart_mod);
        break;

    case 8:
        njScale(NULL, 5.0f, 1.0f, 5.0f);
        DrawBasicShadow();
        break;
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

#define courseDisplayDisplayer      FuncPtr(void, __cdecl, (TASK*), 0x00623E10)

static hook_info* HookInfoCourseDisplayDisplayer;
static void
courseDisplayDisplayerHook(TASK* tp)
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

    HookInfoCourseDisplayDisplayer = FuncHook(courseDisplayDisplayer, courseDisplayDisplayerHook);

    /** Models **/
    object_cart_miles_mod = RF_ChunkLoadObjectFile("cart_miles_mod");
    object_cart_rouge_mod = RF_ChunkLoadObjectFile("cart_rouge_mod");
    object_cart_mod       = RF_ChunkLoadObjectFile("cart_mod");
}
