/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_light.h>               /* lights                                                   */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                                */

/********************************/
/*  Forward Decls               */
/********************************/
/****** Vlist Callback *************************************************************************/
void    rjCnkCalcVlistPosition( NJS_POINT3* dst, const NJS_POINT3* src );
void    rjCnkCalcVlistNormal(   NJS_VECTOR* dst, const NJS_VECTOR* src );
void    rjCnkCalcVlistColor(    NJS_ARGB*   dst, const NJS_ARGB*   src );
void    rjCnkCalcVlistSpecular( NJS_ARGB*   dst, const NJS_ARGB*   src );

/****** Plist Callback *************************************************************************/
Sint16  rjCnkGetTextureNum( Sint16 n );
Uint32  rjCnkGetMaterial( NJS_BGRA dst[RJ_NB_CMC], const NJS_BGRA src[RJ_NB_CMC], Uint32 flag );

/********************************/
/*  Extern Data                 */
/********************************/
/****** UV Offset *******************************************************************************/
RJS_UV _rj_cnk_uv_scroll_;
RJS_UV _rj_cnk_env_scroll_;

/****** Obj/Mdl Callback ************************************************************************/
RJF_CNK_OBJ* _rj_cnk_object_callback_;
RJF_CNK_MDL* _rj_cnk_model_callback_;

/****** Plist Callback **************************************************************************/
RJF_CNK_PLIST_TNUM* _rj_cnk_texture_callback_  = rjCnkGetTextureNum;
RJF_CNK_PLIST_MCOL* _rj_cnk_material_callback_ = rjCnkGetMaterial;

/****** Vlist Callback **************************************************************************/
RJF_CNK_VLIST_POS* _rj_cnk_vlist_pfunc_ = rjCnkCalcVlistPosition;
RJF_CNK_VLIST_NRM* _rj_cnk_vlist_nfunc_ = rjCnkCalcVlistNormal;
RJF_CNK_VLIST_COL* _rj_cnk_vlist_cfunc_ = rjCnkCalcVlistColor;
RJF_CNK_VLIST_SPC* _rj_cnk_vlist_sfunc_ = rjCnkCalcVlistSpecular;

/********************************/
/*  Source                      */
/********************************/
/****** Default Vlist Callbacks *****************************************************************/
static void
rjCnkCalcVlistPosition(NJS_POINT3* dst, const NJS_POINT3* src)
{
    njCalcPoint(NULL, src, dst);
}

static void
rjCnkCalcVlistNormal(NJS_VECTOR* dst, const NJS_VECTOR* src)
{
    njCalcVector(NULL, src, dst);
}

static void
rjCnkCalcVlistColor(NJS_ARGB* dst, const NJS_ARGB* src)
{
    *dst = *src;
}

static void
rjCnkCalcVlistSpecular(NJS_ARGB* dst, const NJS_ARGB* src)
{
    *dst = *src;
}

/****** Default Plist Callbacks *****************************************************************/
static Sint16
rjCnkGetTextureNum(Sint16 n)
{
    return n;
}

static Uint32
rjCnkGetMaterial(NJS_BGRA dst[RJ_NB_CMC], const NJS_BGRA src[RJ_NB_CMC], Uint32 flag)
{
    if ( flag & RJD_CMF_DIFF ) dst[RJ_CMC_DIFF] = src[RJ_CMC_DIFF];
    if ( flag & RJD_CMF_AMBI ) dst[RJ_CMC_AMBI] = src[RJ_CMC_AMBI];
    if ( flag & RJD_CMF_SPEC ) dst[RJ_CMC_SPEC] = src[RJ_CMC_SPEC];

    return flag;
}

/****** UV Scrolling ****************************************************************************/
void
rjCnkSetUvScroll(Float u, Float v)
{
    _rj_cnk_uv_scroll_.u = u;
    _rj_cnk_uv_scroll_.v = v;
}

void
rjCnkSetEnvUvScroll(Float u, Float v)
{
    _rj_cnk_env_scroll_.u = u;
    _rj_cnk_env_scroll_.v = v;
}

/****** Set Callback ****************************************************************************/
void
rjCnkSetObjectCallback(void(__cdecl* callback)(NJS_CNK_OBJECT* object))
{
    _rj_cnk_object_callback_ = callback;
}

void
rjCnkSetMotionCallback(void(__cdecl* callback)(NJS_CNK_OBJECT* object))
{
    _nj_cnk_motion_callback_ = callback;
}

void
rjCnkSetModelCallback(void(__cdecl* callback)(NJS_CNK_MODEL* model))
{
    _rj_cnk_model_callback_ = callback;
}

/****** Set Vlist Callback **********************************************************************/
void
rjCnkSetVListPosCallback(void(__cdecl* func)(NJS_POINT3* dst, const NJS_POINT3* src))
{
    _rj_cnk_vlist_pfunc_ = ( func ) ? ( func ) : ( rjCnkCalcVlistPosition );
}

void
rjCnkSetVListNrmCallback(void(__cdecl* func)(NJS_VECTOR* dst, const NJS_VECTOR* src))
{
    _rj_cnk_vlist_nfunc_ = ( func ) ? ( func ) : ( rjCnkCalcVlistNormal );
}

void
rjCnkSetVListColCallback(void(__cdecl* func)(NJS_ARGB* dst, const NJS_ARGB* src))
{
    _rj_cnk_vlist_cfunc_ = ( func ) ? ( func ) : ( rjCnkCalcVlistColor );
}

void
rjCnkSetVListSpcCallback(void(__cdecl* func)(NJS_ARGB* dst, const NJS_ARGB* src))
{
    _rj_cnk_vlist_sfunc_ = ( func ) ? ( func ) : ( rjCnkCalcVlistSpecular );
}

/****** Default Plist Callbacks *****************************************************************/
void
rjCnkSetTextureCallback(Sint16(__cdecl* callback)(Sint16 n))
{
    _rj_cnk_texture_callback_ = ( callback ) ? ( callback ) : ( rjCnkGetTextureNum );
}

void
rjCnkSetMaterialCallback( Uint32(__cdecl* callback)(NJS_BGRA* dst, const NJS_BGRA* src, Uint32 flag) )
{
    _rj_cnk_material_callback_ = ( callback ) ? ( callback ) : ( rjCnkGetMaterial );
}
