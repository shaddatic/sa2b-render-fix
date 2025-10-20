/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */

/****** System **********************************************************************************/
#include <samt/shinobi/sg_maloc.h>  /* ninja                                                    */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* setconstantmat                                           */
#include <samt/sonic/set.h>         /* checkview                                                */
#include <samt/sonic/light.h>       /* setlightindex                                            */
#include <samt/sonic/score.h>       /* gametimer                                                */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_njcnk.h>               /* core                                                     */
#include <rf_enemywk.h>             /* enemywk                                                  */
#include <rf_renderstate.h>         /* rfrs                                                     */

/****** RF Utility ******************************************************************************/
#include <rfu_model.h>              /* stripflag                                                */

/****** Self ************************************************************************************/
#include <rf_module/rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings                */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Kumi Pika Object ************************************************************************/
#define model_e_kumi_pika           DATA_ARY(NJS_CNK_MODEL , 0x014B2C64, [1])
#define object_e_kumi_pika          DATA_ARY(NJS_CNK_OBJECT, 0x014B2C7C, [1])

/****** Kumi Pika Texlist ***********************************************************************/
#define KumiPikaTexlists            DATA_ARY(NJS_TEXLIST, 0x014B3098, [9])

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static void*
FalseAlloc(void)
{
    return syCalloc( 8, 1 );
}

static void
CnkScrollTexture(NJS_CNK_MODEL* pModel, void* pUvcinfo, u32 scroll)
{
    static const pint fptr = 0x00795790;

    __asm
    {
        push        [scroll]
        mov esi,    [pUvcinfo]
        push        [pModel]

        call        fptr

        add esp, 8
    }
}

/****** Disp ************************************************************************************/
static void
EnemyKumiDisp_RF(task* tp)
{
    const taskwk*  restrict twp = tp->twp;
    const enemywk* restrict ewp = GET_ENEMYWK(tp);

    if ( CheckViewV( &twp->pos, 40.f ) || twp->mode == 2 )
    {
        return;
    }

    SetLight(8);

    switch ( twp->smode )
    {
        case 4:
        {
            njSetTexture( (NJS_TEXLIST*)0x14AC860 );
            break;
        }
        case 6:
        {
            njSetTexture( (NJS_TEXLIST*)0x14B1088 );
            break;
        }
        case 7:
        {
            njSetTexture( (NJS_TEXLIST*)0x14AEFB8 );
            break;
        }
        default:
        {
            njSetTexture( (NJS_TEXLIST*)0x14AAC64 );
            break;
        }
    }

    njPushMatrixEx();
    {
        njTranslateV(NULL, &twp->pos);

        njPushMatrixEx();
        {
            if ( twp->mode == 3 || twp->mode == 4 )
            {
                // offset material implied
                SetConstantMaterial( ewp->color.a, ewp->color.r, ewp->color.g, ewp->color.b );

                OnControl3D( NJD_CONTROL_3D_CNK_CONSTANT_ATTR );

                OnConstantAttr( ~NJD_FST_MASK, NJD_FST_UA );

                RFRS_SetTransMode(RFRS_TRANSMD_AUTO_ATEST);
            }

            njRotateY(NULL, twp->ang.y + 0x4000);

            if ( twp->smode == 5 )
            {
                njScale(NULL, ewp->scale_param, 1.f, ewp->scale_param);
            }

            if ( twp->flag & 0x4000 )
            {
                njCnkDirectDrawObject(ewp->motion.pObject);
            }
            else if ( ewp->motion.type == 2 )
            {
                njCnkSimpleDrawMotionLink(ewp->motion.pObject, &ewp->motion.MotionLink, ewp->motion.nframe);
            }
            else if ( twp->smode != 7 || GetGameTime() > 2 )
            {
                njCnkSimpleDrawMotion(ewp->motion.pObject, ewp->motion.pMtnUnk[ewp->motion.index].mtnp, ewp->motion.nframe);
            }

            if ( twp->mode == 3 || twp->mode == 4 )
            {
                RFRS_SetTransMode(RFRS_TRANSMD_END);

                OffConstantAttr( ~NJD_FST_MASK, ~NJD_FST_UA );

                OffControl3D( NJD_CONTROL_3D_CNK_CONSTANT_ATTR );

                ResetConstantMaterial();
            }
        }
        njPopMatrixEx();

        if ( twp->mode == 5 )
        {
            njFogDisable();

            njSetTexture( &KumiPikaTexlists[ewp->field_46] );

            CnkScrollTexture( model_e_kumi_pika, (void*)0x0147EBE4, ewp->scroll );

            njCnkEasyDrawObject( object_e_kumi_pika );

            njFogEnable();
        }
    }
    njPopMatrixEx();

    SetLight(DefaultLight);
}

/****** Init ************************************************************************************/
void
RFCD_EnemyKumiInit(void)
{
    WriteCall(0x00500205, FalseAlloc); // syCalloc( 0, 1 ) calls
    WriteCall(0x0050035D, FalseAlloc); // ^^

    WriteRetn(0x005011B0);
    WriteJump(0x00501440, EnemyKumiDisp_RF);
}
