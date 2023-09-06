#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

struct EventTexAnimSub1
{
    NJS_CNK_OBJECT* pObject;
    int entries;
    char gap[4];
};

struct EventTexAnimSub0
{
    int startidx;
    int maxidx;
};

struct EventTexAnim
{
    EventTexAnimSub1* somethingelse;
    EventTexAnimSub0* something;
    int count;
};

const int EventAnimateTexture_p = 0x006021A0;
void
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
void
EndiswapEventTexAnim1(EventTexAnimSub1* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim1_p
    }
}

const int EndiswapEventTexAnim0_p = 0x005FE670;
void
EndiswapEventTexAnim0(EventTexAnimSub0* a1)
{
    __asm
    {
        mov eax, [a1]
        call EndiswapEventTexAnim0_p
    }
}

static void
EndiswapEventTexAnim(EventTexAnim* p)
{
    SwapEndianness(&p->count);

    SwapEndianness(&p->somethingelse);

    if (p->somethingelse)
        *(sint*)&p->somethingelse -= 2132869184; // idky I'm doing this

    SwapEndianness(&p->something);

    if (p->something)
        *(sint*)&p->something -= 2132869184;

    for (int i = 0; i < p->count; ++i)
    {
        if (p->somethingelse)
            EndiswapEventTexAnim1(&p->somethingelse[i]);

        if (p->something)
            EndiswapEventTexAnim0(&p->something[i]);
    }
}

__declspec(naked)
static void
__EndiswapEventTexAnim()
{
    __asm
    {
        push ebx
        call EndiswapEventTexAnim
        pop ebx
        retn
    }
}

#define SECT "event"

void
EventSettings(const config* conf)
{
    if (ConfigGetInt(conf, SECT, "texanim", 1))
    {
        WriteCall(0x005FEFF7, __EndiswapEventTexAnim);
    }
}