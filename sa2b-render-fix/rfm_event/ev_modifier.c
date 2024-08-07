#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/file.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>
#include <sa2b/model.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>

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

#define CheckEventPointer(_ptr, _offset)       ((uintptr_t)(_ptr) && (uintptr_t)(_ptr) < (uintptr_t)(_offset))
#define ResolveEventPointer(_ptr, _offset)     (*(uintptr_t*)&(_ptr) += (uintptr_t)(_offset))

static void
FixChunkObjectPointers(NJS_CNK_OBJECT* pObject, uintptr_t offset)
{
    if (CheckEventPointer(pObject->model, offset))
    {
        ResolveEventPointer(pObject->model, offset);

        NJS_CNK_MODEL* p_model = pObject->model;

        ResolveEventPointer(p_model->vlist, offset);
        ResolveEventPointer(p_model->plist, offset);
    }
    if (CheckEventPointer(pObject->child, offset))
    {
        ResolveEventPointer(pObject->child, offset);
        FixChunkObjectPointers(pObject->child, offset);
    }
    if (CheckEventPointer(pObject->sibling, offset))
    {
        ResolveEventPointer(pObject->sibling, offset);
        FixChunkObjectPointers(pObject->sibling, offset);
    }
}

static void
ResolveMotionDataPointers(void* pMotionData, size_t nbObject, size_t nbFactor, uintptr_t offset)
{
    void** pp_key_og = (void**)pMotionData;

    for (size_t i = 0; i < nbObject; ++i)
    {
        for (size_t j = 0; j < nbFactor; ++j)
        {
            if (CheckEventPointer(*pp_key_og, offset))
                ResolveEventPointer(*pp_key_og, offset);

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

    for (int i = 0, m = 1; i < BITSIN(pMotion->type); ++i, m <<= 1)
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

    if (CheckEventPointer(pEventHead->pScenes, offset))
        ResolveEventPointer(pEventHead->pScenes, offset);
    else
        return; // Idk what to do in this case, so I won't worry about it :)

    const size_t nb_scene = pEventHead->nbScene;

    for (uint32_t i = 0; i <= nb_scene; ++i)
    {
        DC_EVENT_SCENE* p_scene = &pEventHead->pScenes[i];

        if (CheckEventPointer(p_scene->pEntries, offset))
            ResolveEventPointer(p_scene->pEntries, offset);
        else
            continue;

        const size_t nb_entry = p_scene->nbEntry;

        for (uint32_t j = 0; j < nb_entry; ++j)
        {
            DC_EVENT_ENTRY* p_entry = &p_scene->pEntries[j];

            if (CheckEventPointer(p_entry->pObject, offset))
            {
                ResolveEventPointer(p_entry->pObject, offset);

                FixChunkObjectPointers(p_entry->pObject, offset);

                if (CheckEventPointer(p_entry->pMotion, offset))
                {
                    ResolveEventPointer(p_entry->pMotion, offset);
                    ResolveEventPointer(p_entry->pMotion->mdata, offset);

                    const size_t nb_object = MDL_CountObject(p_entry->pObject);

                    ResolveMotionPointers(p_entry->pMotion, offset, nb_object);
                }
            }
        }
    }
}

static DC_EVENT_HEADER*
EventLoadModifierFile(void)
{
    char str[260];

    snprintf(str, sizeof(str), "%s/evmod/e%04dmodifier.bin", GetModPath(), EventNum);

    DC_EVENT_HEADER* fevent = uFileLoad(str, NULL);

    if (!fevent)
    {
        OutputFormat("Failed to load: %s", str);
        return NULL;
    }

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
EV_ModifierInit(void)
{
    WriteJump(0x005FAC80, EventDisplayerMod);
    WritePointer(0x005FBB68, EventDestructor);
}
