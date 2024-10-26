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
njCnkNullDrawModel(const NJS_CNK_MODEL* model)
{
    return 0;
}

void
njCnkNullDrawObject(const NJS_CNK_OBJECT* object)
{
    njCnkTransformObject(object, njCnkNullDrawModel);
}

void
njCnkAnimateMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, float frame)
{
    njDrawMotion(object, motion, frame, njCnkNullDrawModel);
}

void
njCnkAnimateMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, float frame)
{
    njDrawMotionLink(object, motion_link, frame, njCnkNullDrawModel);
}

void
AnimateMotion(const ANY_OBJECT* pObject, const MOTION_CTRL* pMtnCtrl)
{
    if (pMtnCtrl->flag & 0x02)
    {
        NJS_MOTION_LINK motion_link;

        motion_link.motion[0] = pMtnCtrl->minfo[0].pMotion;
        motion_link.frame[0]  = pMtnCtrl->minfo[0].frame;

        motion_link.motion[1] = pMtnCtrl->minfo[1].pMotion;
        motion_link.frame[1]  = pMtnCtrl->minfo[1].frame;
        
        njCnkAnimateMotionLink(pObject, &motion_link, pMtnCtrl->ratio);
    }
    else
        njCnkAnimateMotion(pObject, pMtnCtrl->minfo[0].pMotion, pMtnCtrl->minfo[0].frame);
}

void
rjDrawTextureEx(const NJS_TEXTURE_VTX* polygon, Int count, Int trans)
{
    TexExCount = count;
    njDrawTextureEx(polygon, 4, trans);
    TexExCount = 4;
}

void
rjDrawPolygon2D(const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr)
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
