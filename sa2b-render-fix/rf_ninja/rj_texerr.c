/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

#define SAMT_INCL_INTERNAL

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

#undef SAMT_INCL_INTERNAL

/****** Game ************************************************************************/
#include <samt/sonic/texture.h> /* texload                                          */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Self ************************************************************************/
#include <rf_ninja/rj_internal.h> /* parent & siblings                              */

/************************/
/*  Data                */
/************************/
/****** Tex Memory ******************************************************************/
static NJS_TEXSYSTEM TexerrTexsys[1] = { { .globalIndex = -1 } };
static NJS_TEXMANAGE TexerrTexman[1] = { { .bank = -1 } };

/****** Texlist *********************************************************************/
EXTERN NJS_TEXLIST texlist_rf_texerr[];

/************************/
/*  Source              */
/************************/
/****** Init ************************************************************************/
void
RFD_TexerrInit(void)
{
    // backup current tex memory
    const Int           nb_texsys = _nj_texsyssize;
    const Int           nb_texman = _nj_texmanagesize;
    NJS_TEXSYSTEM* const p_texsys = _nj_texsys;
    NJS_TEXMANAGE* const p_texman = _nj_texmanage;

    // put texerr memory
    _nj_texmanagesize = ARYLEN( TexerrTexsys );
    _nj_texsyssize    = ARYLEN( TexerrTexman );
    _nj_texsys        = TexerrTexsys;
    _nj_texmanage     = TexerrTexman;

    njLoadTexture(texlist_rf_texerr);

    // restore tex memory
    _nj_texsyssize    = nb_texsys;
    _nj_texmanagesize = nb_texman;
    _nj_texsys        =  p_texsys;
    _nj_texmanage     =  p_texman;
}
