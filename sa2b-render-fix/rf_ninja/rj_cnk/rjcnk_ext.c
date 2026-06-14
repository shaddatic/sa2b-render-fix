/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

/****** Utl *************************************************************************************/
#include <samt/util/asm.h>          /* asm helper                                               */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>         /* GX                                               */

/****** SOC *************************************************************************/
#include <samt/soc/shader.h>    /* setshader                                        */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Self ************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                    */

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
ASM_FUNC
static int
CnkVListShadow_Ext(const Sint32* vlist, void* njvtxbuf, int is_not_broken)
{
    // arguments
    ASM_MOVE( eax, ASM_ESP(3+0) ); // is_not_broken
    ASM_PUSH(      ASM_ESP(2+0) ); // njvtxbuf
    ASM_MOVE( ecx, ASM_ESP(1+1) ); // vlist

    // call
    ASM_CALL_R( edx, 0x0042D270 );

    // end arguments
    ASM_ESP_ADD( 1 );

    // return
    ASM_RET( 0 );
}

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
    SetShaderType(SHADER_TYPE_MDL);
    gjStartVertex3D(&_nj_unit_matrix_, 0);

    if ( model->vlist )
    {
        if ( CnkVListShadow_Ext(model->vlist, _nj_vertex_buf_, true) == -1 )
        {
            return CNK_RETN_CLIP;
        }
    }

    if ( model->plist )
    {
        CnkPListShadow_Ext(model->plist, _nj_vertex_buf_);
    }

    return CNK_RETN_OK;
}
