/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** System **********************************************************************************/
#include <samt/shinobi/sg_maloc.h>  /* malloc                                                   */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/texture.h>     /* texture                                                  */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rfu_texture.h>            /* self                                                     */

/********************************/
/*  Game Refs                   */
/********************************/
/****** Texname *********************************************************************************/
#define texname_tex                 DATA_ARY(NJS_TEXNAME, 0x01940870, [512])

/********************************/
/*  Source                      */
/********************************/
/****** Create Texlist **************************************************************************/
NJS_TEXLIST*
RFU_CreateTexlist(const c7* fname)
{
    c7 buf[4] = {0};
    NJS_TEXLIST texlist_tex = { .textures = texname_tex, .nbTexture = COUNTOF(texname_tex) };

    for ( isize i = 0; i < COUNTOF(texname_tex); ++i )
    {
        texname_tex[i] = (NJS_TEXNAME){ .filename = buf };
    }

    // if both fail, return
    if ( LoadPakMEM(fname, &texlist_tex) <= 0
    &&   LoadPrsMEM(fname, &texlist_tex) <= 0 )
    {
        return nullptr;
    }

    // if no textures, return
    if ( texlist_tex.nbTexture == 0 )
    {
        return nullptr;
    }

    const isize nb_tname = (isize) texlist_tex.nbTexture;

    byte* p = syMalloc( sizeof(NJS_TEXLIST) + (sizeof(NJS_TEXNAME) * nb_tname) );

    if ( !p )
    {
        njReleaseTexture(&texlist_tex);
        return nullptr;
    }

    NJS_TEXLIST* tlist = (NJS_TEXLIST*)(&p[0]);
    NJS_TEXNAME* tname = (NJS_TEXNAME*)(&p[sizeof(NJS_TEXLIST)]);

    tlist->textures  = tname;
    tlist->nbTexture = nb_tname;

    for ( isize i = 0; i < nb_tname; ++i )
    {
        tname[i] = (NJS_TEXNAME){
            .filename = nullptr,
            .attr     = texname_tex[i].attr,
            .texaddr  = texname_tex[i].texaddr
        };
    }

    return tlist;
}

void
RFU_FreeTexlist(NJS_TEXLIST* ptlo)
{
    njReleaseTexture(ptlo);
    syFree(ptlo);
}
