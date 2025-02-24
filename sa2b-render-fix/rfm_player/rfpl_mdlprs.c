/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/memory.h>        /* memory                                           */

/****** Utility *********************************************************************/
#include <samt/util/endian.h>   /* endian                                           */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/player.h>  /* misc                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/************************/
/*  Constants           */
/************************/
/****** Chunk Max Offsets ***********************************************************/
#define NJD_BITSOFF_MAX     (NJD_CB_DP+1)
#define NJD_TINYOFF_MAX     (NJD_CT_TID2+1)
#define NJD_MATOFF_MAX      (NJD_CM_DAS2+1)
#define NJD_VOLOFF_MAX      (NJD_CO_ST+1)
#define NJD_STRIPOFF_MAX    (NJD_CS_UVH2+1)

/****** Check and Fix Pointer *******************************************************/
#define CHK_POINTER(ptr, off)   ((uintptr_t)(ptr) < (uintptr_t)(off))
#define FIX_POINTER(ptr, off)   (*(uintptr_t*)&(ptr) += (uintptr_t)(off))

/************************/
/*  Structures          */
/************************/
/****** Core Toolkit ****************************************************************/
typedef struct
{
    const void** pp;            /* pointer list                                     */
    int          num;           /* pointer list size in memory                      */
}
FIX_HISTORY;

/************************/
/*  Source              */
/************************/
/************************************************************************************/
/*
*   Big Endian
*/

/****** Fix History *****************************************************************/
static FIX_HISTORY*
CreateFixHistory(void)
{
    FIX_HISTORY* p_history = mtAlloc(FIX_HISTORY, 1);

    p_history->pp  = mtCalloc(void*, 128);
    p_history->num = 128;

    return p_history;
}

static void
FreeFixHistory(FIX_HISTORY* pHistory)
{
    mtFree(pHistory->pp);
    mtFree(pHistory);
}

static bool
CheckAndAddToFixHistory(const void* p, FIX_HISTORY* pHistory)
{
    const int num = pHistory->num;
    const void** pp = pHistory->pp;

    for (int i = 0; i < num; ++i, ++pp)
    {
        if (*pp == nullptr)
        {
            *pp = p;
            return false;
        }

        if (p == *pp)
            return true;
    }

    /** If we got here without returning, the list has been maxed out. Realloc more
      room and clear new space. **/

    mtRecalloc(&pHistory->pp, void*, num, num * 2);

    pHistory->num = num * 2;

    return CheckAndAddToFixHistory(p, pHistory); // try again
}

/****** Byteswap ********************************************************************/
static void
ByteswapVList(Sint32* pVList)
{
    Sint32* vlist = pVList;

    for ( ; ; )
    {
        EndianSwap32(vlist);

        const int type = ((u8*)vlist)[0];

        if (type == NJD_CE)
        {
            /** NJD_ENDOFF **/
            break;
        }

        /** Next data chunk **/
        Sint32* const next_vlist = vlist + (((u16*)vlist)[1] + 1);

        vlist++; // skip header

        for ( ; vlist < next_vlist; ++vlist)
        {
            EndianSwap32(vlist);
        }
    }
}

static void
ByteswapPList(Sint16* pPList)
{
    Sint16* plist = pPList;
    int type;

    for ( ; ; )
    {
        EndianSwap16(plist);

        type = ((u8*)plist)[0];

        if (type == NJD_CE)
        {
            /** NJD_ENDOFF **/
            break;
        }

        if (type < NJD_BITSOFF_MAX) // null and bits
        {
            /** NJD_BITSOFF **/

            /** Next offset **/
            ++plist;
            continue;
        }

        if (type < NJD_TINYOFF_MAX) // tiny
        {
            /** NJD_TINYOFF **/
            EndianSwap16(plist+1);

            /** Next offset **/
            plist += 2;
            continue;
        }

        if (type < NJD_STRIPOFF_MAX) // material, volume, and strip
        {
            /** NJD_STRIPOFF **/
            EndianSwap16(plist+1); // endiswap size

            Sint16* const next_plist = plist + (((u16*)plist)[1] + 2);

            plist += 2; // skip 'type' and 'size'

            for ( ; plist < next_plist; ++plist)
            {
                EndianSwap16(plist);
            }

            continue;
        }

        /** An error occured, stop **/
        break;
    }
}

static void
FixChunkPointersAndByteswap(NJS_CNK_OBJECT* pObject, uintptr_t offset, FIX_HISTORY* pHistory)
{
    do
    {
        if ( !CheckAndAddToFixHistory(pObject, pHistory) )
        {
            EndianSwap32(&pObject->evalflags);

            EndianSwap32(&pObject->pos[0]);
            EndianSwap32(&pObject->pos[1]);
            EndianSwap32(&pObject->pos[2]);

            EndianSwap32(&pObject->ang[0]);
            EndianSwap32(&pObject->ang[1]);
            EndianSwap32(&pObject->ang[2]);

            EndianSwap32(&pObject->scl[0]);
            EndianSwap32(&pObject->scl[1]);
            EndianSwap32(&pObject->scl[2]);

            // EndianSwap32(&pObject->re_quat);

            if (pObject->model)
            {
                EndianSwap32(&pObject->model);

                FIX_POINTER(pObject->model, offset);

                NJS_CNK_MODEL* p_model = pObject->model;

                if ( !CheckAndAddToFixHistory(p_model, pHistory) )
                {
                    if (p_model->vlist)
                    {
                        EndianSwap32(&p_model->vlist);

                        FIX_POINTER(p_model->vlist, offset);

                        if ( !CheckAndAddToFixHistory(p_model->vlist, pHistory) )
                        {
                            ByteswapVList(p_model->vlist);
                        }
                    }

                    if (p_model->plist)
                    {
                        EndianSwap32(&p_model->plist);

                        FIX_POINTER(p_model->plist, offset);

                        if ( !CheckAndAddToFixHistory(p_model->plist, pHistory) )
                        {
                            ByteswapPList(p_model->plist);
                        }
                    }

                    EndianSwap32(&p_model->center.x);
                    EndianSwap32(&p_model->center.y);
                    EndianSwap32(&p_model->center.z);

                    EndianSwap32(&p_model->r);
                }
            } 

            if (pObject->child)
            {
                EndianSwap32(&pObject->child);

                FIX_POINTER(pObject->child, offset);

                FixChunkPointersAndByteswap(pObject->child, offset, pHistory);
            }

            if (pObject->sibling)
            {
                EndianSwap32(&pObject->sibling);

                FIX_POINTER(pObject->sibling, offset);
            }
        }

        pObject = pObject->sibling;
    }
    while (pObject);
}

/************************************************************************************/
/*
*   Little Endian
*/

/****** Fix Pointers ****************************************************************/
static void
FixChunkPointers(NJS_CNK_OBJECT* pObject, uintptr_t offset)
{
    do
    {
        if (pObject->model && CHK_POINTER(pObject->model, offset))
        {
            FIX_POINTER(pObject->model, offset);

            NJS_CNK_MODEL* p_model = pObject->model;

            if (p_model->vlist && CHK_POINTER(p_model->vlist, offset))
            {
                FIX_POINTER(p_model->vlist, offset);
            }
            if (p_model->plist && CHK_POINTER(p_model->plist, offset))
            {
                FIX_POINTER(p_model->plist, offset);
            }
        }

        if (pObject->child && CHK_POINTER(pObject->child, offset))
        {
            FIX_POINTER(pObject->child, offset);

            FixChunkPointers(pObject->child, offset);
        }

        if (pObject->sibling && CHK_POINTER(pObject->sibling, offset))
        {
            FIX_POINTER(pObject->sibling, offset);
        }

        pObject = pObject->sibling;
    }
    while (pObject);
}

/************************************************************************************/
/*
*   Fix Player Object List
*/

/****** Fix Object List *************************************************************/
static PL_OBJECT*
NEW_LoadPlayerMDL(PL_OBJECT* pObjList)
{
    if (!pObjList || pObjList[0].index == -1)
        return nullptr;

    const uintptr_t baseptr = (uintptr_t) pObjList;

    /** Get Big Endian Mode:
    
        We're just checking if the upper 2 bytes of the index value are set, as
      that would mean the bytes are flipped as the model ID's never exceed 500-ish;
      so, this check can't fail in regular circumstances.
        We need to loop through every index in the list because Sonic uses an ID of
      0. That will always return Little Endian, every time. **/

    bool is_be = false;

    for (int i = 0; ; ++i)
    {
        if (pObjList[i].index == -1)
            break;

        if (pObjList[i].index & 0xFFFF0000)
        {
            is_be = true;
            break;
        }
    }

    /** Fix Object List **/

    PL_OBJECT* obj_list = pObjList;

    if ( is_be ) // big endian
    {
        /** We use a fix history here to remember what we have and have not fixed.
          We don't need this in little endian because we can just do a simple
          greater-than check, but with byteswapping we have absolutely no idea what
          has an has not been byteswapped.
            All it does is store pointers to objects, models, vlists, and plists
          that have already had their bytes swapped. With this info, we can avoid
          byteswapping or fixing pointers twice which is an issue in the vanilla
          game, which is why we're replacing it here. Adding little endian support
          was just another upside. **/

        FIX_HISTORY* p_history = CreateFixHistory();

        do
        {
            EndianSwap32(&obj_list->index);
            EndianSwap32(&obj_list->pObject);

            FIX_POINTER(obj_list->pObject, baseptr);

            CHAR_OBJECTS[obj_list->index].pObject = obj_list->pObject;

            FixChunkPointersAndByteswap(obj_list->pObject, baseptr, p_history);

            ++obj_list;
        }
        while (obj_list->index != -1);

        FreeFixHistory(p_history);
    }
    else // little endian
    {
        do
        {
            FIX_POINTER(obj_list->pObject, baseptr);

            CHAR_OBJECTS[obj_list->index].pObject = obj_list->pObject;

            FixChunkPointers(obj_list->pObject, baseptr);

            ++obj_list;
        }
        while (obj_list->index != -1);
    }

    return pObjList;
}

__declspec(naked)
static void
___LoadPlayerMDL(void)
{
    __asm
    {
        push        eax                 // returned ptr from LoadPRS
        call        NEW_LoadPlayerMDL
        add esp,    4
        retn
    }
}

/************************************************************************************/
/*
*   Init
*/

/****** Init ************************************************************************/
void
RFPL_ModelPrsInit(void)
{
    /** Patch the PRS loading code, have to do it this way because of the mod
      hooking this function first. So, we hook just after the LoadPRS function is
      called, then handle the rest from there. The NOP call just forces a quick
      return after we're done. **/

    WriteNOP( 0x00459598, 0x0045959E);
    WriteCall(0x00459598, ___LoadPlayerMDL);
}
