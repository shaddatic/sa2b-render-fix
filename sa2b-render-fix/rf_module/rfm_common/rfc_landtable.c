/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */
#include <samt/writeop.h>   /* WriteNOP                                             */
#include <samt/funchook.h>  /* FuncHook                                             */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>        /* task                                         */
#include <samt/sonic/njctrl.h>      /* oncontrol3d                                  */
#include <samt/sonic/light.h>       /* setlight                                     */

#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/landtable.h>   /* landtable                                    */
#undef SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_njcnk.h>       /* cnkdraw                                              */
#include <rf_renderstate.h> /* render state                                         */

/****** Self ************************************************************************/
#include <rf_module/rfm_common/rfc_transparancy/rfct_internal.h> /* self            */

/************************/
/*  Game Functions      */
/************************/
/****** Shadow Map ******************************************************************/
#define gjSetShadow         FUNC_PTR(void, __cdecl, (const void*, const f32)  , 0x00495EB0)
#define gjTranslateShadow   FUNC_PTR(void, __cdecl, (const void*, const void*), 0x00496160)
#define gjClearLandShadow   FUNC_PTR(void, __cdecl, (void)                    , 0x00496310)

/************************/
/*  Headless Funcs      */
/************************/
/****** Camera Cull *****************************************************************/
bool    GetCurrCameraCullState( void );

___TODO("Make actual header definitions for these");
void    rjCnkBeginShadowTex(void);
void    rjCnkEndShadowTex(void);

/************************/
/*  Source              */
/************************/
/****** LandTable Draw **************************************************************/
static void
DrawLandtable_RF(void)
{
    OnControl3D( NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW );

    njSetTexture( pObjLandTable->pTexList );

    SetLight(2);

    //if ( pObjLandTable->ssAttribute & 2 ) // some flag? does nothing in battle
    {
        const s32             nb_landentrylist = nbObjLandEntry;
        const OBJ_LANDENTRY** pp_landentrylist = pObjLandEntry;

        for ( s32 i = 0; i < nb_landentrylist; ++i, ++pp_landentrylist )
        {
            const OBJ_LANDENTRY* p_landentry = *pp_landentrylist;

            const s32 landattr = p_landentry->slAttribute;

            const NJS_CNK_OBJECT* p_obj = p_landentry->pObject;

            njPushMatrixEx();

            njTranslateA(NULL, p_obj->pos);

            njRotateZ(NULL, p_obj->ang[2]);
            njRotateY(NULL, p_obj->ang[1]);
            njRotateX(NULL, p_obj->ang[0]);

            if ( landattr & LANDDRAW_NOFOG )
            {
                njFogDisable();
            }

            if ( !(landattr & LANDDRAW_NOSHADOW) )
            {
                gjSetShadow( &p_landentry->xCenter, p_landentry->radius );
                gjTranslateShadow( p_obj->pos, p_obj->ang );
            }

            if ( boolLandGjmdl )
            {
                gjDrawModel( (GJS_MODEL*)p_obj->model );
            }
            else // chunk
            {
                rjCnkBeginShadowTex();

                if ( landattr & LANDDRAW_NOCOMPILE )
                {
                    if ( landattr & LANDDRAW_SIMPLEDRAW )
                    {
                        njCnkSimpleDrawModel(p_obj->model);
                    }
                    else
                    {
                        njCnkEasyDrawModel(p_obj->model);
                    }
                }
                else
                {
                    njCnkDirectDrawModel(p_obj->model);
                }

                rjCnkEndShadowTex();
            }

            if ( !(landattr & LANDDRAW_NOSHADOW) )
            {
                gjClearLandShadow();
            }

            if ( landattr & LANDDRAW_NOFOG )
            {
                njFogEnable();
            }

            njPopMatrixEx();
        }
    }

    OffControl3D( NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_SHADOW );
}

#define ListGroundForDrawing        FUNC_PTR(void, __cdecl, (void), 0x0047CAE0)
#define DrawLandtable               FUNC_PTR(void, __cdecl, (void), 0x0047C2E0)
#define DrawMotLandEntry            FUNC_PTR(void, __cdecl, (void), 0x0047C6E0)

static void
LandDisplayer_RF(task* tp)
{
    if ( GetCurrCameraCullState() )
    {
        return;
    }

    SaveConstantAttr();

    if ( boolLandDisplay == true )
    {
        rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_OPAQUE );

        ListGroundForDrawing();
        DrawLandtable();
        DrawMotLandEntry();

        rjCnkSetControl( ~0, RJD_CNK_CTRL_MASK_DRAW );
    }

    LoadConstantAttr();
}

static void
LandDisplayerSort_RF(task* tp)
{
    if ( GetCurrCameraCullState() )
    {
        return;
    }

    SaveConstantAttr();

    if ( boolLandDisplay == true )
    {
        rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_TRANSLUCENT );

//      ListGroundForDrawing();
        DrawLandtable();
        DrawMotLandEntry();

        rjCnkSetControl( ~0, RJD_CNK_CTRL_MASK_DRAW );
    }

    LoadConstantAttr();
}

/****** Auto-format *****************************************************************/
static bool
LandTableIsGinja(const OBJ_LANDTABLE* pLand)
{
    int count = pLand->ssDispCount;

    if (count < 0)
        count = pLand->ssCount;

    for (int i = 0; i < count; ++i)
    {
        const OBJ_LANDENTRY* const p_entry = &pLand->pLandEntry[i];

        const NJS_CNK_OBJECT* const p_obj = p_entry->pObject;

        /** If entry isn't set to draw, skip **/

        if ( !(p_entry->slAttribute & LANDDRAW_DRAW) )
        {
            continue;
        }

        /** Chunk models are unlikely to not have 'plist' data, while Ginja models
          never uses that pointer in SA2. If 'plist' exists, it's almost
          certainly a Chunk model; meaning a Chunk LandTable **/

        if (p_obj->model && p_obj->model->plist)
        {
            return false;
        }
    }

    return true;
}

static mt_hookinfo LandChangeLandTableHookInfo[1];
static void
LandChangeLandTableHook(OBJ_LANDTABLE* land)
{
    boolLandGjmdl = LandTableIsGinja(land);

    FuncHookCall( LandChangeLandTableHookInfo, LandChangeLandTable(land) );
}

/****** Init ************************************************************************/
void
RFC_LandtableInit(void)
{
    /** Automatically determine landtable format type **/
    FuncHook(LandChangeLandTableHookInfo, LandChangeLandTable_p, LandChangeLandTableHook);

    WriteJump(0x0047C2E0, DrawLandtable_RF);
    WriteJump(0x0047C200, LandDisplayer_RF);
    WriteJump(0x0047C270, LandDisplayerSort_RF);
}
