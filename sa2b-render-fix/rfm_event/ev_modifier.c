#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/file.h>
#include <sa2b/memutil.h>
#include <sa2b/model.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>
#include <rf_eventinfo.h>

typedef struct
{
    NJS_CNK_OBJECT* pObject;
    NJS_MOTION*     pMotion;
    char            __gap[20];
    Uint32          flag;
}
DC_EVENT_ENTRY;

typedef struct
{
    DC_EVENT_ENTRY* pEntries;
    size_t          nbEntry;
    char            __gap[24];
}
DC_EVENT_SCENE;

typedef struct
{
    DC_EVENT_SCENE* pScenes;
    char            __gap[4];
    size_t          nbScene;
}
DC_EVENT_HEADER;

#define EVENT_DC_KEY    (0xC600000)

#define CheckDCPointer(_ptr)                ((uintptr_t)(_ptr) >= EVENT_DC_KEY && (uintptr_t)(_ptr) < 0x0C900000)
#define ResolveDCPointer(_ptr, _offset)     (*(uintptr_t*)&(_ptr) = ((uintptr_t)(_ptr) - EVENT_DC_KEY) + (uintptr_t)(_offset))

static void
FixChunkObjectPointers(NJS_CNK_OBJECT* pObject, uintptr_t offset)
{
    if (CheckDCPointer(pObject->model))
    {
        ResolveDCPointer(pObject->model, offset);

        NJS_CNK_MODEL* p_model = pObject->model;

        ResolveDCPointer(p_model->vlist, offset);
        ResolveDCPointer(p_model->plist, offset);
    }
    if (CheckDCPointer(pObject->child))
    {
        ResolveDCPointer(pObject->child, offset);
        FixChunkObjectPointers(pObject->child, offset);
    }
    if (CheckDCPointer(pObject->sibling))
    {
        ResolveDCPointer(pObject->sibling, offset);
        FixChunkObjectPointers(pObject->sibling, offset);
    }
}

void
ResolveMotionDataPointers(void* pMotionData, size_t nbObject, size_t nbFactor, uintptr_t offset)
{
    void** pp_key_og = (void**)pMotionData;

    for (size_t i = 0; i < nbObject; ++i)
    {
        for (size_t j = 0; j < nbFactor; ++j)
        {
            if (CheckDCPointer(*pp_key_og))
                ResolveDCPointer(*pp_key_og, offset);

            /** To next factor 'p' & 'nb' **/
            ++pp_key_og;
        }

        /** To next MDATA entry **/
        pp_key_og += nbFactor;
    }
}

static void
ResolveMotionPointers(NJS_MOTION* pMotion, uintptr_t offset, size_t nbObject)
{
    int nb_mkey = 0;

    for (int i = 0, m = 1; i < bitsin(pMotion->type); ++i, m <<= 1)
    {
        if (pMotion->type & m)
            ++nb_mkey;
    }

    if (nb_mkey < 1 || nb_mkey > 4)
        RF_DebugFuncError("Motion mkey count is invalid");

    ResolveMotionDataPointers(pMotion->mdata, nbObject, nb_mkey, offset);
}

static void
EventResolveModPointers(DC_EVENT_HEADER* pEventHead)
{
    const uintptr_t offset = (uintptr_t)pEventHead;

    if (CheckDCPointer(pEventHead->pScenes))
        ResolveDCPointer(pEventHead->pScenes, offset);
    else
        return; // Idk what to do in this case, so I won't worry about it :)

    const size_t nb_scene = pEventHead->nbScene;

    for (uint32_t i = 0; i < nb_scene; ++i)
    {
        DC_EVENT_SCENE* p_scene = &pEventHead->pScenes[i];

        if (CheckDCPointer(p_scene->pEntries))
            ResolveDCPointer(p_scene->pEntries, offset);
        else
            continue;

        const size_t nb_entry = p_scene->nbEntry;

        for (uint32_t j = 0; j < nb_entry; ++j)
        {
            DC_EVENT_ENTRY* p_entry = &p_scene->pEntries[j];

            if (CheckDCPointer(p_entry->pObject))
            {
                ResolveDCPointer(p_entry->pObject, offset);

                FixChunkObjectPointers(p_entry->pObject, offset);

                if (CheckDCPointer(p_entry->pMotion))
                {
                    ResolveDCPointer(p_entry->pMotion, offset);
                    ResolveDCPointer(p_entry->pMotion->mdata, offset);

                    const size_t nb_object = MDL_CountObject(p_entry->pObject);

                    ResolveMotionPointers(p_entry->pMotion, offset, nb_object);
                }
            }
        }
    }
}

static DC_EVENT_HEADER*
EventLoadModifierFile()
{
    char str[260];

    snprintf(str, sizeof(str), "%s/evmod/e%04dmodifier.bin", GetModPath(), EventNum);

    if (!uFileExists(str))
    {
    FAIL:
        OutputFormat("Failed to load: %s", str);
        return NULL;
    }

    DC_EVENT_HEADER* fevent = uFileLoad(str, NULL);

    if (!fevent)
        goto FAIL;

    OutputFormat("Loading: %s", str);

    EventResolveModPointers(fevent);

    return fevent;
}

static DC_EVENT_HEADER* EventCurModHeader;
static bool EventFileLoadAttempted;

static void
EventDisplayMod(int scene)
{
    const DC_EVENT_SCENE* p_scene = &EventCurModHeader->pScenes[scene];

    const DC_EVENT_ENTRY* p_entries = p_scene->pEntries;
    const size_t          nb_entry  = p_scene->nbEntry;

    for (uint32_t i = 0; i < nb_entry; ++i)
    {
        const DC_EVENT_ENTRY* p_entry = &p_entries[i];

        if (p_entry->flag & 0x40)
        {
            if (p_entry->pMotion)
                njCnkModDrawMotion(p_entry->pObject, p_entry->pMotion, EventSceneFrame);
            else
                njCnkModDrawObject(p_entry->pObject);
        }
    }
}

static void
EventDisplayerMod(TASK* tp)
{
    if (!EventFileLoadAttempted)
    {
        EventCurModHeader = EventLoadModifierFile();
        EventFileLoadAttempted = true;
    }

    if (DisableCutscene || CutsceneMode == 7 || CutsceneMode == 8 || CutsceneMode == 2 || 0.0f == EventFrame)
        return;

    if (!EventCurModHeader || EventCurModHeader->nbScene != *(int*)(0x0204FE28))
        return;

    EventDisplayMod(0);
    EventDisplayMod(EventScene);
}

static void
EventDestructor(TASK* tp)
{
    if (EventCurModHeader)
        MemFree(EventCurModHeader);

    EventCurModHeader = NULL;
    EventFileLoadAttempted = false;
}

void
EV_ModifierInit()
{
    WriteJump(0x005FAC80, EventDisplayerMod);
    WritePointer(0x005FBB68, EventDestructor);
}