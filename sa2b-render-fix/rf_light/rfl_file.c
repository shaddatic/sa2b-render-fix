/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/memory.h>        /* memcopy                                          */
#include <samt/file.h>          /* fileload                                         */
#include <samt/string.h>        /* strformat                                        */
#include <samt/modinfo.h>       /* modpath                                          */
#include <samt/modloader.h>     /* mod loader                                       */

/****** Utility *********************************************************************/
#include <samt/util/endian.h>   /* endian                                           */

/****** GX **************************************************************************/
#include <samt/gx/gxlight.h>    /* gxlight                                          */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/light.h>   /* light                                            */
#undef SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_gx.h>              /* rf gx                                            */

/****** Self ************************************************************************/
#include <rf_light/rfl_internal.h> /* parent & siblings                             */

/************************/
/*  Game Defs           */
/************************/
/****** Core Toolkit ****************************************************************/
#define GlobalBuffer            DATA_ARY(byte, 0x01DEFE20, [0x100000])

/************************/
/*  Macros              */
/************************/
/****** Character Count *************************************************************/
#define CHARIN(s)               (sizeof(s) - 1)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
GetLightFilePaths(const c8* puPathBase, const c8** ppuOutPathDC, const c8** ppuOutPathGC)
{
    const size_t sz_path = mtStrSize(puPathBase, STR_NOMAX);

    // get gc path
    c8* const pu_path_gc = (void*) &GlobalBuffer[0x200];

    mtStrCopy(pu_path_gc, puPathBase, sz_path - CHARIN(".bin"));

    mtStrAppend(pu_path_gc, STR_AUTOLEN, "_gc.bin", STR_NOMAX);

    // get replaced paths
    const c8* pu_repl_path_dc = ML_GetReplaceablePath(puPathBase);
    const c8* pu_repl_path_gc = ML_GetReplaceablePath(pu_path_gc);

    const c8* pu_out_path_dc = nullptr;
    const c8* pu_out_path_gc = nullptr; 

    const s32 nb_mod = MI_GetTotalNumber();

    for (s32 i = nb_mod - 1; i >= 0; --i)
    {
        const mod_info* p_modinfo = MI_GetInfoByPosition(i);

        if ( mtPathSearch(pu_repl_path_gc, p_modinfo->cPath, STR_NOMAX) == 0 )
        {
            pu_out_path_gc = pu_repl_path_gc;
            pu_out_path_dc = pu_repl_path_dc;
            break;
        }

        if ( mtPathSearch(pu_repl_path_dc, p_modinfo->cPath, STR_NOMAX) == 0 )
        {
            pu_out_path_dc = pu_repl_path_dc;
            break;
        }
    }

    // the whole point of this function is that the DC files get priority. If a DC file is found before a GC one, then it will act as if no GC files exist.
    // if a GC file is found first, it will continue looking for a DC file to also load

    if ( !pu_out_path_dc )
    {
        pu_out_path_dc = puPathBase;

        if ( !pu_out_path_gc )
        {
            pu_out_path_gc = pu_path_gc;
        }
    }

    *ppuOutPathDC = pu_out_path_dc;
    *ppuOutPathGC = pu_out_path_gc;
}

#define LIGHT_COUNT         (12)

#define SIZEOF_LIGHTBIN             (sizeof(LIGHT)    * LIGHT_COUNT)
#define SIZEOF_LIGHTBIN_GC          (sizeof(LIGHT_GC) * LIGHT_COUNT)

static void
ByteswapLights(LIGHT* pLight)
{
    for (int i = 0; i < LIGHT_COUNT; ++i)
    {
       if ( pLight[i].r < 0.f || pLight[i].r > 1.f ||
            pLight[i].g < 0.f || pLight[i].g > 1.f ||
            pLight[i].b < 0.f || pLight[i].b > 1.f )
       {
           for (int j = 0; j < LIGHT_COUNT; ++j)
           {
               EndianSwap32(&pLight[j].vec.x);
               EndianSwap32(&pLight[j].vec.y);
               EndianSwap32(&pLight[j].vec.z);

               EndianSwap32(&pLight[j].dif);
               EndianSwap32(&pLight[j].amb);

               EndianSwap32(&pLight[j].r);
               EndianSwap32(&pLight[j].g);
               EndianSwap32(&pLight[j].b);
           }
           return;
       }
    }
}

static void
ByteswapLightsGC(LIGHT_GC* pLight)
{
    for (int i = 0; i < LIGHT_COUNT; ++i)
    {
        if ( pLight[i].r < 0.f || pLight[i].r > 1.f ||
             pLight[i].g < 0.f || pLight[i].g > 1.f ||
             pLight[i].b < 0.f || pLight[i].b > 1.f )
        {
            for (int j = 0; j < LIGHT_COUNT; ++j)
            {
                EndianSwap32(&pLight[j].vec.x);
                EndianSwap32(&pLight[j].vec.y);
                EndianSwap32(&pLight[j].vec.z);

                EndianSwap32(&pLight[j].r);
                EndianSwap32(&pLight[j].g);
                EndianSwap32(&pLight[j].b);

                EndianSwap32(&pLight[j].amb_r);
                EndianSwap32(&pLight[j].amb_g);
                EndianSwap32(&pLight[j].amb_b);

                EndianSwap32(&pLight[j].flag);
            }
            return;
        }
    }
}

static void __fastcall
LoadLightFile_RF(const char* pcFileName)
{
    c8* pu_buf = GlobalBuffer;

    mtStrFormat(pu_buf, 0x200, "./resource/gd_PC/%s", pcFileName);

    const c8* pu_light_dc;
    const c8* pu_light_gc;

    GetLightFilePaths(pu_buf, &pu_light_dc, &pu_light_gc);

    /** The idea here is:

      - If NEITHER file exists, the light data should be left as-is.
      - If the DC light file exists and the GC *doesn't*, the GC light data should be nulled out.
      - If the DC file doesn't but GC does, the DC data should be left alone.
      - If BOTH exist, they should both be loaded normally.

        Hope that makes sense lol **/

    bool has_dc_file = false;
    bool has_gc_file = false;

//  if ( pu_light_dc ) // will always be a valid pointer
    {
        OutputFormat("RF INFO: Reading light file: %s", pu_light_dc);

        LIGHT* p_lights = (void*) &GlobalBuffer[0x400];

        if ( mtFileReadEx(pu_light_dc, p_lights, SIZEOF_LIGHTBIN) )
        {
            ByteswapLights(p_lights);

            mtMemCopy(Lights, p_lights, SIZEOF_LIGHTBIN);

            has_dc_file = true;
        }
    }

    if ( pu_light_gc )
    {
        OutputFormat("RF INFO: Reading light file: %s", pu_light_gc);

        LIGHT_GC* p_lights = (void*) &GlobalBuffer[0x400];

        if ( mtFileReadEx(pu_light_gc, p_lights, SIZEOF_LIGHTBIN_GC) )
        {
            ByteswapLightsGC(p_lights);

            mtMemCopy(LightsGC, p_lights, SIZEOF_LIGHTBIN_GC);

            has_gc_file = true;
        }
    }

    // if DC exists but GC doesn't, then null GC light data

    if ( has_dc_file && !has_gc_file )
    {
        mtMemSet(LightsGC, 0x00, SIZEOF_LIGHTBIN_GC);
    }
}

/****** Init ************************************************************************/
void
RFL_FileInit(void)
{
    WriteJump(LoadLightFile_p, LoadLightFile_RF);
}
