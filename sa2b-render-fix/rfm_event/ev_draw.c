/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/funchook.h>      /* funchook                                         */

/****** Utility *********************************************************************/
#include <samt/util/cnkmdl.h>   /* chunk model                                      */

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
#include <rf_draw.h>            /* mod draw                                         */
#include <rf_util.h>            /* switch displayer                                 */

/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h>          /* parent & siblings                    */

/************************/
/*  Game Functions      */
/************************/
/****** Event ***********************************************************************/
#define SetEntryMotionCallback      FUNC_PTR(void, __fastcall, (NJS_CNK_OBJECT*), 0x00601B50)
#define gjDrawObject                FUNC_PTR(void, __cdecl   , (GJS_OBJECT*)    , 0x0042B530)

/************************/
/*  Constants           */
/************************/
/****** Event ***********************************************************************/
#define CHUNK_ATTR_OPAQUE       (1)
#define CHUNK_ATTR_TRANSPARENT  (2)

/************************/
/*  Data                */
/************************/
/****** Event Draw Mode *************************************************************/
static bool ApplyModelDiffuse;

/************************/
/*  Source              */
/************************/
/****** Get Chunk *******************************************************************/
static s32
EV_GetCnkAttr(const Sint16* pPList)
{
    s32 attr = 0;

    if ( (RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT) && _nj_control_3d_flag_ & NJD_CONTROL_3D_DEPTH_QUEUE )
    {
        attr |= CHUNK_ATTR_TRANSPARENT;
    }

    const Sint16* plist = pPList;

    for ( ; ; )
    {
        const int type = CNK_GET_OFFTYPE(plist);

        if (type == NJD_CE)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type == NJD_CN)
        {
            /** NJD_NULLOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type <= CNK_BITSOFF_MAX)
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type <= CNK_TINYOFF_MAX)
        {
            /** NJD_TINYOFF **/

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type <= CNK_MATOFF_MAX)
        {
            /** NJD_MATOFF **/

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        if (type <= CNK_STRIPOFF_MAX)
        {
            /** NJD_STRIPOFF **/
            const Sint16 fst = plist[0];

            if ( fst & (NJD_FST_UA|NJD_FST_NAT) )
            {
                attr |= CHUNK_ATTR_TRANSPARENT;
            }
            else
            {
                attr |= CHUNK_ATTR_OPAQUE;
            }

            if ( attr == (CHUNK_ATTR_OPAQUE|CHUNK_ATTR_TRANSPARENT) )
            {
                return attr;
            }

            /** Next offset **/
            plist += ((u16*)plist)[1] + 2;
            continue;
        }

        /** An error occured, stop **/
        break;
    }

    return attr;
}

static s32
EV_GetCnkAttrObject(const NJS_CNK_OBJECT* object)
{
    s32 attr = 0;

    const NJS_CNK_OBJECT* restrict p_obj = object;

    do
    {
        if ( p_obj->model && p_obj->model->plist )
        {
            attr |= EV_GetCnkAttr(p_obj->model->plist);

            if ( attr == (CHUNK_ATTR_OPAQUE|CHUNK_ATTR_TRANSPARENT) )
            {
                return attr;
            }
        }

        if ( p_obj->child )
        {
            attr |= EV_GetCnkAttrObject(p_obj->child);

            if ( attr == (CHUNK_ATTR_OPAQUE|CHUNK_ATTR_TRANSPARENT) )
            {
                return attr;
            }
        }

        p_obj = p_obj->sibling;
    }
    while ( p_obj );

    return attr;
}

/****** Draw Chunk ******************************************************************/
static void
EV_CnkDrawObjectSub(const NJS_CNK_OBJECT* object)
{
    const s32 attr = EV_GetCnkAttrObject( object );

    if ( RFRS_GetCnkDrawMode() == RFRS_CNKDRAWMD_TRANSPARENT )
    {
        if ( attr == CHUNK_ATTR_TRANSPARENT && (object->child || object->sibling) )
        {
            RFRS_SetCullMode(RFRS_CULLMD_INVERSE);

            rjCnkDrawObject(object);

            RFRS_SetCullMode(RFRS_CULLMD_NORMAL);

            rjCnkDrawObject(object);

            RFRS_SetCullMode(RFRS_CULLMD_END);
        }
        else if ( attr & CHUNK_ATTR_TRANSPARENT )
        {
            rjCnkDrawObject(object);
        }
    }
    else if ( attr & CHUNK_ATTR_OPAQUE )
    {
        rjCnkDrawObject(object);
    }
}

static void
EV_CnkEasyDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    EV_CnkDrawObjectSub(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkSimpleDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    EV_CnkDrawObjectSub(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkEasyMultiDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    EV_CnkDrawObjectSub(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkSimpleMultiDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    EV_CnkDrawObjectSub(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkDrawMotionSub(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    const s32 attr = EV_GetCnkAttrObject( object );

    if ( RFRS_GetCnkDrawMode() == RFRS_CNKDRAWMD_TRANSPARENT )
    {
        if ( attr == CHUNK_ATTR_TRANSPARENT && (object->child || object->sibling) )
        {
            RFRS_SetCullMode(RFRS_CULLMD_INVERSE);

            rjCnkDrawMotion(object, motion, frame);

            RFRS_SetCullMode(RFRS_CULLMD_NORMAL);

            rjCnkDrawMotion(object, motion, frame);

            RFRS_SetCullMode(RFRS_CULLMD_END);
        }
        else if ( attr & CHUNK_ATTR_TRANSPARENT )
        {
            rjCnkDrawMotion(object, motion, frame);
        }
    }
    else if ( attr & CHUNK_ATTR_OPAQUE )
    {
        rjCnkDrawMotion(object, motion, frame);
    }
}

static void
EV_CnkEasyDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    EV_CnkDrawMotionSub(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkSimpleDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    EV_CnkDrawMotionSub(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkEasyMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    EV_CnkDrawMotionSub(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkSimpleMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    EV_CnkDrawMotionSub(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkDrawShapeMotionSub(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    const s32 attr = EV_GetCnkAttrObject( object );

    if ( RFRS_GetCnkDrawMode() == RFRS_CNKDRAWMD_TRANSPARENT )
    {
        if ( attr == CHUNK_ATTR_TRANSPARENT && (object->child || object->sibling) )
        {
            RFRS_SetCullMode(RFRS_CULLMD_INVERSE);

            rjCnkDrawShapeMotionBE(object, motion, shape, frame);

            RFRS_SetCullMode(RFRS_CULLMD_NORMAL);

            rjCnkDrawShapeMotionBE(object, motion, shape, frame);

            RFRS_SetCullMode(RFRS_CULLMD_END);
        }
        else if ( attr & CHUNK_ATTR_TRANSPARENT )
        {
            rjCnkDrawShapeMotionBE(object, motion, shape, frame);
        }
    }
    else if ( attr & CHUNK_ATTR_OPAQUE )
    {
        rjCnkDrawShapeMotionBE(object, motion, shape, frame);
    }
}

static void
EV_CnkEasyDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    EV_CnkDrawShapeMotionSub(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkSimpleDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    EV_CnkDrawShapeMotionSub(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkEasyMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    EV_CnkDrawShapeMotionSub(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

static void
EV_CnkSimpleMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    EV_CnkDrawShapeMotionSub(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

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
EV_SetConstMat(void)
{
    NJS_ARGB argb = {0};

    const f32 evframe = EventLastFrame;

    for ( int i = 0; i < ARYLEN(EventEffData.screen); ++i )
    {
        const EV_EFF_SCREEN* restrict p_scr = &EventEffData.screen[i];

        if ( p_scr->type < EV_EFF_SCREEN_SPRITE_FADEIN )
        {
            continue;
        }

        if ( evframe >= p_scr->frame && evframe <= (p_scr->frame + p_scr->frametime) )
        {
            const f32 spframe = evframe - p_scr->frame;

            if ( spframe < 30.f && p_scr->type == EV_EFF_SCREEN_SPRITE_FADEIN )
            {
                argb.a = spframe * (1.f/30.f);
            }
            else if ( (p_scr->frametime - 30) <= spframe && p_scr->fadeout )
            {
                argb.a = ((f32)(p_scr->frame + p_scr->frametime) - evframe) * (1.f/30.f);
            }
            else
            {
                argb.a = 1.f;
            }

            argb.r =
            argb.g =
            argb.b = 1.f;
        }
    }

    njSetConstantMaterial(&argb);
}

static void
EventSceneModDraw(const int nbScene)
{
    const EVENT_SCENE* const p_scene = &SceneData[nbScene];

    const int nb_entry = p_scene->nbEntry;

    for (int i = 0; i < nb_entry; ++i)
    {
        const EVENT_ENTRY* const p_entry = &p_scene->pEntries[i];

        const int attr = p_entry->attr;

        njPushMatrixEx();

        switch ( EventGetEntryType(p_entry) )
        {
            case EV_ENTRY_TYPE_NONE:
            case EV_ENTRY_TYPE_DRAW:
            case EV_ENTRY_TYPE_MTN:
            case EV_ENTRY_TYPE_SHAPE:
            case EV_ENTRY_TYPE_EASYNOFOG:
            case EV_ENTRY_TYPE_MULTIDRAW:
            case EV_ENTRY_TYPE_MULTIMTN:
            case EV_ENTRY_TYPE_MULTISHAPE:
            {
                break;
            }
            case EV_ENTRY_TYPE_MODDRAW:
            {
                njCnkModDrawObject(p_entry->pObject);
                break;
            }
            case EV_ENTRY_TYPE_MODMTN:
            {
                njCnkModDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                break;
            }
        }

        njCnkSetMotionCallback(NULL);

        njPopMatrixEx();
    }
}

static void
EventSceneDraw(const int nbScene, const int nbLayer)
{
    switch ( DebugDrawPass )
    {
        case DBG_DRAWPASS_ALL:
        {
            break;
        }
        case DBG_DRAWPASS_OPAQUE:
        {
            if ( nbLayer != EV_ALL_LAYERS )
            {
                return;
            }
            break;
        }
        case DBG_DRAWPASS_TRANS:
        {
            if ( nbLayer == EV_ALL_LAYERS )
            {
                return;
            }
            break;
        }
        default: // specific layer
        {
            const s32 layer = (DebugDrawPass - DBG_DRAWPASS_LAYER_START);

            if ( layer != nbLayer )
            {
                return;
            }
            break;
        }
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    if (ApplyModelDiffuse)
    {
        OffControl3D(NJD_CONTROL_3D_DEPTH_QUEUE|NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL);
    }

    const EVENT_SCENE* const p_scene = &SceneData[nbScene];

    const int nb_entry = p_scene->nbEntry;

    for (int i = 0; i < nb_entry; ++i)
    {
        const EVENT_ENTRY* const p_entry = &p_scene->pEntries[i];

        if ( nbLayer == EV_ALL_LAYERS )
        {
            SetEntryMotionCallback(p_entry->pObject);
        }
        else if ( p_entry->layer != nbLayer )
        {
            continue;
        }

        const bool use_gj = !p_entry->pObject;

        const int attr = p_entry->attr;

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
                    EV_CnkSimpleDrawObject(p_entry->pObject);
                }
                else
                {
                    EV_CnkEasyDrawObject(p_entry->pObject);
                }

                break;
            }
            case EV_ENTRY_TYPE_MTN:
            {
                EventLightSwitchSingle();

                EventScrollTexture(nbScene, i);

                if ( (attr & (EV_ENTF_SIMPLEMAT|EV_ENTF_FORCESIMPLE)) )
                {
                    EV_CnkSimpleDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }
                else
                {
                    EV_CnkEasyDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }

                break;
            }
            case EV_ENTRY_TYPE_SHAPE:
            {
                EventLightSwitchSingle();

                EventScrollTexture(nbScene, i);

                if ( (attr & EV_ENTF_SIMPLEMAT|EV_ENTF_FORCESIMPLE) )
                {
                    EV_CnkSimpleDrawShapeMotion(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                }
                else
                {
                    EV_CnkEasyDrawShapeMotion(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
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
                    EV_CnkSimpleMultiDrawObject(p_entry->pObject);
                }
                else
                {
                    EV_CnkEasyMultiDrawObject(p_entry->pObject);
                }

                break;
            }
            case EV_ENTRY_TYPE_MULTIMTN:
            {
                EventLightSwitchMulti(attr);

                EventScrollTexture(nbScene, i);

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    EV_CnkSimpleMultiDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }
                else
                {
                    EV_CnkEasyMultiDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                }

                break;
            }
            case EV_ENTRY_TYPE_MULTISHAPE:
            {
                EventLightSwitchMulti(attr);

                EventScrollTexture(nbScene, i);

                if ( (attr & EV_ENTF_SIMPLEMAT) )
                {
                    EV_CnkSimpleMultiDrawShapeMotion(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                }
                else
                {
                    EV_CnkEasyMultiDrawShapeMotion(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
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

    /** Draw Big **/

    if ( nbLayer < 1 && p_scene->pBig && EvBigActive )
    {
        const EVENT_BIG* const p_big = p_scene->pBig;

        if ( p_big->nbScene )
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
    {
        OnControl3D(NJD_CONTROL_3D_DEPTH_QUEUE|NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL);
    }

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
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

#define Z_VALUE             (1.0f)

#define EvBackColor                 DATA_REF(NJS_COLOR, 0x01DB0F88)
#define EvScreenEffectColor         DATA_REF(NJS_COLOR, 0x01DB0EB8)

static void
EV_DrawScreenEffect(void)
{
    njSetBackColor( EvBackColor.color, EvBackColor.color, EvBackColor.color );

    if ( EvScreenEffectColor.argb.a == 0x00 )
    {
        return;
    }

    const f32 disp_ratio = GetDisplayRatio();

    const f32 x_adj = (disp_ratio - 1.0f) * (320.0f) + 1.0f;

    const Uint32 color = EvScreenEffectColor.color;

    NJS_POLYGON_VTX poly[4];

    poly[0].x   = 0.0f - x_adj;
    poly[0].y   = 0.0f;
    poly[0].z   = Z_VALUE;
    poly[0].col = color;

    poly[1].x   = 0.0f - x_adj;
    poly[1].y   = 480.0f;
    poly[1].z   = Z_VALUE;
    poly[1].col = color;

    poly[2].x   = 640.0f + x_adj;
    poly[2].y   = 0.0f;
    poly[2].z   = Z_VALUE;
    poly[2].col = color;

    poly[3].x   = 640.0f + x_adj;
    poly[3].y   = 480.0f;
    poly[3].z   = Z_VALUE;
    poly[3].col = color;

    rjDrawPolygon(poly, ARYLEN(poly), EvScreenEffectColor.argb.a != 0xFF);
}

/****** Task ************************************************************************/
void
EventDisplayerShadow(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 1.f > EventFrame)
    {
        return;
    }

    /** Setup draw state **/
    njSetCamera( &EventCamera );

    /** Draw modifiers **/
    EventSceneModDraw(EVENT_BASE_SCENE);
    EventSceneModDraw(EventSceneNum);
}

void
EventDisplayerSort(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 1.f > EventFrame)
    {
        return;
    }

    /** Set constant material via screen sprites **/
    EV_SetConstMat();

    /** Draw **/
    njSetBackColor(0, 0, 0);
    njSetCamera( &EventCamera );

    njSetTexture(EventData.pTexlist);
    EventLightSet();

    njCnkSetMotionCallback(NULL);

    const int old_rmode = _gj_render_mode_;

    {
        _gj_render_mode_ = GJD_DRAW_TRANS;

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

        for (int i = 1; i <= 8; ++i)
        {
            EventSceneDraw(EVENT_BASE_SCENE, i);
            EventSceneDraw(EventSceneNum   , i);
        }

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

        _gj_render_mode_ = old_rmode;
    }
}

void
EventDisplayerDelayed(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 1.f > EventFrame)
    {
        return;
    }

    /** Set constant material via screen sprites **/
    EV_SetConstMat();

    /** Draw **/
    njSetBackColor(0, 0, 0);
    njSetCamera( &EventCamera );

    njSetTexture(EventData.pTexlist);
    EventLightSet();

    EV_DebugDisp(tp);

    njCnkSetMotionCallback(NULL);

    /** Draw Event Scenes **/

    EventDrawReflections();
    EventDrawSprites();

    const int old_rmode = _gj_render_mode_;

    {
        _gj_render_mode_ = GJD_DRAW_TRANS;

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

        for (int i = 9; i <= 16; ++i)
        {
            EventSceneDraw(EVENT_BASE_SCENE, i);
            EventSceneDraw(EventSceneNum   , i);
        }

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

        _gj_render_mode_ = old_rmode;
    }

    if (EventUseFlare)
    {
        EventDrawFlare(&EventFlarePos);
    }

    if (EventDebugInfo == 1)
    {
        EventDebug();
    }
    else if (EventDebugInfo == 2)
    {
        EventDebugNull();
    }

    EV_DrawScreenEffect();
}

void
EventDisplayer(task* tp)
{
    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 1.f > EventFrame)
    {
        return;
    }

    /** Set constant material via screen sprites **/
    EV_SetConstMat();

    /** Draw **/
    njSetBackColor(0, 0, 0);
    njSetCamera( &EventCamera );

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
        EventSceneDraw(EventSceneNum   , EV_ALL_LAYERS);

        /** Draw opaque equipment strips **/

        if ( EV_GetEquipmentMode() )
        {
            EventEquipmentDraw();
        }

        /** Draw first transparent layer **/

        _gj_render_mode_ = GJD_DRAW_TRANS;

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

        EventSceneDraw(EVENT_BASE_SCENE, 0);
        EventSceneDraw(EventSceneNum   , 0);

        /** Draw transparent equipment strips **/

        if ( EV_GetEquipmentMode() )
        {
            EventEquipmentDraw();
        }

        RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);

        _gj_render_mode_ = old_rmode;
    }
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
    WriteJump(0x005FAA70, EventInitiator);

    WriteJump(0x005FB4FD, 0x005FB5B9); // disable vanilla black bars

    SwitchDisplayer(0x005FB04D, DISP_SORT); // set screen effect to sorted displayer
}
