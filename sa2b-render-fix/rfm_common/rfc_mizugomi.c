#include <sa2b/core.h>
#include <sa2b/memutil.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>

#define njDrawSomethingStart    FuncPtr(void, __cdecl, (int), 0x00491160)

const int njDrawSomeSprite_p = 0x00491600;
static void
njDrawSomeSprite(NJS_POINT3* a1, int a2, float a3, float a4, float a5, int a6)
{
    __asm
    {
        push[a6]
        push[a5]
        push[a4]
        push[a3]
        push[a2]
        mov eax, [a1]
        call njDrawSomeSprite_p
        add esp, 20
    }
}

#define LODWORD(d) (*(uint32_t*)&d)

static void
DrawMizugomi(TASK* tp)
{
    ANYWK* const mwp = TO_ANYWK(tp->mwp);

    njSetTextureNum(0);
    njDrawSomethingStart(1);
    njDrawSomeSprite((NJS_POINT3*)mwp->work.ptr[0], mwp->work.sl[1], 0.0f, 0.075000003f, 0.075000003f, 0xFF809050);
    njPopMatrixEx();
}

__declspec(naked)
static void
__DrawMizugomiAM(void)
{
    __asm
    {
        push edx
        push ebx
        call DrawMizugomi
        pop ebx
        pop edx
        retn
    }
}

#define pMizugomiEQ DataRef(TASK*, 0x01AEFC18)

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
    WriteNoOP(0x004D67F9, 0x004D6806);
    WriteCall(0x004D67F9, __DrawMizugomiAM);

    WriteJump(0x00690BC0, __BGMizugomiEQ);

    /** So, Death Chamber is missing this entirely, so to get 
        them to appear I'm using the particle code from Cannons Core K **/

    WriteJump(0x006AB743, __BGMizugomiDCOff);
    WriteJump(0x006AB74A, __BGMizugomiDCOn);

    WritePointer(0x00BA4FD8, 0x00C8A90C); // Switch Texlist
    WritePointer(0x00DBDFD0, 0x00C8A90C); // ^

    WriteCall(0x006AA467, __BGMizugomiDCBegin); // Load CCK particles
}
