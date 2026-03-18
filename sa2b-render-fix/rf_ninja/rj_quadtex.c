/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* WriteJump                                                */

/****** Util ************************************************************************************/
#include <samt/util/endian.h>       /* swap endian                                              */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */
#include <samt/ninja/njcontext.h>   /* ninja context                                            */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* resolution                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>  /* parent & siblings                                         */

/********************************/
/*  Game Vars                   */
/********************************/
/****** Ch Quad Color ***************************************************************************/
#define _ch_quad_color_             DATA_REF(Uint32         , 0x01A54FF0)
#define pTexSurface                 DATA_REF(NJS_TEXSURFACE*, 0x01A55840)

/********************************/
/*  Constants                   */
/********************************/
/****** Half Screen Values **********************************************************************/
#define SCREEN_HW                   (640.f*0.5f)
#define SCREEN_HH                   (480.f*0.5f)

/********************************/
/*  Variables                   */
/********************************/
/****** Quad Attr *******************************************************************************/
static Sint32 _rj_quad_trans_;
static Uint32 _rj_quad_col_;
static Uint32 _rj_quad_off_;

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static void
___StartChangeQuadTexAttr(void)
{
    // if vertex buffer used, draw now because we're switching texture
    rjEndVertex();

    rjSetHwCullingCtx();

    rjSetBlend2D(_rj_quad_trans_);
}

static void
___EndChangeQuadTexAttr(void)
{
    rjStartVertex2D(RJ_VERTEX_PTCO);
}

static void
___SetQuadTexColor(Uint32 col)
{
    _rj_quad_col_ = col;
    _rj_quad_off_ = 0xFF000000;
}

static void
___SetQuadTexHColor(Uint32 col, Uint32 off)
{
    _rj_quad_col_ = col;
    _rj_quad_off_ = off;
}

/****** Start/End *******************************************************************************/
void
rjQuadTextureStart(Sint32 trans)
{
    _rj_quad_trans_ = trans;
}

void
rjQuadTextureEnd(void)
{
    rjEndVertex();

    rjSetHwCulling( RJ_CULL_NONE );
}

/****** Quad Attr *******************************************************************************/
void
rjSetQuadTexture(Sint32 texid, Uint32 col)
{
    ___StartChangeQuadTexAttr();

    rjSetTextureNum(texid);
    rjSetTexture2D(FALSE);

    ___SetQuadTexColor(col);

    ___EndChangeQuadTexAttr();
}

void
rjSetQuadTextureG(Sint32 gid, Uint32 col)
{
    ___StartChangeQuadTexAttr();

    rjSetTextureNumG(gid);
    rjSetTexture2D(FALSE);

    ___SetQuadTexColor(col);

    ___EndChangeQuadTexAttr();
}

void
rjSetQuadTextureH(Sint32 texid, Uint32 col, Uint32 off)
{
    ___StartChangeQuadTexAttr();

    rjSetTextureNum(texid);
    rjSetTexture2D(FALSE);

    ___SetQuadTexHColor(col, off);

    ___EndChangeQuadTexAttr();
}

/****** Quad Color ******************************************************************************/
void
rjSetQuadTextureColor(Uint32 col)
{
    ___StartChangeQuadTexAttr();

    rjSetHwTextureParamCtx();

    ___SetQuadTexColor(col);

    ___EndChangeQuadTexAttr();
}

void
rjSetQuadTextureHColor(Uint32 col, Uint32 off)
{
    ___StartChangeQuadTexAttr();

    rjSetHwTextureParamCtx();

    ___SetQuadTexHColor(col, off);

    ___EndChangeQuadTexAttr();
}

/****** Quad Texture ****************************************************************************/
void
rjDrawQuadTexture(const NJS_QUAD_TEXTURE* q, Float z)
{
    /**** Constants *************************************************************************/

    const Float scrn_hw = SCREEN_HW;
    const Float scrn_hh = SCREEN_HH;

    const Uint32 col = _rj_quad_col_;
    const Uint32 off = _rj_quad_off_;

    /**** Draw ******************************************************************************/

    const Sint32 nbv = rjStartTriStrip(4);

    RJS_VERTEX_PTCO* restrict p_buf = rjGetVertexBuffer();

    p_buf[0].pos.x = q->x1;
    p_buf[0].pos.y = q->y1;
    p_buf[0].pos.z = z;
    p_buf[0].u     = q->u1;
    p_buf[0].v     = q->v1;
    p_buf[0].col   = col;
    p_buf[0].off   = off;

    p_buf[1].pos.x = q->x2;
    p_buf[1].pos.y = q->y1;
    p_buf[1].pos.z = z;
    p_buf[1].u     = q->u2;
    p_buf[1].v     = q->v1;
    p_buf[1].col   = col;
    p_buf[1].off   = off;

    p_buf[2].pos.x = q->x1;
    p_buf[2].pos.y = q->y2;
    p_buf[2].pos.z = z;
    p_buf[2].u     = q->u1;
    p_buf[2].v     = q->v2;
    p_buf[2].col   = col;
    p_buf[2].off   = off;

    p_buf[3].pos.x = q->x2;
    p_buf[3].pos.y = q->y2;
    p_buf[3].pos.z = z;
    p_buf[3].u     = q->u2;
    p_buf[3].v     = q->v2;
    p_buf[3].col   = col;
    p_buf[3].off   = off;

    for ( int i = 0; i < 4; ++i )
    {
        p_buf[i].pos.x = (p_buf[i].pos.x - scrn_hw) / scrn_hw;
        p_buf[i].pos.y = (p_buf[i].pos.y - scrn_hh) / scrn_hh;
    }

    rjEndTriStrip(nbv);
}

void
rjDrawQuadTextureEx(const NJS_QUAD_TEXTURE_EX* q)
{
    /**** Constants *************************************************************************/

    const Float scrn_hw = SCREEN_HW;
    const Float scrn_hh = SCREEN_HH;

    const Uint32 col = _rj_quad_col_;
    const Uint32 off = _rj_quad_off_;

    /**** Draw ******************************************************************************/

    const Sint32 nbv = rjStartTriStrip(4);

    RJS_VERTEX_PTCO* restrict p_buf = rjGetVertexBuffer();

    p_buf[0].pos.x = q->x;
    p_buf[0].pos.y = q->y;
    p_buf[0].pos.z = q->z;
    p_buf[0].u     = q->u;
    p_buf[0].v     = q->v;
    p_buf[0].col   = col;
    p_buf[0].off   = off;

    p_buf[1].pos.x = q->x + q->vx1;
    p_buf[1].pos.y = q->y + q->vy1;
    p_buf[1].pos.z = q->z;
    p_buf[1].u     = q->u + q->vu1;
    p_buf[1].v     = q->v + q->vv1;
    p_buf[1].col   = col;
    p_buf[1].off   = off;

    p_buf[2].pos.x = q->x + q->vx2;
    p_buf[2].pos.y = q->y + q->vy2;
    p_buf[2].pos.z = q->z;
    p_buf[2].u     = q->u + q->vu2;
    p_buf[2].v     = q->v + q->vv2;
    p_buf[2].col   = col;
    p_buf[2].off   = off;

    p_buf[3].pos.x = q->x + q->vx1 + q->vx2;
    p_buf[3].pos.y = q->y + q->vy1 + q->vy2;
    p_buf[3].pos.z = q->z;
    p_buf[3].u     = q->u + q->vu1 + q->vu2;
    p_buf[3].v     = q->v + q->vv1 + q->vv2;
    p_buf[3].col   = col;
    p_buf[3].off   = off;

    for ( int i = 0; i < 4; ++i )
    {
        p_buf[i].pos.x = (p_buf[i].pos.x - scrn_hw) / scrn_hw;
        p_buf[i].pos.y = (p_buf[i].pos.y - scrn_hh) / scrn_hh;
    }

    rjEndTriStrip(nbv);
}

/****** Usercall ********************************************************************************/
static void
chSetupQuadTexture(void)
{
    Uint32 col = _ch_quad_color_;

    EndianSwap32(&col);
    rjSetQuadTextureColor(col);

    rjStartVertex2D(RJ_VERTEX_PTCO);
}

static void
chDrawQuadTexture(const NJS_QUAD_TEXTURE* q, Float z)
{
    chSetupQuadTexture();

    NJS_QUAD_TEXTURE q2 = *q;

    Float ylo, yhi;

    if ( q2.y2 > q2.y1 )
    {
        ylo = q2.y2;
        yhi = q2.y1;
    }
    else
    {
        ylo = q2.y1;
        yhi = q2.y2;
    }

    const Float yoff = (480.f - ylo) - yhi;

    q2.y1 += yoff;
    q2.y2 += yoff;

    rjDrawQuadTexture(&q2, z);
    rjQuadTextureEnd();
}

__declspec(naked)
static void
___chDrawQuadTexture(void)
{
    __asm
    {
        push        [esp+4]
        push        esi

        call        chDrawQuadTexture

        add esp,    8
        retn
    }
}

static void
chDrawQuadTexture2(const NJS_QUAD_TEXTURE* q, Float z)
{
    chSetupQuadTexture();
    rjDrawQuadTexture(q, z);
    rjQuadTextureEnd();
}

__declspec(naked)
static void
___chDrawQuadTexture2(void)
{
    __asm
    {
        push        [esp+4]
        push        eax

        call        chDrawQuadTexture2

        add esp,    8
        retn
    }
}

/****** Init ************************************************************************************/
void
RJ_QuadTexInit(void)
{
    WriteJump(0x00781CB0, rjQuadTextureStart);
    WriteJump(0x00782000, ___chDrawQuadTexture);
    WriteJump(0x0057E730, ___chDrawQuadTexture2);
    WriteJump(0x005A6450, ___chDrawQuadTexture2);
}
