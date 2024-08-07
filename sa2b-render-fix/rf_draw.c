/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/writemem.h>  /* WriteData, WriteJump, WritePointer                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Utility *********************************************************************/
#include <sa2b/util/anyobj.h>   /* ANY_OBJECT                                       */

/****** Game ************************************************************************/
#include <sa2b/sonic/motion.h>    /* MOTION_CTRL                                      */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_mod.h>             /* RFMOD_PushPolygon                                */

/****** Self ************************************************************************/
#include <rf_draw.h>            /* self                                             */

/************************/
/*  Constants           */
/************************/
/****** DrawTextureEx ***************************************************************/
#define TexExCount          DATA_REF(int32_t, 0x0077F6BF)

/****** DrawPolygon2D ***************************************************************/
#define Poly2DN             DATA_REF(int32_t, 0x00490FA8)

/************************/
/*  Source              */
/************************/
int 
njCnkNullDrawModel(NJS_CNK_MODEL* model)
{
    return 0;
}

void
njCnkNullDrawObject(NJS_CNK_OBJECT* object)
{
    njCnkTransformObject(object, njCnkNullDrawModel);
}

void
njCnkAnimateMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, float frame)
{
    njDrawMotion(object, motion, frame, njCnkNullDrawModel);
}

void
njCnkAnimateMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame)
{
    njDrawMotionLink(object, motion_link, frame, njCnkNullDrawModel);
}

void
AnimateMotion(ANY_OBJECT* pObject, MOTION_CTRL* pMtnCtrl)
{
    if (pMtnCtrl->flag & 0x02)
    {
        NJS_MOTION_LINK motion_link;

        NJS_MOTION* motion_one = pMtnCtrl->minfo[0].pMotion;
        motion_link.frame[0] = pMtnCtrl->minfo[0].frame;
        float frame_two = pMtnCtrl->minfo[1].frame;
        motion_link.motion[0] = motion_one;
        NJS_MOTION* motion_two = pMtnCtrl->minfo[1].pMotion;
        motion_link.frame[1] = frame_two;
        float frame = pMtnCtrl->ratio;
        motion_link.motion[1] = motion_two;
        njCnkAnimateMotionLink(pObject, &motion_link, frame);
    }
    else
        njCnkAnimateMotion(pObject, pMtnCtrl->minfo[0].pMotion, pMtnCtrl->minfo[0].frame);
}

int32_t
njCnkModDrawModel(NJS_CNK_MODEL* model)
{
    if (_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if (model->r > 0 && njCnkModelClip(model))
            return 1;

    Sint32* vlist = model->vlist;

    int type = ((uint8_t*)vlist)[0];

    if (type != NJD_CV)
        return type;

    ++vlist;

    const int offst = ((uint16_t*)vlist)[0];
    const int nbidx = ((uint16_t*)vlist)[1];

    ++vlist;

    NJS_POINT3* base_vtx_buf = (NJS_POINT3*)_nj_vertex_buf_;

    NJS_POINT3* vtx_buf = &base_vtx_buf[offst];

    njCalcPoints(NULL, (NJS_POINT3*)vlist, vtx_buf, nbidx);

    Sint16* plist = model->plist;

    type = plist[0];

    ++plist;

    while (type == NJD_CO_P3)
    {
        int size = ((uint16_t*)plist)[0];
        int nbpoly = plist[1] & 0x3FFF;

        plist += 2;

        RFMOD_PushPolygon(plist, base_vtx_buf, nbpoly);

        plist += size - 1;

        type = plist[0];
    }

    return 0;
}

void
njCnkModDrawObject(NJS_CNK_OBJECT* object)
{
    njCnkTransformObject(object, njCnkModDrawModel);
}

void
njCnkModDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, float frame)
{
    njDrawMotion(object, motion, frame, njCnkModDrawModel);
}

void
njCnkModDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame)
{
    njDrawMotionLink(object, motion_link, frame, njCnkModDrawModel);
}

void
rjDrawTextureEx(NJS_TEXTURE_VTX* polygon, Int count, Int trans)
{
    TexExCount = count;
    njDrawTextureEx(polygon, 4, trans);
    TexExCount = 4;
}

void
rjDrawPolygon2D(NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr)
{
    Poly2DN = n;
    njDrawPolygon2D(p, 4, pri, attr);
    Poly2DN = 4;
}

/****** Init ************************************************************************/
void
RF_DrawInit(void)
{
    /** Allow 'count' argument to be writeable **/
    WriteData(&TexExCount, 4, int32_t);

    /** Allow 'n' argument to be writeable **/
    WriteData(&Poly2DN, 4, int32_t);
}
