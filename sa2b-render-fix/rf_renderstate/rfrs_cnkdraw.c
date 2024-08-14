/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_renderstate/rfrs_internal.h> /* parent & siblings                      */

/************************/
/*  Source Structures   */
/************************/
/****** Kill Func List **************************************************************/
typedef struct
{
    u32 addr;
    int func;
}
CNK_FUNCCALL;

/************************/
/*  Source Data         */
/************************/
/****** Kill Func List **************************************************************/
static CNK_FUNCCALL CnkFuncs[] =
{
    { .addr = 0x0042CD31 },
    { .addr = 0x0042CD70 },
    { .addr = 0x0042CD8C },
    { .addr = 0x0042CDDA },
    { .addr = 0x0042CDFE },
    { .addr = 0x0042CE56 },
    { .addr = 0x0042CE7D },
    { .addr = 0x0042CEA8 },
    { .addr = 0x0042CEBA },
};

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
CnkStripSetHide(void)
{
    static bool s_func_got;

    if (!s_func_got)
    {
        for (int i = 0; i < ARYLEN(CnkFuncs); ++i)
            CnkFuncs[i].func = *(s32*)(CnkFuncs[i].addr+1);

        s_func_got = true;
    }

    for (int i = 0; i < ARYLEN(CnkFuncs); ++i)
    {
        *(u8*) (CnkFuncs[i].addr)   = 0x90;
        *(u32*)(CnkFuncs[i].addr+1) = 0x90909090;
    }
}

static void
CnkStripSetDraw(void)
{
    for (int i = 0; i < ARYLEN(CnkFuncs); ++i)
    {
        *(u8*) (CnkFuncs[i].addr)   = 0xE8;
        *(s32*)(CnkFuncs[i].addr+1) = CnkFuncs[i].func;
    }
}

/****** Extern **********************************************************************/
void
SetChunkStripHideMode(bool bHide)
{
    static bool s_last_md;

    if (bHide == s_last_md)
        return;

    s_last_md = bHide;

    bHide ? CnkStripSetHide() : CnkStripSetDraw();
}
