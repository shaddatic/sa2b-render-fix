/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* WriteJump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_magic.h>           /* rf_magic                                         */
#include <rf_light.h>           /* chunk light                                      */

/****** Self ************************************************************************/
#include <rf_ninja/rj_internal.h>           /* parent & siblings                    */
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* self                                 */

/************************/
/*  Game References     */
/************************/
/****** Shadow Map ******************************************************************/
#define _gj_shadow_tex_callback_    FUNC_REF(void, __cdecl, (s32), 0x01A55828)

#define _gj_shadow_tex_num_         DATA_REF(u8, 0x01934758)

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
rjCnkBeginShadowTex(void)
{
    if ( _nj_control_3d_flag_ & 0x80000 )
    {
        NJS_MATRIX m = *_nj_curr_matrix_;

        njInvertMatrix(&m);

        gjStartVertex3D(&m, 0);

        if (_gj_shadow_tex_callback_) _gj_shadow_tex_callback_(1);

        _rj_cnk_shadow_tex_ = _gj_shadow_tex_num_ + 1;
    }
    else
    {
        _rj_cnk_shadow_tex_ = 0;
    }
}

void
rjCnkEndShadowTex(void)
{
    _rj_cnk_shadow_tex_ = 0;
}

/****** Other Draws *****************************************************************/
static Sint32
CnkDrawModel_NoClip(const NJS_CNK_MODEL* model)
{
    NJS_CNK_MODEL mdl = *model;

    mdl.r = -1.f;

    return rjCnkDrawModel( &mdl );
}

#if 0

#define chAttrEnable                    DATA_REF(Bool, 0x01AED2CC)

static void
CalcVlistColorCh(NJS_BGRA* dst, const NJS_BGRA* src)
{
    // RGBA (Chao) -> ARGB (Cnk)
    dst->a = src->b;
    dst->r = src->a;
    dst->g = src->r;
    dst->b = src->g;
}

static Sint32
CnkDrawModel_ChDraw(const NJS_CNK_MODEL* model)
{
    if ( !chAttrEnable )
    {
        rjCnkSetVListColCallback( CalcVlistColorCh );

        const Sint32 ret = rjCnkDrawModel( model );

        rjCnkSetVListColCallback( nullptr );

        return ret;
    }
    else
    {
        return CNK_RETN_OK;
    }
}

#endif

/****** Cnk Init ********************************************************************/
void
RFD_ChunkInit(void)
{
    /** RF Chunk draw functions **/
    WriteRetn(0x0042D340); // begin draw

    WriteJump(0x0042D500, CnkDrawModel_NoClip); // CnkDrawModelSub
//  WriteJump(0x0056DDD0, CnkDrawModel_ChDraw);

    WriteJump(0x0042EB30, rjCnkTransformObject);

    // fix shape motion not calling motion callback
    WriteJump(0x00784890, rjCnkPushPopShape);
    WriteJump(0x00784E70, rjCnkPushPopShapeLink);
}
