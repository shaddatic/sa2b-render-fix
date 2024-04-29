#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>

typedef union
{
    uint8_t ub[4];
    int8_t sb[4];
    uint16_t us[2];
    int16_t ss[2];
    uint32_t ui;
    int32_t si;
    float32_t f;
}
GLOBAL_BUFFER;

#define GlobalBuffer        DataAry(GLOBAL_BUFFER , 0x01DEFE20, [1])
#define object_car_mod      DataAry(NJS_CNK_OBJECT, 0x00B4D254, [1])

static void
TruckTranslateModVertex(float sizeX, float sizeZ, Angle3* pAng)
{
    NJS_VECTOR inpts[4];
    NJS_VECTOR outpts[4];

    inpts[2].x = sizeX;
    inpts[0].x = -inpts[2].x;
    inpts[0].y = 30.0f;
    inpts[0].z = -sizeZ;
    inpts[1].y = 130.0f;
    inpts[1].z = sizeZ + -900.0f;
    inpts[2].y = 30.0f;
    inpts[3].y = 130.0f;
    inpts[1].x = inpts[0].x;
    inpts[2].z = inpts[0].z;
    inpts[3].x = inpts[2].x;
    inpts[3].z = inpts[1].z;

    njPushMatrix(&_nj_unit_matrix_);

    njRotateY(NULL, pAng->y);
    njRotateX(NULL, pAng->x);
    njRotateZ(NULL, pAng->z);
    njCalcPoints(NULL, inpts, outpts, arylen(inpts));

    njPopMatrixEx();
    njPushMatrix(&_nj_unit_matrix_);

    NJS_POINT3 point = { 0.0f, -200.0f, -100.0f };

    njRotateY(0, pAng->y);
    njCalcPoint(NULL, &point, &point);

    njPopMatrixEx();

    NJS_CNK_MODEL* car_mod = object_car_mod->model;

    GlobalBuffer[0].si = car_mod->vlist[0];
    GlobalBuffer[1].si = car_mod->vlist[1];

    float* verts_src = (float*)&car_mod->vlist[2];
    float* verts_dst = &GlobalBuffer[2].f;

    int nb_vert = GlobalBuffer[1].us[1];

    int hi_idx = 0;
    int lo_idx = 0;

    while (nb_vert--)
    {
        float new_y;
        float new_z;
        float new_x;

        if (0.0f < verts_src[1])
        {
            new_x = outpts[hi_idx].x;
            new_z = outpts[hi_idx].z;
            new_y = outpts[hi_idx].y;

            ++hi_idx;
        }
        else
        {
            new_x = (outpts[lo_idx].x - point.x) * 0.12f + point.x + 100.0f;
            new_z = (outpts[lo_idx].z - point.z) * 0.12f + point.z + 100.0f;
            new_y = point.y;

            ++lo_idx;
        }

        verts_dst[0] = new_x;
        verts_dst[1] = new_y;
        verts_dst[2] = new_z;

        verts_src += 3;
        verts_dst += 3;

        hi_idx &= 3u;
        lo_idx &= 3u;
    }

    int v28 = *(int*)verts_src;
    *(int*)verts_dst = v28;

    while (v28 != NJD_CE)
    {
        ; // Code trap; can probably be removed but it's doing no harm
    }
}

static void
DrawTruckShadow(float sizeX, float sizeZ, Angle3* pAng)
{
    TruckTranslateModVertex(sizeX, sizeZ, pAng);

    NJS_CNK_MODEL* car_model = object_car_mod->model;

    const float r = sqrtf((sizeX * sizeX) + (sizeZ * sizeZ));

    NJS_CNK_MODEL model = {
        .vlist = (Sint32*)GlobalBuffer,
        .plist = car_model->plist,
        .center = car_model->center,
        .r = (r * 2) + 300.0f
    };

    njCnkModDrawModel(&model);
}

static void
ObjectTruckDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ANYWK* const trkwp = TO_ANYWK(tp->mwp);

    njPushMatrixEx();

    const float trans_y = (trkwp[13].work.f[2] + 10.0f) + twp->pos.y - 5.0f + trkwp[20].work.f[1];

    njTranslate(NULL, twp->pos.x, trans_y, twp->pos.z);
    DrawTruckShadow(70.0f, 60.0f, &twp->ang);

    njPopMatrixEx();
}

void
CHS_TruckInit(void)
{
    WriteJump(0x005E85B0, ObjectTruckDisplayerMod);
    KillCall(0x005E4CE7); // Kill SetStencilInfo
}
