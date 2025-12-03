/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Utility *********************************************************************************/
#include <samt/util/anyobj.h>       /* ANY_OBJECT                                               */

/****** Game ************************************************************************************/
#include <samt/sonic/motion.h>      /* MOTION_CTRL                                              */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* rf ninja                                                 */

/****** Self ************************************************************************************/
#include <rfu_draw.h>               /* self                                                     */

/********************************/
/*  Source                      */
/********************************/
/****** Animate *********************************************************************************/
static Sint32
njCnkNullDrawModel(const NJS_CNK_MODEL* model)
{
    return 0;
}

void
njCnkAnimateMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    njDrawMotion(object, motion, frame, njCnkNullDrawModel);
}

void
njCnkAnimateMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame)
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
