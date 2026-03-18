/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** System **********************************************************************************/
#include <samt/shinobi/sg_maloc.h>  /* symalloc                                                 */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

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
/****** Static **********************************************************************************/
static NJS_TEXMANAGE*
rjSearchTexManage(Uint32 globalIndex)
{
    if ( _nj_texmanagesize <= 0 )
    {
        return nullptr;
    }

    const Sint32  nb_texman = _nj_texmanagesize;
    NJS_TEXMANAGE* p_texman = _nj_texmanage;

    for ( Int i = 0; i < nb_texman; ++i, ++p_texman )
    {
        NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

        if ( p_texsys && p_texsys->globalIndex == globalIndex )
        {
            return p_texman;
        }
    }

    return nullptr;
}

/****** Texlist *********************************************************************************/
Sint32
rjSetTexture(NJS_TEXLIST* texlist)
{
    _nj_curr_ctx_->texlist = texlist;
    return 1;
}

NJS_TEXLIST*
rjGetCurrentTexlist(void)
{
    return _nj_curr_ctx_->texlist;
}

/****** Set Texture *****************************************************************************/
Sint32
rjSetTextureNum(Uint32 n)
{
    Sint32 retcode;

    NJS_TEXMANAGE* p_texman;
    NJS_TEXSYSTEM* p_texsys;

    NJS_TEXLIST* const ptls = _nj_curr_ctx_->texlist;

    if ( !ptls || ptls->nbTexture <= n )
    {
    TEX_ERR:
        p_texman = (NJS_TEXMANAGE*) texture_rf_texerr[0].texaddr;
        p_texsys = p_texman->texsys;

        retcode = -1;
    }
    else
    {
        p_texman = (NJS_TEXMANAGE*) ptls->textures[n].texaddr;

        if (!p_texman) goto TEX_ERR;

        p_texsys = p_texman->texsys;

        if (!p_texsys) goto TEX_ERR;

        retcode = 1;
    }

    // ignore this warning, it's wrong
    _nj_curr_ctx_->texture = &p_texsys->texsurface;
    _nj_curr_ctx_->gbix    = p_texsys->globalIndex;
    _nj_curr_ctx_->bank    = p_texman->bank;
    _nj_curr_ctx_->texnum  = n;

    return retcode;
}

Sint32
rjSetTextureNumG(Uint32 globalIndex)
{
    Sint32 retcode;

    NJS_TEXMANAGE* p_texman = rjSearchTexManage(globalIndex);

    if ( !p_texman )
    {
        p_texman = (NJS_TEXMANAGE*) texture_rf_texerr[0].texaddr;
        retcode = -1;
    }
    else
    {
        retcode = 1;
    }

    // texsystem always exists at this point
    NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

    _nj_curr_ctx_->texture = &p_texsys->texsurface;
    _nj_curr_ctx_->gbix    = p_texsys->globalIndex;
    _nj_curr_ctx_->bank    = p_texman->bank;
    _nj_curr_ctx_->texnum  = -1;

    return retcode;
}

/****** Texture Limit ***************************************************************************/
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

/****** Conversion ******************************************************************************/
static Sint32 __fastcall
___SetTextureNum(Uint32 n)
{
    return rjSetTextureNum(n);
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

    /****** Func Hook ***********************************************************************/

    WriteJump(0x0042ED30, ___SetTextureNum);
}
