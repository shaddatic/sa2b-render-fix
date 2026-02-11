/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/ewalker.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*     Egg Walker player, and base header for walkers.
*/
#ifndef H_SA2B_FIGURE_EGGWALKER
#define H_SA2B_FIGURE_EGGWALKER

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/player.h>      /* core player                                              */
#include <samt/sonic/reform.h>      /* reform object                                            */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Player Work *****************************************************************************/
#define GET_WALKERWK(_tp)       ((walkerwk*)tp->awp)

typedef struct walkerwk
{
    playerwk        pw;             /* player work                                              */

    char field_35C;
    char field_35D;
    char field_35E;
    char field_35F;
    char field_360;
    char field_361[3];
    __int16 field_364;
    __int16 field_366;
    __int16 field_368;
    __int16 field_36A;
    __int16 field_36C;
    __int16 field_36E;
    char field_370[4];
    float field_374;
    char field_378[8];
    int field_380;
    char field_384[12];
    float field_390;
    float field_394;
    float field_398;
    int field_39C;
    char field_3A0[132];
    int alsosomerotation;
    int field_428;
    int field_42C;
    int CannonRecoil;
    int alsomayberotation;
    float field_438;
    float field_43C;
    float field_440;
    NJS_TEXLIST*    tlist_walktex;  /* texlist, walktex                                         */
    NJS_TEXLIST*    tlist;          /* texlist                                                  */
    playerobj*      freeobj;        /* free object list                                         */
    playermot*      freemtn;        /* free motion list                                         */
}
walkerwk;

/********************************/
/*  Variables                   */
/********************************/
/****** Player Work *****************************************************************************/
#define EggWalkerWorkPointer            DATA_REF(walkerwk* , 0x01A51F0C)

/****** Matrix **********************************************************************************/
#define mtx_EWalkerBase                 DATA_REF(NJS_MATRIX, 0x01A51F70)
#define mtx_EWalkerLaserBlaster         DATA_REF(NJS_MATRIX, 0x01A51EAC)
#define mtx_EWalkerLargeCannon          DATA_REF(NJS_MATRIX, 0x01A51D2C)
#define mtx_EWalkerJetEngineL           DATA_REF(NJS_MATRIX, 0x01A52000)
#define mtx_EWalkerJetEngineR           DATA_REF(NJS_MATRIX, 0x01A52060)
#define mtx_EWalkerProtectiveArmor      DATA_REF(NJS_MATRIX, 0x01A520C0)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     The Eggwalker's main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    EggWalkerMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define EggWalkerMotionCallBack_p           FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x00744020)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_EGGWALKER*/
