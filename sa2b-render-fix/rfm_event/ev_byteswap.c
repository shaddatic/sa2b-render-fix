#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/file.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>
#include <sa2b/model.h>

/** Util **/
#include <sa2b/util/endian.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_draw.h>
#include <rf_eventinfo.h>

#define PTR_OFFSET      (0x7F210040)

#define FixPointer(p)   (*(uintptr_t*)p) -= PTR_OFFSET;

static bool
EV_IsByteswapped(const void* p)
{
    return ( (uintptr_t)(&EventData) <= (uintptr_t)(p) && (uintptr_t)(0x0241FE20) > (uintptr_t)(p) );
}

const int EventAnimateTexture_p = 0x006021A0;
static void
EventAnimateTexture(EventTexAnimSub1* a1, int a2, int a3)
{
    __asm
    {
        push[a3]
        mov edi, [a2]
        mov edx, [a1]
        call EventAnimateTexture_p
        add esp, 4
    }
}

const int EndiswapEventTexAnim1_p = 0x005FE8A0;
static void
EndiswapEventTexAnim1(EventTexAnimSub1* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim1_p
    }
}

const int EndiswapEventTexAnim0_p = 0x005FE670;
static void
EndiswapEventTexAnim0(EventTexAnimSub0* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim0_p
    }
}

static void
EventByteSwapTexAnim(EventTexAnim* p)
{
    EndianSwap(&p->count);

    EndianSwap(&p->somethingelse);

    if (p->somethingelse)
        *(int32_t*)&p->somethingelse -= PTR_OFFSET; // idky I'm doing this

    EndianSwap(&p->something);

    if (p->something)
        *(int32_t*)&p->something -= PTR_OFFSET;

    for (EventTexAnimSub1* ptexanim = p->somethingelse; ptexanim->entries; ++ptexanim)
    {
        if (p->somethingelse)
            EndiswapEventTexAnim1(ptexanim);
    }

    for (int i = 0; i < p->count; ++i)
    {
        if (p->something)
            EndiswapEventTexAnim0(&p->something[i]);
    }
}

__declspec(naked)
static void
___EventByteSwapTexAnim(void)
{
    __asm
    {
        push ebx
        call EventByteSwapTexAnim
        pop ebx
        retn
    }
}

static void
EventByteSwapReflection(EV_REFLECT_DATA* pReflect)
{
    EndianSwap(&pReflect->count);

    for (int i = 0; i < 32; ++i)
    {
        EndianSwap(&pReflect->AlphaValues[i]);
    }

    EndianSwap(&pReflect->ReflectionVtxs);

    if (pReflect->ReflectionVtxs)
    {
        FixPointer(&pReflect->ReflectionVtxs);

        const int nb = pReflect->count;

        for (int i = 0; i < nb; ++i)
        {
            NJS_POINT3* p_plane = &pReflect->ReflectionVtxs[i*4];

            EndianSwap(&p_plane[0].x);
            EndianSwap(&p_plane[0].y);
            EndianSwap(&p_plane[0].z);

            EndianSwap(&p_plane[1].x);
            EndianSwap(&p_plane[1].y);
            EndianSwap(&p_plane[1].z);

            EndianSwap(&p_plane[2].x);
            EndianSwap(&p_plane[2].y);
            EndianSwap(&p_plane[2].z);

            EndianSwap(&p_plane[3].x);
            EndianSwap(&p_plane[3].y);
            EndianSwap(&p_plane[3].z);
        }
    }
}

__declspec(naked)
static void
___EventByteSwapReflection(void)
{
    __asm
    {
        push eax
        call EventByteSwapReflection
        pop eax
        retn
    }
}

static void
EventByteSwapMainFile(EventFileHeader* pEvHead)
{
    if (pEvHead->nbScene <= 65535) // is little-endian
        return;

    EndianSwap(&pEvHead->scenes);
    EndianSwap(&pEvHead->texlist);
    EndianSwap(&pEvHead->nbScene);
    EndianSwap(&pEvHead->SpriteSizes);
    EndianSwap(&pEvHead->reflections);
    EndianSwap(&pEvHead->BlareObjects);
    EndianSwap(&pEvHead->MechParts);

    // Other stuff

    EndianSwap(&pEvHead->MilesTails);

    // Other stuff

    EndianSwap(&pEvHead->Equipment);

    EndianSwap(&pEvHead->UVAnims);
    EndianSwap(&pEvHead->dropShadow);

    // Other stuff

    if (pEvHead->UVAnims)
        EventByteSwapTexAnim(pEvHead->UVAnims);
}

void
EV_ByteSwapInit(void)
{
    if (RF_ConfigGetInt(CNF_EVENT_TEXANIM))
    {
        WriteCall(0x005FEFF7, ___EventByteSwapTexAnim);
//      WriteJump(0x005FE320, ___EventByteSwapReflection);
    }
}
