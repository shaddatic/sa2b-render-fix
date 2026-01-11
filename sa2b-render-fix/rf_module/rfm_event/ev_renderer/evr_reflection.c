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
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

/************************/
/*  Game Definitions    */
/************************/
/****** Functions *******************************************************************/
#define SetAlphaFade        FUNC_PTR(void, __cdecl, (Sint32), 0x00600B40)

/************************/
/*  Data                */
/************************/
/****** Reflection Plane ************************************************************/
static NJS_PLANE ReflectionPlanes[32];

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
EventCalcReflectionPlanes(void)
{
    EVENT_REFLECTION* p_reflection = EventData.pReflections;

    if (!p_reflection->count)
        return;

    const int nb = MIN(p_reflection->count, 32);

    for (int i = 0; i < nb; ++i)
    {
        NJS_POINT3* p_plane = &p_reflection->ReflectionVtxs[i*4];

        ReflectionPlanes[i].px = (p_plane[0].x + p_plane[1].x + p_plane[2].x + p_plane[3].x) * 0.25f;
        ReflectionPlanes[i].py = (p_plane[0].y + p_plane[1].y + p_plane[2].y + p_plane[3].y) * 0.25f;
        ReflectionPlanes[i].pz = (p_plane[0].z + p_plane[1].z + p_plane[2].z + p_plane[3].z) * 0.25f;

        NJS_VECTOR v1, v2;

        v1.x = p_plane[1].x - p_plane[0].x;
        v1.y = p_plane[1].y - p_plane[0].y;
        v1.z = p_plane[1].z - p_plane[0].z;

        v2.x = p_plane[2].x - p_plane[0].x;
        v2.y = p_plane[2].y - p_plane[0].y;
        v2.z = p_plane[2].z - p_plane[0].z;

        NJS_VECTOR ov;

        njOuterProduct2(&v1, &v2, &ov);
        njUnitVector(&ov);

        ReflectionPlanes[i].vx = -ov.x;
        ReflectionPlanes[i].vy = -ov.y;
        ReflectionPlanes[i].vz = -ov.z;
    }
}

static void
MirrorPlane(const NJS_PLANE* pPlane)
{
    const f32 vh = njSqrt( (pPlane->vx * pPlane->vx) + (pPlane->vz * pPlane->vz) );
    const f32 vv = njSqrt( (pPlane->vy * pPlane->vy) + (vh * vh) );

    Angle angx = njArcCos(vh         / vv);
    Angle angy = njArcCos(pPlane->vz / vh);

    if (pPlane->vy > 0.f) angx = -angx;
    if (pPlane->vx > 0.f) angy = -angy;

    njTranslate(NULL, pPlane->px, pPlane->py, pPlane->pz);

    njRotateY(NULL, angy);
    njRotateX(NULL, angx);

    njScale(NULL, 1.f, 1.f, -1.f);

    njRotateX(NULL, -angx);
    njRotateY(NULL, -angy);

    njTranslate(NULL, -pPlane->px, -pPlane->py, -pPlane->pz);
}

static void
EventDrawReflectionModels(int nbScene)
{
    const EVENT_SCENE* const p_scene = &SceneData[nbScene];

    const int nb_entry = p_scene->nbEntry;

    for (int i = 0; i < nb_entry; ++i)
    {
        const EVENT_ENTRY* const p_entry = &p_scene->pEntries[i];

        const int attr = p_entry->attr;

        if ( !(attr & EV_ENTF_REFLECT) )
            continue;

        switch ( EventGetEntryType(p_entry) )
        {
            case EV_ENTRY_TYPE_NONE:
            {
                break;
            }
            case EV_ENTRY_TYPE_DRAW:
            {
                EventLightSwitchSingle();
                njCnkEasyDrawObject(p_entry->pObject);
                break;
            }
            case EV_ENTRY_TYPE_MTN:
            {
                EventLightSwitchSingle();
                njCnkEasyDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                break;
            }
            case EV_ENTRY_TYPE_SHAPE:
            {
                EventLightSwitchSingle();
                njCnkEasyDrawShapeMotion(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                break;
            }
            case EV_ENTRY_TYPE_MULTIDRAW:
            {
                EventLightSwitchMulti(attr);
                njCnkEasyMultiDrawObject(p_entry->pObject);
                break;
            }
            case EV_ENTRY_TYPE_MULTIMTN:
            {
                EventLightSwitchMulti(attr);
                njCnkEasyMultiDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
                break;
            }
            case EV_ENTRY_TYPE_MULTISHAPE:
            {
                EventLightSwitchMulti(attr);
                njCnkEasyMultiDrawShapeMotion(p_entry->pObject, p_entry->pMotion, p_entry->pShape, EventSceneFrame);
                break;
            }
            case EV_ENTRY_TYPE_EASYNOFOG:
            case EV_ENTRY_TYPE_MODDRAW:
            case EV_ENTRY_TYPE_MODMTN:
            {
                break;
            }
        }
    }
}

static void
EventDrawReflectionsSub(int nbScene)
{
    const EVENT_REFLECTION* p_reflection = EventData.pReflections;

    const int nb_planes = p_reflection->count;

    for (int i = 0; i < nb_planes; ++i)
    {
        njPushMatrixEx();

        MirrorPlane(&ReflectionPlanes[i]);

        SetAlphaFade(p_reflection->AlphaValues[i]);

        EventDrawReflectionModels(nbScene);

        njPopMatrixEx();
    }
}

/****** Extern **********************************************************************/
void
EventDrawReflections(void)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_MIRROR_MODEL);

    RFRS_SetTransMode(RFRS_TRANSMD_AUTO_TRANS);

    SaveConstantAttr();
    SaveControl3D();

    EventCalcReflectionPlanes();

    EventDrawReflectionsSub(EVENT_BASE_SCENE);
    EventDrawReflectionsSub(EventSceneNum);

    LoadConstantAttr();
    LoadControl3D();

    RFRS_SetTransMode(RFRS_TRANSMD_END);

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_MIRROR_MODEL);
}
