/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/njctrl.h>  /* ninja control                                    */
#include <samt/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h>          /* parent & siblings                    */
#include <rfm_event/ev_draw/evd_internal.h> /* children                             */

/************************/
/*  Game Functions      */
/************************/
/****** Event ***********************************************************************/
#define SetEntryMotionCallback      FUNC_PTR(void, __fastcall, (NJS_CNK_OBJECT*), 0x00601B50)
#define gjDrawObject                FUNC_PTR(void, __cdecl   , (GJS_OBJECT*)    , 0x0042B530)

/************************/
/*  Data                */
/************************/
/****** Event Draw Mode *************************************************************/
static bool ApplyModelDiffuse;

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
EventScrollTexture(const int nbScene, const int nbEntry)
{
    static const uintptr_t p = 0x005F9640;

    __asm
    {
        push [nbEntry]
        mov eax, [nbScene]
        call p
        add esp, 4
    }
}

static void
EventSceneDraw(const int nbScene, const int nbLayer)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    if (ApplyModelDiffuse)
        OffControl3D(NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL);

    const EVENT_SCENE* const p_scene = &SceneData[nbScene];

    const int nb_entry = p_scene->nbEntry;

    for (int i = 0; i < nb_entry; ++i)
    {
        const EVENT_ENTRY* const p_entry = &p_scene->pEntries[i];

        if (nbLayer != EV_ALL_LAYERS && p_entry->layer != nbLayer)
            continue;

        const bool use_gj = !p_entry->pObject;

        const int attr = p_entry->attr;

        SetEntryMotionCallback(p_entry->pObject);

        njPushMatrixEx();

        switch ( EventGetEntryType(p_entry) )
        {
            case EV_ENTRY_TYPE_NONE:
                break;

            case EV_ENTRY_TYPE_DRAW:
            {
                EventLightSwitchSingle();

                EventScrollTexture(nbScene, i);

                if (use_gj)
                {
                    gjDrawObject(p_entry->pGjsObject);
                    break;
                }

                if ( (attr & (EV_ENTF_SIMPLEMAT|EV_ENTF_FORCESIMPLE)) )
                {
                    njCnkSimpleDrawObject(p_entry->pObject);
                }
                else
                {
                    njCnkEasyDrawObject(p_entry->pObject);
                }

                break;
            }
            case EV_ENTRY_TYPE_MTN:
            {
                EventLightSwitchSingle();

                EventScrollTexture(nbScene, i);

                DRAW_MTN:

                if ( (attr & (EV_ENTF_SIMPLEMAT|EV_ENTF_FORCESIMPLE)) )
                {
                    njCnkSimpleDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }
                else
                {
                    njCnkEasyDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }

                break;
            }
            case EV_ENTRY_TYPE_SHAPE:
            {
                EventLightSwitchSingle();

                EventScrollTexture(nbScene, i);

                /** Fix for Rouges wings in E0024 **/
                if (EventNum == 24 && nbScene == 1 && i == 8)
                    goto DRAW_MTN;

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleDrawShapeMotionBE(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                }
                else
                {
                    njCnkEasyDrawShapeMotionBE(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                }

                break;
            }
            case EV_ENTRY_TYPE_EASYNOFOG:
            {
                EventLightSwitchSingle();

                njFogDisable();

                EventScrollTexture(nbScene, i);

                if (use_gj)
                {
                    gjDrawObject(p_entry->pGjsObject);
                    njFogEnable();
                    break;
                }

                njCnkEasyDrawObject(p_entry->pObject);

                njFogEnable();
                break;
            }
            case EV_ENTRY_TYPE_MULTIDRAW:
            {
                EventLightSwitchMulti(attr);

                EventScrollTexture(nbScene, i);

                if (use_gj)
                {
                    gjDrawObject(p_entry->pGjsObject);
                    break;
                }

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleMultiDrawObject(p_entry->pObject);
                }
                else
                {
                    njCnkEasyMultiDrawObject(p_entry->pObject);
                }

                break;
            }
            case EV_ENTRY_TYPE_MULTIMTN:
            {
                EventLightSwitchMulti(attr);

                EventScrollTexture(nbScene, i);

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleMultiDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }
                else
                {
                    njCnkEasyMultiDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }

                break;
            }
            case EV_ENTRY_TYPE_MULTISHAPE:
            {
                EventLightSwitchMulti(attr);

                EventScrollTexture(nbScene, i);

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    njCnkSimpleMultiDrawShapeMotionBE(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                }
                else
                {
                    njCnkEasyMultiDrawShapeMotionBE(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                }

                break;
            }
            case EV_ENTRY_TYPE_MODDRAW:
            case EV_ENTRY_TYPE_MODMTN:
                break;
        }

        njCnkSetMotionCallback(NULL);

        njPopMatrixEx();
    }

    EventLightSwitchSingle();

    if (nbLayer < 1 && p_scene->pBig)
    {
        const EVENT_BIG* const p_big = p_scene->pBig;

        if (p_big->nbMotion)
        {
            njPushMatrixEx();

            const EVENT_BIG_MOTION* const p_mot = &p_big->motions[EventBigScene];

            if (!p_mot->shape)
            {
                njCnkSimpleDrawMotion(p_big->object, p_mot->motion, EventBigFrame);
            }
            else
            {
                njCnkSimpleDrawShapeMotion(p_big->object, p_mot->motion, p_mot->shape, EventBigFrame);
            }

            njPopMatrixEx();
        }
    }

    if (ApplyModelDiffuse)
        OnControl3D(NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL);

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

static int
EventSceneGetLayerCount(const int nbScene)
{
    int nb_layer = 0;

    const EVENT_SCENE* const p_scene = &SceneData[nbScene];

    const int nb_entry = p_scene->nbEntry;

    for (int i = 0; i < nb_entry; ++i)
    {
        const EVENT_ENTRY* const p_entry = &p_scene->pEntries[i];

        const int layer = p_entry->layer + 1;

        if (nb_layer < layer)
            nb_layer = layer;
    }

    return nb_layer;
}

static int
EventGetLayerCount(void)
{
    const int nb_layer_base  = EventSceneGetLayerCount(EVENT_BASE_SCENE);
    const int nb_layer_scene = EventSceneGetLayerCount(EventScene);

    return MAX(nb_layer_base, nb_layer_scene);
}

static void
EventResetEquipmentFlags(void)
{
    for (int i = 0; i < ARYLEN(EventEquipmentFlags); ++i)
    {
        EventEquipmentFlags[i] = 0;
    }
}

#define PlayerEqipmentList          DATA_ARY(Sint8, 0x01DEB300, [29])

static void
EventEquipmentDraw(void)
{
    OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW);

    njPushMatrixEx();

    for (int i = 0, j = 0; i < 18; ++i, j += 2)
    {
        const int eqidx = EventEquipmentIndexes[i];

        if ( eqidx != -1 && (eqidx == -2 || PlayerEqipmentList[eqidx]) )
        {
            EVENT_EQUIPMENT* const p_equip = &EventData.pEquipment[i];

            NJS_CNK_OBJECT* const p_object1 = p_equip->pObject1;
            NJS_CNK_OBJECT* const p_object2 = p_equip->pObject2;

            if (EventEquipmentFlags[j+0] && p_object1)
            {
                njSetMatrix(NULL, &EventEquipmentMatrices[j+0]);

                p_object1->evalflags |= (NJD_EVAL_UNIT_POS|NJD_EVAL_UNIT_ANG);

                njCnkSimpleDrawObject(p_object1);
            }
            if (EventEquipmentFlags[j+1] && p_object2)
            {
                njSetMatrix(NULL, &EventEquipmentMatrices[j+1]);

                p_object2->evalflags |= (NJD_EVAL_UNIT_POS|NJD_EVAL_UNIT_ANG);

                njCnkSimpleDrawObject(p_object2);
            }
        }
    }

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW);
}

/****** Task ************************************************************************/
static void
EventDisplayerDelayed(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    /** Draw **/
    njSetBackColor(0, 0, 0);
    EventCameraInit();

    njSetTexture(EventData.pTexlist);
    EventLightSet();

    njCnkSetMotionCallback(NULL);

    /** Draw Event Scenes **/
    {
        const int old_rmode = _gj_render_mode_;

        _gj_render_mode_    = GJD_DRAW_TRANS;

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

        const int nb_layer = EventGetLayerCount();

        for (int i = 1; i < nb_layer; ++i)
        {
            EventSceneDraw(EVENT_BASE_SCENE, i);
            EventSceneDraw(EventScene      , i);
        }

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

        _gj_render_mode_ = old_rmode;
    }

    EventDrawReflections();

    if (EventUseFlare)
        EventDrawFlare(&EventFlarePos);

    EventDrawSprites();

    if (EventDebugInfo == 1)
        EventDebug();
    if (EventDebugInfo == 2)
        EventDebugNull();

    EventDrawScreenQuad();
    Draw43Bars();
}

static void
EventDisplayer(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    /** Draw **/
    njSetBackColor(0, 0, 0);
    EventCameraInit();

    njSetTexture(EventData.pTexlist);
    EventLightSet();

    EventResetEquipmentFlags();

    njCnkSetMotionCallback(NULL);

    /** Draw Event Scenes **/
    {
        const int old_rmode = _gj_render_mode_;

        /** Draw all opaque polygons **/

        _gj_render_mode_ = GJD_DRAW_SOLID;

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_OPAQUE);

        EventSceneDraw(EVENT_BASE_SCENE, EV_ALL_LAYERS);
        EventSceneDraw(EventScene      , EV_ALL_LAYERS);

        /** Draw first transparent layer **/

        _gj_render_mode_ = GJD_DRAW_TRANS;

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

        EventSceneDraw(EVENT_BASE_SCENE, 0);
        EventSceneDraw(EventScene      , 0);

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

        _gj_render_mode_ = old_rmode;
    }

    if ( EV_GetEquipmentMode() )
        EventEquipmentDraw();
}

/****** Control *********************************************************************/
void
RFCTRL_EventApplyModelDiffuse(void)
{
    ApplyModelDiffuse = true;
}

/****** Init ************************************************************************/
void
EV_DrawInit(void)
{
    WriteJump(0x005FABF0, EventDisplayer);
    WriteJump(0x005FAD20, EventDisplayerDelayed);

}
