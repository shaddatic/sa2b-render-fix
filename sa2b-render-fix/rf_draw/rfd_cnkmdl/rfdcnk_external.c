/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>         /* GX                                               */

/****** Game ************************************************************************/
#include <samt/sonic/shaders.h> /* GX                                               */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
#pragma optimize("", off)
static int
CnkVListShadow_Ext(const Sint32* vlist, void* njvtxbuf, int is_not_broken)
{
    static const uintptr_t p = 0x0042D270;

    int result;

    __asm
    {
        mov eax, [is_not_broken]
        push [njvtxbuf]
        mov ecx, [vlist]
        call p
        add esp, 4
        mov [result], eax
    }

    return result;
}
#pragma optimize("", on)

static void
CnkPListShadow_Ext(const Sint16* plist, const void* njvtxbuf)
{
    DATA_REF(void*, 0x0174F7E8) = DATA_REF(void*, 0x0174F7EC);
    FUNC_PTR(void, __cdecl, (const Sint16*, const void*), 0x0042CF30)(plist, njvtxbuf);
    GX_End();
}

int
CnkDrawShadow_Ext(const NJS_CNK_MODEL* model, const void* vbuf)
{
    SetShaders(1);
    gjStartVertex3D(&_nj_unit_matrix_, 0);

    if ( model->vlist )
    {
        if ( CnkVListShadow_Ext(model->vlist, _nj_vertex_buf_, true) == -1 )
        {
            return -1;
        }
    }

    if ( model->plist )
    {
        CnkPListShadow_Ext(model->plist, _nj_vertex_buf_);
    }

    return 0;
}
