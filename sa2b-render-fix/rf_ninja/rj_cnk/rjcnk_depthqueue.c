/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* cnkfuncmd                                            */

/****** Self ************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                    */

/************************/
/*  Source              */
/************************/
/****** Begin ***********************************************************************/
void
rjCnkBeginDepthQueue(const NJS_CNK_MODEL* model)
{
    if ( (_nj_control_3d_flag_ & NJD_CONTROL_3D_DEPTH_QUEUE) && (RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT) )
    {
        NJS_POINT3 pt;
        njCalcPoint(NULL, &model->center, &pt);

        // if z + radius is further away that the depth queue near value (Z is negative)

        _rj_cnk_context_.depthq = ( (pt.z - model->r) < _rj_depth_queue_near_ ) ? RJ_CNK_DQ_ON : RJ_CNK_DQ_NEAR;
    }
    else
    {
        _rj_cnk_context_.depthq = RJ_CNK_DQ_OFF;
    }
}

/****** Calc Vertex *****************************************************************/
void
rjCnkCalculateDepthQueue(const CNK_VERTEX_HEAD* vhead, RJS_VERTEX_BUF* vbuf)
{
    if ( _rj_cnk_context_.depthq == RJ_CNK_DQ_OFF )
    {
        return;
    }

    /** Get/Set color attr **/

    Bool has_color;

    if ( _rj_cnk_context_.vattr & RJD_CVF_COLOR )
    {
        has_color = true;
    }
    else // no color attr
    {
        if ( _rj_cnk_context_.depthq != RJ_CNK_DQ_ON )
        {
            return; // if not 'NEAR' stop, alpha is 100% already
        }

        _rj_cnk_context_.vattr |= RJD_CVF_COLOR;

        has_color = false;
    }

    /** depth queue attributes **/

    const Float dq_near = _rj_depth_queue_near_;
    const Float dq_far  = _rj_depth_queue_far_;

    const Float dq_diff = dq_far - dq_near;

    const Float dq_mul = 1.f / (dq_diff * 2.f); // we need the range to be 0.0 ~ 0.5

    /** Set "depth queue" **/

    const int nb_vtx = vhead->nbindeces;

    RJS_VERTEX_BUF* restrict p_buf = vbuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        if ( p_buf->pos.z < dq_near )
        {
            if ( p_buf->pos.z <= dq_far )
            {
                p_buf->col.a = 0.f;
            }
            else
            {
                p_buf->col.a = ( dq_diff - (p_buf->pos.z - dq_near) ) * dq_mul;
            }
        }
        else
        {
            p_buf->col.a = 1.f;
        }

        if ( !has_color )
        {
            p_buf->col.r = 1.f;
            p_buf->col.g = 1.f;
            p_buf->col.b = 1.f;
        }

        ++p_buf;
    }
}

void
rjCnkCalculateDepthQueueNF(const CNK_VERTEX_HEAD* vhead, RJS_VERTEX_BUF* vbuf)
{
    if ( _rj_cnk_context_.depthq == RJ_CNK_DQ_OFF )
    {
        return;
    }

    if ( vhead->wstat != CNK_WEIGHT_END )
    {
        return;
    }

    /** Get/Set color and size attr **/

    Bool has_color;

    size_t ln_vtx;    // length of vertex
    size_t off_index; // p_vtx->i offset

    switch ( _rj_cnk_context_.vattr )
    {
        case RJD_CVT_P:
        {
            ln_vtx    = sizeof(CNK_VERTEX_NF) / sizeof(Uint16);
            off_index = sizeof(NJS_POINT3)    / sizeof(Uint16);

            if ( _rj_cnk_context_.depthq != RJ_CNK_DQ_ON )
            {
                return; // if not 'NEAR' stop, alpha is 100% already
            }

            _rj_cnk_context_.vattr |= RJD_CVF_COLOR;

            has_color = false;
            break;
        }
        case RJD_CVT_PN:
        {
            ln_vtx    = sizeof(CNK_VERTEX_VN_NF) / sizeof(Uint16);
            off_index = (sizeof(NJS_POINT3) * 2) / sizeof(Uint16);

            if ( _rj_cnk_context_.depthq != RJ_CNK_DQ_ON )
            {
                return; // if not 'NEAR' stop, alpha is 100% already
            }

            _rj_cnk_context_.vattr |= RJD_CVF_COLOR;

            has_color = false;
            break;
        }
        case RJD_CVT_PC:
        {
            ln_vtx    = sizeof(CNK_VERTEX_NF_D8) / sizeof(Uint16);
            off_index = sizeof(NJS_POINT3)       / sizeof(Uint16);

            has_color = true;
            break;
        }
        default:
        {
            return;
        }
    }

    /** depth queue attributes **/

    const Float dq_near = _rj_depth_queue_near_;
    const Float dq_far  = _rj_depth_queue_far_;

    const Float dq_diff = dq_far - dq_near;

    const Float dq_mul = 1.f / (dq_diff * 2.f); // we need the range to be 0.0 ~ 0.5

    /** Set "depth queue" **/

    const int    nb_vtx = vhead->nbindeces;
    const Uint16* p_vtx = (void*) vhead->d;

    for (int i = 0; i < nb_vtx; ++i)
    {
        RJS_VERTEX_BUF* restrict p_buf = &vbuf[ p_vtx[off_index] ];

        if ( p_buf->pos.z < dq_near )
        {
            if ( p_buf->pos.z <= dq_far )
            {
                p_buf->col.a = 0.f;
            }
            else
            {
                p_buf->col.a = ( dq_diff - (p_buf->pos.z - dq_near) ) * dq_mul;
            }
        }
        else
        {
            p_buf->col.a = 1.f;
        }

        if ( !has_color )
        {
            p_buf->col.r = 1.f;
            p_buf->col.g = 1.f;
            p_buf->col.b = 1.f;
        }

        p_vtx += ln_vtx;
    }
}
