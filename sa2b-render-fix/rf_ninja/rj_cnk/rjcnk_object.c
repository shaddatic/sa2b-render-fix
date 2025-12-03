/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* render state                                             */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                                */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Common **********************************************************************************/
#define _nj_cnk_rotbase_matrix_     DATA_REF(NJS_MATRIX, 0x01934AC0)

/********************************/
/*  Source                      */
/********************************/
/****** Common **********************************************************************************/
static inline void
___rjCnkObjectRotateBase(void)
{
    njGetMatrix(&_nj_cnk_rotbase_matrix_);
}

static inline void
___rjCnkObjectRotateSet(void)
{
    NJS_MATRIX* m = _nj_curr_matrix_;

    m->m[0][0] = _nj_cnk_rotbase_matrix_.m[0][0];
    m->m[0][1] = _nj_cnk_rotbase_matrix_.m[0][1];
    m->m[0][2] = _nj_cnk_rotbase_matrix_.m[0][2];
    m->m[1][0] = _nj_cnk_rotbase_matrix_.m[1][0];
    m->m[1][1] = _nj_cnk_rotbase_matrix_.m[1][1];
    m->m[1][2] = _nj_cnk_rotbase_matrix_.m[1][2];
    m->m[2][0] = _nj_cnk_rotbase_matrix_.m[2][0];
    m->m[2][1] = _nj_cnk_rotbase_matrix_.m[2][1];
    m->m[2][2] = _nj_cnk_rotbase_matrix_.m[2][2];
}

/****** Draw Object *****************************************************************************/
void
rjCnkTransformObject(NJS_CNK_OBJECT* object, Sint32(*callback)(NJS_CNK_MODEL* model))
{
    NJS_CNK_OBJECT* p_obj = object;

    do
    {
        const Uint32 evals = p_obj->evalflags;

        if ( evals & NJD_EVAL_ROTATE_BASE )
        {
            ___rjCnkObjectRotateBase();
        }

        Sint32 mdlret = CNK_RETN_OK;

        if ( ( evals & (NJD_EVAL_UNIT_POS|NJD_EVAL_UNIT_ANG|NJD_EVAL_UNIT_SCL) ) == (NJD_EVAL_UNIT_POS|NJD_EVAL_UNIT_ANG|NJD_EVAL_UNIT_SCL) )
        {
            if ( _rj_cnk_object_callback_ )
            {
                _rj_cnk_object_callback_( p_obj );
            }

            if ( !(evals & NJD_EVAL_HIDE) )
            {
                mdlret = callback( p_obj->model );
            }

            if ( !(evals & NJD_EVAL_BREAK) && (!(evals & NJD_EVAL_CLIP) || mdlret == CNK_RETN_OK) )
            {
                rjCnkTransformObject( p_obj->child, callback );
            }
        }
        else // not all unit flags
        {
            njPushMatrixEx();

            if ( !(evals & NJD_EVAL_UNIT_POS) )
            {
                njTranslateEx2( p_obj->pos );
            }

            if ( !(evals & NJD_EVAL_UNIT_ANG) )
            {
                if ( evals & NJD_EVAL_ROTATE_SET )
                {
                    ___rjCnkObjectRotateSet();
                }
                else if ( evals & NJD_EVAL_QUATERNION )
                {
                    njQuaternionEx2( p_obj->re_quat, (Float*) p_obj->ang );
                }
                else
                {
                    njRotateEx( p_obj->ang, evals & NJD_EVAL_ZXY_ANG );
                }
            }

            if ( !(evals & NJD_EVAL_UNIT_SCL) )
            {
                njScaleEx2( p_obj->scl );
            }

            if ( _rj_cnk_object_callback_ )
            {
                _rj_cnk_object_callback_( p_obj );
            }

            if ( p_obj->model && !(evals & NJD_EVAL_HIDE) )
            {
                mdlret = callback( p_obj->model );
            }

            if ( !(evals & NJD_EVAL_BREAK) && (!(evals & NJD_EVAL_CLIP) || mdlret == CNK_RETN_OK) )
            {
                rjCnkTransformObject( p_obj->child, callback );
            }

            njPopMatrixEx();
        }

        p_obj = p_obj->sibling;
    }
    while ( p_obj );
}

/****** Draw Motion *****************************************************************************/
void
rjCnkTransformMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame, Sint32(*callback)(NJS_CNK_MODEL*))
{
    njDrawMotion(object, motion, frame, callback);
}

void
rjCnkTransformMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*))
{
    njDrawMotionLink(object, motion_link, rate, callback);
}

/****** Draw Shape Motion ***********************************************************************/
void
rjCnkTransformShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame, Float sframe, Sint32(*callback)(NJS_CNK_MODEL*))
{
    njDrawShapeMotion(object, motion, shape, frame, sframe, callback);
}

void
rjCnkTransformShapeMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*))
{
    njDrawShapeLink(object, motion_link, shape_link, rate, callback);
}

/****** Draw Big Endian *************************************************************************/
void
rjCnkTransformShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame, Float sframe, Sint32(*callback)(NJS_CNK_MODEL*))
{
    /** Big endian shape motion draw **/

    njDrawShapeMotionBE(object, motion, shape, frame, sframe, callback);
}

void
rjCnkTransformShapeMotionLinkBE(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*))
{
    /** Big endian shape link draw **/

    njDrawShapeLinkBE(object, motion_link, shape_link, rate, callback);
}
