/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

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
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_ninja.h>           /* mod draw                                         */
#include <rf_util.h>            /* switch displayer                                 */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

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
/****** Common **********************************************************************/
static bool
IsTranclucentPass(void)
{
    return (rjCnkGetControl() & RJD_CNK_CTRL_MASK_DRAW) == RJD_CNK_CTRL_TRANSLUCENT;
}

/****** Get Chunk *******************************************************************/
static s32
EV_GetCnkAttr(const Sint16* pPList)
{
    s32 attr = 0;

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
EV_IsDepthQueue(const NJS_CNK_MODEL* model)
{
    if ( (_nj_control_3d_flag_ & NJD_CONTROL_3D_DEPTH_QUEUE) && (RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT) )
    {
        NJS_POINT3 pt;
        njCalcPoint(NULL, &model->center, &pt);

        // hardcoded 
        return ( (pt.z - model->r) < _rj_depth_queue_near_ ) ? CHUNK_ATTR_TRANSPARENT : 0;
    }

    return 0;
}

static s32
EV_GetCnkAttrObject(NJS_CNK_OBJECT* object)
{
    s32 attr = 0;

    const NJS_CNK_OBJECT* restrict p_obj = object;

    do
    {
        if ( p_obj->model )
        {
            if ( p_obj->model->plist )
            {
                attr |= EV_GetCnkAttr(p_obj->model->plist);

                if ( !(attr & CHUNK_ATTR_TRANSPARENT) && IsTranclucentPass() )
                {
                    attr |= EV_IsDepthQueue(p_obj->model);
                }

                if ( attr == (CHUNK_ATTR_OPAQUE|CHUNK_ATTR_TRANSPARENT) )
                {
                    return attr;
                }
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
EV_CnkDrawObjectSub(NJS_CNK_OBJECT* object, Sint32(*drawfn)(NJS_CNK_MODEL*))
{
    const s32 attr = EV_GetCnkAttrObject( object );

    if ( IsTranclucentPass() )
    {
        if ( attr == CHUNK_ATTR_TRANSPARENT && (object->child || object->sibling) )
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_INVERSE );

            rjCnkTransformObject(object, drawfn);

            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_NORMAL );

            rjCnkTransformObject(object, drawfn);

            rjCnkSetControl( ~0, RJD_CNK_CTRL_MASK_CULL );
        }
        else if ( attr & CHUNK_ATTR_TRANSPARENT )
        {
            rjCnkTransformObject(object, drawfn);
        }
    }
    else if ( attr & CHUNK_ATTR_OPAQUE )
    {
        rjCnkTransformObject(object, drawfn);
    }
}

static void
EV_CnkEasyDrawObject(NJS_CNK_OBJECT* object)
{
    EV_CnkDrawObjectSub(object, njCnkEasyDrawModel);
}

static void
EV_CnkSimpleDrawObject(NJS_CNK_OBJECT* object)
{
    EV_CnkDrawObjectSub(object, njCnkSimpleDrawModel);
}

static void
EV_CnkEasyMultiDrawObject(NJS_CNK_OBJECT* object)
{
    EV_CnkDrawObjectSub(object, njCnkEasyMultiDrawModel);
}

static void
EV_CnkSimpleMultiDrawObject(NJS_CNK_OBJECT* object)
{
    EV_CnkDrawObjectSub(object, njCnkSimpleMultiDrawModel);
}

static void
EV_CnkDrawMotionSub(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame, Sint32(*drawfn)(NJS_CNK_MODEL*))
{
    const s32 attr = EV_GetCnkAttrObject( object );

    if ( IsTranclucentPass() )
    {
        if ( attr == CHUNK_ATTR_TRANSPARENT && (object->child || object->sibling) )
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_INVERSE );

            rjCnkDrawMotion(object, motion, frame, drawfn);

            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_NORMAL );

            rjCnkDrawMotion(object, motion, frame, drawfn);

            rjCnkSetControl( ~0, RJD_CNK_CTRL_MASK_CULL );
        }
        else if ( attr & CHUNK_ATTR_TRANSPARENT )
        {
            rjCnkDrawMotion(object, motion, frame, drawfn);
        }
    }
    else if ( attr & CHUNK_ATTR_OPAQUE )
    {
        rjCnkDrawMotion(object, motion, frame, drawfn);
    }
}

static void
EV_CnkEasyDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    EV_CnkDrawMotionSub(object, motion, frame, njCnkEasyDrawModel);
}

static void
EV_CnkSimpleDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    EV_CnkDrawMotionSub(object, motion, frame, njCnkSimpleDrawModel);
}

static void
EV_CnkEasyMultiDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    EV_CnkDrawMotionSub(object, motion, frame, njCnkEasyMultiDrawModel);
}

static void
EV_CnkSimpleMultiDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    EV_CnkDrawMotionSub(object, motion, frame, njCnkSimpleMultiDrawModel);
}

static void
EV_CnkDrawShapeMotionSub(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame, Sint32(*drawfn)(NJS_CNK_MODEL*))
{
    const s32 attr = EV_GetCnkAttrObject( object );

    if ( IsTranclucentPass() )
    {
        if ( attr == CHUNK_ATTR_TRANSPARENT && (object->child || object->sibling) )
        {
            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_INVERSE );

            rjCnkDrawShapeMotionBE(object, motion, shape, frame, frame, drawfn);

            rjCnkSetControl( ~RJD_CNK_CTRL_MASK_CULL, RJD_CNK_CTRL_NORMAL );

            rjCnkDrawShapeMotionBE(object, motion, shape, frame, frame, drawfn);

            rjCnkSetControl( ~0, RJD_CNK_CTRL_MASK_CULL );
        }
        else if ( attr & CHUNK_ATTR_TRANSPARENT )
        {
            rjCnkDrawShapeMotionBE(object, motion, shape, frame, frame, drawfn);
        }
    }
    else if ( attr & CHUNK_ATTR_OPAQUE )
    {
        rjCnkDrawShapeMotionBE(object, motion, shape, frame, frame, drawfn);
    }
}

static void
EV_CnkEasyDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    EV_CnkDrawShapeMotionSub(object, motion, shape, frame, njCnkEasyDrawModel);
}

static void
EV_CnkSimpleDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    EV_CnkDrawShapeMotionSub(object, motion, shape, frame, njCnkSimpleDrawModel);
}

static void
EV_CnkEasyMultiDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    EV_CnkDrawShapeMotionSub(object, motion, shape, frame, njCnkEasyMultiDrawModel);
}

static void
EV_CnkSimpleMultiDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    EV_CnkDrawShapeMotionSub(object, motion, shape, frame, njCnkSimpleMultiDrawModel);
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

void
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

void
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

void
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

        if ( p_big->nbMotion )
        {
            NJS_TEXLIST* p_tls = njGetCurrentTexList();

            if ( EvBigTexture )
            {
                njSetTexture(EvBigTexture);
            }

            njPushMatrixEx();

            const EVENT_BIG_MOTION* const p_mot = &p_big->pMotions[EventBigMotion];

            njCnkSimpleDrawShapeMotion(p_big->pObject, p_mot->pMotion, p_mot->pShape, EventBigFrame);

            njPopMatrixEx();

            njSetTexture(p_tls);
        }
    }

    if (ApplyModelDiffuse)
    {
        OnControl3D(NJD_CONTROL_3D_DEPTH_QUEUE|NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL);
    }

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

void
EventResetEquipmentFlags(void)
{
    for (int i = 0; i < ARYLEN(EventEquipmentFlags); ++i)
    {
        EventEquipmentFlags[i] = 0;
    }
}

#define PlayerEqipmentList          DATA_ARY(Sint8, 0x01DEB300, [29])

void
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

            NJS_CNK_OBJECT* const p_object1 = p_equip->Equipment[0].pObject;
            NJS_CNK_OBJECT* const p_object2 = p_equip->Equipment[1].pObject;

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

#define SCRNPOLY_Z_VALUE            (1.0f)

#define EvBackColor                 DATA_REF(NJS_COLOR, 0x01DB0F88)
#define EvScreenEffectColor         DATA_REF(NJS_COLOR, 0x01DB0EB8)

void
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
    poly[0].z   = SCRNPOLY_Z_VALUE;
    poly[0].col = color;

    poly[1].x   = 0.0f - x_adj;
    poly[1].y   = 480.0f;
    poly[1].z   = SCRNPOLY_Z_VALUE;
    poly[1].col = color;

    poly[2].x   = 640.0f + x_adj;
    poly[2].y   = 0.0f;
    poly[2].z   = SCRNPOLY_Z_VALUE;
    poly[2].col = color;

    poly[3].x   = 640.0f + x_adj;
    poly[3].y   = 480.0f;
    poly[3].z   = SCRNPOLY_Z_VALUE;
    poly[3].col = color;

    rjDrawPolygon(poly, ARYLEN(poly), EvScreenEffectColor.argb.a != 0xFF);
}

/****** Control *********************************************************************/
void
RFCTRL_EventApplyModelDiffuse(void)
{
    ApplyModelDiffuse = true;
}
