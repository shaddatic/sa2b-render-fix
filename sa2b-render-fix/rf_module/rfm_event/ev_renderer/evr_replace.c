/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/samdl.h>             /* samdl                                                    */
#include <samt/string.h>            /* str                                                      */
#include <samt/modloader.h>         /* modloader                                                */
#include <samt/config.h>            /* config                                                   */
#include <samt/memory.h>            /* memory                                                   */
#include <samt/writeop.h>           /* write jump                                               */
#include <samt/model.h>             /* get node                                                 */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings                  */

/********************************/
/*  Constants                   */
/********************************/
/****** Large Buffer ***************************************************************************/
#define BUF_SIZE        (512)

/********************************/
/*  Structures                  */
/********************************/
/****** Cache ***********************************************************************************/
typedef struct
{
    char* str;                      /* file path                                                */
    void* mem;                      /* loaded memory                                            */
}
REPLACE_CACHE;

/********************************/
/*  Game Defs                   */
/********************************/
/****** Large Buffer ***************************************************************************/
#define ReplCache           DATA_ARY(REPLACE_CACHE, 0x01DEFE20, [0x100000 / 2])
#define ReplStrs            DATA_ARY(c8           , 0x01EEFE20, [0x100000 * sizeof(int)])

/********************************/
/*  Variables                   */
/********************************/
/****** Memory Cache ****************************************************************************/
static isize MemCacheCount;
static void** MemCacheList;

/****** Replace String Index ********************************************************************/
static isize StringIndex;

/****** Path Buffers ***************************************************************************/
static c8* BasePath;
static c8* PathBuffer;

/********************************/
/*  Source                      */
/********************************/
/****** Cache ***********************************************************************************/
static void*
ReplaceCacheFind(const c8* puPath)
{
    const isize nb_mem = MemCacheCount;

    for ( isize i = 0; i < nb_mem; ++i )
    {
        if ( !ReplCache[i].str )
        {
            continue;
        }

        if ( mtStrMatch(ReplCache[i].str, puPath, STR_NOMAX) )
        {
            return ReplCache[i].mem;
        }
    }

    return nullptr;
}

static void
ReplaceCacheAdd(const c8* puPath, void* pMem)
{
    if ( !pMem )
    {
        return;
    }

    c8* pu_str = nullptr;

    if ( puPath )
    {
        pu_str = &ReplStrs[StringIndex];

        StringIndex += mtStrCopy(pu_str, puPath, STR_NOMAX);
    }

    const isize i = MemCacheCount++;

    ReplCache[i].str = pu_str;
    ReplCache[i].mem = pMem;
}

/****** Common **********************************************************************************/
static inline mt_config*
StartReplaceIni(const c8* puSrcPath)
{
    const c8* pu_path = mlGetReplacedFile(puSrcPath);

    // if not replaced, eg. original pointer returned
    if ( pu_path == puSrcPath )
    {
        return nullptr;
    }

    mtStrCopy(    BasePath, pu_path, BUF_SIZE );
    mtPathParent( BasePath, nullptr, BUF_SIZE );

    return mtConfigOpen(pu_path);
}

static inline NJS_CNK_OBJECT*
GetReplaceObject(const c8* puName)
{
    if ( mtStrMatch(puName, "null", STR_NOMAX) )
    {
        return nullptr;
    }
    else
    {
        mt_samdl* p_samdl = ReplaceCacheFind(puName);

        if ( !p_samdl )
        {
            mtStrFormat(PathBuffer, BUF_SIZE, "%s/%s", BasePath, puName);

            p_samdl = mtSAModelLoad(PathBuffer, SAMDL_NOFLAG);

            ReplaceCacheAdd(puName, p_samdl);
        }

        return p_samdl->pChunk;
    }
}

static inline NJS_MOTION*
GetReplaceMotion(const c8* puName)
{
    if ( mtStrMatch(puName, "null", STR_NOMAX) )
    {
        return nullptr;
    }
    else
    {
        mt_saanim* p_saanim = ReplaceCacheFind(puName);

        if ( !p_saanim )
        {
            mtStrFormat(PathBuffer, BUF_SIZE, "%s/%s", BasePath, puName);

            p_saanim = mtSAAnimLoad(PathBuffer, SAANIM_NOFLAG);

            ReplaceCacheAdd(puName, p_saanim);
        }

        return p_saanim->pMotion;
    }
}

/****** Replace Attribute ***********************************************************************/
static void
ReplaceEventSceneEntry(isize ixEvent, isize ixScene, isize ixEntry)
{
    EVENT_ENTRY* p_this_entry = &EventData.pScenes[ixScene].pEntries[ixEntry];

    mtStrFormat(PathBuffer, BUF_SIZE, "resource/gd_PC/EVENT/e%04i_rf/scene%03i_entry%03i.ini", ixEvent, ixScene, ixEntry);

    mt_config* const p_cnf = StartReplaceIni(PathBuffer);

    if ( !p_cnf )
    {
        return;
    }

    RF_DbgExtra("Reading ini '/e%04i_rf/scene%03i_entry%03i.ini'", ixEvent, ixScene, ixEntry);

    /** Object **/

    const c8* pu_object = mtConfigGetString(p_cnf, NULL, "object", nullptr);

    if ( pu_object )
    {
        p_this_entry->pObject = GetReplaceObject( pu_object );
    }

    /** Motion **/

    const c8* pu_motion = mtConfigGetString(p_cnf, NULL, "motion", nullptr);

    if ( pu_motion )
    {
        p_this_entry->pMotion = GetReplaceMotion( pu_motion );
    }

    /** Motion Shape **/

    const c8* pu_shape = mtConfigGetString(p_cnf, NULL, "shape", nullptr);

    if ( pu_shape )
    {
        p_this_entry->pShape = GetReplaceMotion( pu_shape );
    }

    /** Flags **/

    const u32 attr = mtConfigGetHex(p_cnf, NULL, "attr", 0xFFFFFFFF);

    if ( attr != 0xFFFFFFFF )
    {
        p_this_entry->attr = attr;
    }

    /** Layer **/

    const u32 layer = mtConfigGetInt(p_cnf, NULL, "layer", -1);

    if ( layer != -1 )
    {
        p_this_entry->layer = layer;
    }

    /** End Config **/

    mtConfigFree(p_cnf);
}

static void
ReplaceEventSceneBig(isize ixEvent, isize ixScene)
{
    EVENT_BIG* p_big = EventData.pScenes[ixScene].pBig;

    mtStrFormat(PathBuffer, BUF_SIZE, "resource/gd_PC/EVENT/e%04i_rf/scene%03i_big.ini", ixEvent, ixScene);

    mt_config* const p_cnf = StartReplaceIni(PathBuffer);

    if ( !p_cnf )
    {
        return;
    }

    RF_DbgExtra("Reading ini '/e%04i_rf/scene%03i_big.ini'", ixEvent, ixScene);

    /** Object **/

    const c8* pu_object = mtConfigGetString(p_cnf, NULL, "object", nullptr);

    if ( pu_object )
    {
        p_big->pObject = GetReplaceObject( pu_object );
    }

    /** Motion Count **/

    const isize nb_motion = mtConfigGetInt(p_cnf, NULL, "motion_num", -1);

    if ( nb_motion != -1 )
    {
        c8 buf[16];

        if ( nb_motion > p_big->nbMotion )
        {
            EVENT_BIG_MOTION* p_bigmot = mtCalloc(EVENT_BIG_MOTION, nb_motion);

            ReplaceCacheAdd(NULL, p_bigmot);

            p_big->pMotions = p_bigmot;
        }

        for ( isize i = 0; i < nb_motion; ++i )
        {
            mtStrFormat(buf, 16, "motion%03i", i);

            /** Motion **/

            const c8* pu_motion = mtConfigGetString(p_cnf, buf, "motion", nullptr);

            if ( pu_motion )
            {
                p_big->pMotions[i].pMotion = GetReplaceMotion( pu_motion );
            }

            /** Motion Shape **/

            const c8* pu_shape = mtConfigGetString(p_cnf, buf, "shape", nullptr);

            if ( pu_shape )
            {
                p_big->pMotions[i].pShape = GetReplaceMotion( pu_shape );
            }
        }

        p_big->nbMotion = nb_motion;
    }

    /** Loop Motion **/

    const int motion_loop = mtConfigGetInt(p_cnf, NULL, "motion_loop", -1);

    if ( motion_loop != -1 )
    {
        p_big->bLoopMotion = motion_loop;
    }

    /** End Config **/

    mtConfigFree(p_cnf);
}

static void
ReplaceEventSceneCamera(isize ixEvent, isize ixScene)
{
    mtStrFormat(PathBuffer, BUF_SIZE, "resource/gd_PC/EVENT/e%04i_rf/scene%03i_camera.ini", ixEvent, ixScene);

    mt_config* const p_cnf = StartReplaceIni(PathBuffer);

    if ( !p_cnf )
    {
        return;
    }

    RF_DbgExtra("Reading ini '/e%04i_rf/scene%03i_camera.ini'", ixEvent, ixScene);

    EVENT_SCENE* p_scene = &EventData.pScenes[ixScene];

    const isize nb_motion = mtConfigGetInt(p_cnf, NULL, "motion_num", -1);

    if ( nb_motion != -1 )
    {
        c8 buf[16];

        if ( nb_motion > p_scene->nbCameraMotion )
        {
            NJS_MOTION** p_motions = mtCalloc(NJS_MOTION*, nb_motion);

            ReplaceCacheAdd(NULL, p_motions);

            p_scene->pCameraMotions = p_motions;
        }

        for ( isize i = 0; i < nb_motion; ++i )
        {
            mtStrFormat(buf, 16, "motion%03i", i);

            /** Motion **/

            const c8* pu_motion = mtConfigGetString(p_cnf, buf, "motion", nullptr);

            if ( pu_motion )
            {
                p_scene->pCameraMotions[i] = GetReplaceMotion( pu_motion );
            }
        }

        p_scene->nbCameraMotion = nb_motion;
    }

    /** End Config **/

    mtConfigFree(p_cnf);
}

static void
ReplaceEventEquipment(isize ixEvent)
{
    mtStrFormat(PathBuffer, BUF_SIZE, "resource/gd_PC/EVENT/e%04i_rf/equipment.ini", ixEvent);

    mt_config* const p_cnf = StartReplaceIni(PathBuffer);

    if ( !p_cnf )
    {
        return;
    }

    RF_DbgExtra("Reading ini '/e%04i_rf/equipment.ini'", ixEvent);

    EVENT_EQUIPMENT* p_equip = EventData.pEquipment;

    const isize nb_equip = mtConfigGetInt(p_cnf, NULL, "equipment_num", -1);

    if ( nb_equip != -1 )
    {
        c8 buf[16];

        for ( isize i = 0; i < nb_equip; ++i )
        {
            mtStrFormat(buf, 16, "equipment%03i", i);

            /** Motion **/

            const c8* pu_attach = mtConfigGetString(p_cnf, buf, "attach_object", nullptr);

            if ( pu_attach )
            {
                mt_samdl* p_samdl = ReplaceCacheFind( pu_attach );

                if ( p_samdl )
                {
                    NJS_CNK_OBJECT* p_obj = p_samdl->pChunk;

                    p_equip[i].pAttachRoot = p_obj;

                    const i32 node0 = mtConfigGetInt(p_cnf, buf, "attach_node0", -1);
                    const i32 node1 = mtConfigGetInt(p_cnf, buf, "attach_node1", -1);

                    if ( node0 > 0 )
                    {
                        p_equip[i].Equipment[0].pAttach = mtCnkGetNode(p_obj, node0);
                    }

                    if ( node1 > 0 )
                    {
                        p_equip[i].Equipment[1].pAttach = mtCnkGetNode(p_obj, node1);
                    }
                }
            }

            const c8* pu_object0 = mtConfigGetString(p_cnf, buf, "object0", nullptr);
            const c8* pu_object1 = mtConfigGetString(p_cnf, buf, "object1", nullptr);

            if ( pu_object0 )
            {
                p_equip[i].Equipment[0].pObject = GetReplaceObject( pu_object0 );
            }

            if ( pu_object1 )
            {
                p_equip[i].Equipment[1].pObject = GetReplaceObject( pu_object1 );
            }
        }
    }

    /** End Config **/

    mtConfigFree(p_cnf);
}

/****** Start/End *******************************************************************************/
void
EVR_EndReplaceAttr(void)
{
    if ( MemCacheList )
    {
        const isize nb_mem = MemCacheCount;
        void**       p_mem = MemCacheList;

        for ( isize i = 0; i < nb_mem; ++i )
        {
            mtFree(p_mem[i]);
        }

        mtFree(p_mem);

        MemCacheList = nullptr;
    }
}

void
EVR_StartReplaceAttr(void)
{
    EVR_EndReplaceAttr();

    MemCacheCount = 0;
    StringIndex   = 0;

    c8* mem_buffer = mtAlloc(c8, BUF_SIZE*2);

    PathBuffer = &mem_buffer[0];
    BasePath   = &mem_buffer[BUF_SIZE];

    const isize ix_event = EventNum;

    const isize nb_scene = EventData.nbScene + 1;

    for ( int ix_scene = 0; ix_scene < nb_scene; ++ix_scene )
    {
        const isize nb_entry = EventData.pScenes[ix_scene].nbEntry;

        ReplaceEventSceneBig(ix_event, ix_scene);
        ReplaceEventSceneCamera(ix_event, ix_scene);

        for ( int ix_entry = 0; ix_entry < nb_entry; ++ix_entry )
        {
            ReplaceEventSceneEntry(ix_event, ix_scene, ix_entry);
        }
    }

    ReplaceEventEquipment(ix_event);

    mtFree(mem_buffer);

    if ( !MemCacheCount )
    {
        return;
    }

    const isize nb_mem = MemCacheCount;
    void**       p_mem = mtAlloc(void*, nb_mem);

    for ( isize i = 0; i < nb_mem; ++i )
    {
        p_mem[i] = ReplCache[i].mem;
    }

    MemCacheList = p_mem;
}
