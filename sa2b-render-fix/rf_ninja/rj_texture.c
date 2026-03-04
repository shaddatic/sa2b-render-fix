/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/funchook.h>          /* func hook                                                */

/****** System **********************************************************************************/
#include <samt/shinobi/sg_maloc.h>  /* symalloc                                                 */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/texture.h>     /* texload                                                  */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* get config                                               */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** Tex Memory ******************************************************************************/
#define TEXSYS_INITSIZE             (2048)

/********************************/
/*  Data                        */
/********************************/
/****** Tex Memory ******************************************************************************/
static NJS_TEXSYSTEM TexerrTexsys[1] = { { .globalIndex = -1 } };
static NJS_TEXMANAGE TexerrTexman[1] = { { .bank = -1 } };

/****** Texlist *********************************************************************************/
EXTERN NJS_TEXLIST texlist_rf_texerr[];

/********************************/
/*  Game Refs                   */
/********************************/
/****** Tex Memory ******************************************************************************/
#define njReleaseTextureAll_p       FUNC_PTR(void, __cdecl, (void), 0x0042F990)

#define TexManageBuf                DATA_REF(NJS_TEXMANAGE*, 0x01934B00)
#define TexSystemBuf                DATA_REF(NJS_TEXSYSTEM*, 0x01934AF8)

/********************************/
/*  Source                      */
/********************************/
/****** Init ************************************************************************************/
static mt_hookinfo ReleaseTextureAll_hi[1]; 
static void
ChangeTextureLimit(Int ntex)
{
    // make sure the texture system as the addresses we expect
    if ( TexManageBuf != _nj_texmanage || TexSystemBuf != _nj_texsys )
    {
        return;
    }

    // make sure the texture system is empty
    njReleaseTextureAll();

    const Int texmemsize = MIN(_nj_texmanagesize, _nj_texsyssize);

    // if something else has already expanded the textures, stop
    if ( ntex <= texmemsize )
    {
        return;
    }

    // all checks passed, change the texture limit
    syFree(TexManageBuf);
    syFree(TexSystemBuf);

    NJS_TEXMANAGE* p_newmanage = syMalloc( sizeof(NJS_TEXMANAGE) * ntex );
    NJS_TEXSYSTEM* p_newsystem = syMalloc( sizeof(NJS_TEXSYSTEM) * ntex );

    njInitTextureEx(p_newmanage, ntex, p_newsystem, ntex);

    TexManageBuf = p_newmanage;
    TexSystemBuf = p_newsystem;

    RF_DbgInfo("Expanded texture limit to %i, from %i!", ntex, texmemsize);
}

/****** Init ************************************************************************************/
void
RJ_TextureInit(void)
{
    /****** Expand Textures *****************************************************************/

    ChangeTextureLimit(TEXSYS_INITSIZE * CNF_GetInt(CNF_GLOBAL_TEXSYSSIZE));

    /****** Tex Error ***********************************************************************/

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
