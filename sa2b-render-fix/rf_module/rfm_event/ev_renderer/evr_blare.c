/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/funchook.h>      /* funchook                                         */

/****** System **********************************************************************/
#include <samt/shinobi/sg_maloc.h> /* symaloc                                       */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/njctrl.h>  /* ninja control                                    */
#include <samt/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

/************************/
/*  Structures          */
/************************/
/****** Task Work *******************************************************************/
#define GET_BLAREWK(tp)         ((EV_BLARE_PARAM*)(tp)->awp)

typedef struct 
{
    NJS_CNK_OBJECT* object;
    NJS_MOTION*     motion;
    NJS_MOTION*     shape;
    f32             frame;
    i32             type;
    u32             attr;
    i32             maxtimer;
    i32             timer;
    f32             fade;
}
EV_BLARE_PARAM;

/************************/
/*  Source              */
/************************/
/****** Task ************************************************************************/
static void
blareExec(task* tp)
{
    EV_BLARE_PARAM* p_blarewk = GET_BLAREWK(tp);

    const int timer = ++p_blarewk->timer;

    if ( timer >= p_blarewk->maxtimer )
    {
        DestroyTask(tp);
        return;
    }

    p_blarewk->fade = 1.f - ((f32)timer / (f32)p_blarewk->maxtimer);
}

static void
blareDisp(task* tp)
{
    EV_BLARE_PARAM* p_blarewk = GET_BLAREWK(tp);

    SaveControl3D();
    SaveConstantAttr();
    SaveConstantMaterial();

    njSetTexture(EventData.pTexlist);

    if ( p_blarewk->fade < 1.f && p_blarewk->fade > 0.f )
    {
        FUNC_PTR(void, __cdecl, (i32), 0x00600B40)( (i32)(p_blarewk->fade * 100.f) );

        const u32 attr = p_blarewk->attr;

        njPushMatrixEx();

        switch ( p_blarewk->type )
        {
            case EV_ENTRY_TYPE_DRAW:
            {
                EventLightSwitchSingle();

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleDrawObject(p_blarewk->object);
                }
                else
                {
                    njCnkEasyDrawObject(p_blarewk->object);
                }

                break;
            }
            case EV_ENTRY_TYPE_MTN:
            {
                EventLightSwitchSingle();

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleDrawMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->frame);
                }
                else
                {
                    njCnkEasyDrawMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->frame);
                }

                break;
            }
            case EV_ENTRY_TYPE_SHAPE:
            {
                EventLightSwitchSingle();

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleDrawShapeMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->shape, p_blarewk->frame);
                }
                else
                {
                    njCnkEasyDrawShapeMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->shape, p_blarewk->frame);
                }

                break;
            }
            case EV_ENTRY_TYPE_MULTIDRAW:
            {
                EventLightSwitchMulti(attr);

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleMultiDrawObject(p_blarewk->object);
                }
                else
                {
                    njCnkEasyMultiDrawObject(p_blarewk->object);
                }

                break;
            }
            case EV_ENTRY_TYPE_MULTIMTN:
            {
                EventLightSwitchMulti(attr);

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleMultiDrawMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->frame);
                }
                else
                {
                    njCnkEasyMultiDrawMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->frame);
                }

                break;
            }
            case EV_ENTRY_TYPE_MULTISHAPE:
            {
                EventLightSwitchMulti(attr);

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleMultiDrawShapeMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->shape, p_blarewk->frame);
                }
                else
                {
                    njCnkEasyMultiDrawShapeMotion(p_blarewk->object, p_blarewk->motion, p_blarewk->shape, p_blarewk->frame);
                }

                break;
            }
        }

        njPopMatrixEx();
    }

    LoadConstantMaterial();
    LoadConstantAttr();
    LoadControl3D();
}

static void
EV_BlareCreate(const EV_BLARE_PARAM* pBlareParam)
{
    task* tp = CreateElementalTask(TELE_NUL, LEV_2, blareExec, "blareExec");

    tp->disp_dely = blareDisp;

    EV_BLARE_PARAM* p_blarewk = syMalloc( sizeof(EV_BLARE_PARAM) );

    tp->awp = TO_ANYWK(p_blarewk);

    *p_blarewk = *pBlareParam;
}

/****** Extern **********************************************************************/
void
EV_BlareExec(int ixScene)
{
    const EVENT_SCENE* p_scene = &SceneData[ixScene];

    const int nb_entry = p_scene->nbEntry;

    for ( int ix_entry = 0; ix_entry < nb_entry; ++ix_entry )
    {
        const EVENT_ENTRY* p_entry = &p_scene->pEntries[ix_entry];

        for ( int ix_blare = 0; ix_blare < ARYLEN(EvBlareInfo); ++ix_blare )
        {
            EV_BLARE_INFO* p_blare = &EvBlareInfo[ix_blare];

            if ( p_blare->enabled == TRUE && p_entry->pObject == EventData.pBlareObjects[ix_blare] )
            {
                const EV_BLARE_PARAM param =
                {
                    .object = p_entry->pObject,
                    .motion = p_entry->pMotion,
                    .shape  = p_entry->pShape,
                    .frame  = EventSceneFrame,
                    .type   = EventGetEntryType(p_entry),
                    .attr   = p_entry->attr,

                    .maxtimer = p_blare->maxtimer + 30,
                };

                EV_BlareCreate(&param);

                if ( ++p_blare->drawnum > p_blare->maxdraw )
                {
                    p_blare->enabled = FALSE;
                }
            }

            break;
        }
    }
}
