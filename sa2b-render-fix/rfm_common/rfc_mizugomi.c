#include <sa2b/core.h>
#include <sa2b/memutil.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>

#define njDrawSomethingStart    FuncPtr(void, __cdecl, (int), 0x00491160)

const int njDrawSomeSprite_p = 0x00491600;
static void
njDrawSomeSprite(NJS_POINT3* p, int n, float pri, float w, float h, Uint32 col)
{
    __asm
    {
        push[col]
        push[h]
        push[w]
        push[pri]
        push[n]
        mov eax, [p]
        call njDrawSomeSprite_p
        add esp, 20
    }
}

#define texlist_mizugomi_am     DataAry(NJS_TEXLIST, 0x0162DD08, [1])

#define GET_MIZUWK(tp_)     ((MIZUWK*)tp_->mwp) 

typedef struct
{
    NJS_POINT3* p;
    int         n;
}
MIZUWK;

static void
MizugomiDisplayer_AM(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    MIZUWK* const mwp = GET_MIZUWK(tp);

    if (twp->mode)
        return;

    njFogDisable();

    njColorBlendingMode(NJD_SOURCE_COLOR     , NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);

    njPushMatrixEx();

    njTranslateEx(&twp->pos);

    njSetTexture(texlist_mizugomi_am);
    njSetTextureNum(0);

    njDrawSomethingStart(1);
    njDrawSomeSprite(mwp->p, mwp->n, 0.0f, 0.075000003f, 0.075000003f, 0xFF809050);

    njPopMatrixEx();

    njColorBlendingMode(NJD_SOURCE_COLOR     , NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);

    njFogEnable();
}

#define pMizugomiEQ     DataRef(TASK*, 0x01AEFC18)

static void
BGMizugomiEQ(void)
{
    if (pMizugomiEQ)
        pMizugomiEQ->twp->mode = 0;
}

const int SetFogTableNot = 0x006DF9B0;

__declspec(naked)
static void
__BGMizugomiEQ(void)
{
    __asm
    {
        call SetFogTableNot
        jmp BGMizugomiEQ
    }
}

#define texlist_mizugomi_dc     DataPtr(NJS_TEXLIST, 0x00B6F51C)

#define pMizugomiCCK            DataRef(TASK*, 0x01AEE2B0)

static void
BGMizugomiDCOff(void)
{
    if (pMizugomiCCK)
        pMizugomiCCK->twp->mode = 1;
}

static void
BGMizugomiDCOn(void)
{
    if (pMizugomiCCK)
        pMizugomiCCK->twp->mode = 0;
}

const int dcjump = 0x006AB9D0;

__declspec(naked)
static void
__BGMizugomiDCOff(void)
{
    __asm
    {
        call dcjump
        jmp BGMizugomiDCOff
    }
}

__declspec(naked)
static void
__BGMizugomiDCOn(void)
{
    __asm
    {
        add esp, 28h
        jmp BGMizugomiDCOn
    }
}

#define MizugomiCreateCCK   FuncPtr(void, __cdecl, (void), 0x006605D0)

static void
BGMizugomiDCBegin(void)
{
    if (!pMizugomiCCK)
        MizugomiCreateCCK();
}

const int ObjectAsiotoCreate = 0x006F1920;

__declspec(naked)
static void
__BGMizugomiDCBegin(void)
{
    __asm
    {
        call BGMizugomiDCBegin
        jmp ObjectAsiotoCreate
    }
}

void
RFC_MizugomiInit(void)
{
    WriteJump(0x004D6770, MizugomiDisplayer_AM);

    WriteJump(0x00690BC0, __BGMizugomiEQ);

    /** So, Death Chamber is missing this entirely, so to get 
        them to appear I'm using the particle code from Cannons Core K **/

    WriteJump(0x006AB743, __BGMizugomiDCOff);
    WriteJump(0x006AB74A, __BGMizugomiDCOn);

    WritePointer(0x00BA4FD8, 0x00C8A90C); // Switch Texlist
    WritePointer(0x00DBDFD0, 0x00C8A90C); // ^

    WriteCall(0x006AA467, __BGMizugomiDCBegin); // Load CCK particles
}
