/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/sonic.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*     Sonic the Hedgehog player, and base header for speed characters.
*/
#ifndef H_SA2B_FIGURE_SONIC
#define H_SA2B_FIGURE_SONIC

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
/*  Enums                       */
/********************************/
/****** Player Motion ***************************************************************************/
enum
{
    SONICMOT_LSDS          = 87,
    SONICMOT_IRITATED1,
    SONICMOT_IRITATED2,
    SONICMOT_IRITATED3,
    SONICMOT_SOMERSAULT,
    SONICMOT_SOMERSAULT2,
    SONICMOT_SOMERSAULT3,
    SONICMOT_SOMERSAULTSTOP,
    SONICMOT_SOMERSAULTCANCEL,
    SONICMOT_DASHSOMER,
    SONICMOT_DASHSOMER2,
    SONICMOT_DASHSOMER3,
    SONICMOT_DASHSOMER3F,
    SONICMOT_JUMPDASH,
    SONICMOT_AIR0,
    SONICMOT_AIR1,
    SONICMOT_AIR2,
    SONICMOT_GLIDEL,
    SONICMOT_GLIDER,
    SONICMOT_GLIDE2L,
    SONICMOT_GLIDE2R,
    SONICMOT_GLIDEBL,
    SONICMOT_GLIDEBR,
    SONICMOT_GLIDEB2L,
    SONICMOT_GLIDEB2R,
    SONICMOT_GLIDEOTTOTOL,
    SONICMOT_GLIDEOTTOTOR,
    SONICMOT_SOAPJUMP0,
    SONICMOT_SOAPJUMP1,
    SONICMOT_SOAPJUMP2,
    SONICMOT_TRICKJUMP,
    SONICMOT_WAZAPOSE,
    SONICMOT_2PSTARTPOSE,
    SONICMOT_2PSTARTWAIT,
    SONICMOT_BOARDL,
    SONICMOT_BOARDR,
    SONICMOT_BOARD2L,
    SONICMOT_BOARD2R,
    SONICMOT_BOARDBRAKEL,
    SONICMOT_BOARDBRAKER,
    SONICMOT_BOARDJUMP,
    SONICMOT_BOARDJUMP_FALL,
    SONICMOT_BOARDFALL,
    SONICMOT_BOARDLAND,
    SONICMOT_BOARDDAMAGER,
    SONICMOT_BOARDDAMAGEL,
    SHADOWMOT_BOARDRANKB,
    SHADOWMOT_BOARDRANKA,
    SHADOWMOT_BOARDSPECIAL,
    METALSONICMOT_BOARDRANKB,
    METALSONICMOT_BOARDRANKA,
    METALSONICMOT_BOARDSPECIAL,
    AMYMOT_BOARDRANKB,
    AMYMOT_BOARDRANKA,
    AMYMOT_BOARDSPECIAL,
    SONICMOT_BOARDSPECIAL,
    SONICMOT_BOARDRANKA,
    SONICMOT_BOARDRANKB,
    SONICMOT_BOARD_BOARDL,
    SONICMOT_BOARD_BOARDR,
    SONICMOT_BOARD_BOARD2L,
    SONICMOT_BOARD_BOARD2R,
    SONICMOT_BOARD_BOARDBRAKEL,
    SONICMOT_BOARD_BOARDBRAKER,
    SONICMOT_BOARD_BOARDJUMP,
    SONICMOT_BOARD_BOARDJUMP_FALL,
    SONICMOT_BOARD_BOARDFALL,
    SONICMOT_BOARD_BOARDLAND,
    SONICMOT_BOARD_BOARDDAMAGER,
    SONICMOT_BOARD_BOARDDAMAGEL,
    SHADOWMOT_BOARD_BOARDRANKB,
    SHADOWMOT_BOARD_BOARDRANKA,
    SHADOWMOT_BOARD_BOARDSPECIAL,
    METALSONICMOT_BOARD_BOARDRANKB,
    METALSONICMOT_BOARD_BOARDRANKA,
    METALSONICMOT_BOARD_BOARDSPECIAL,
    AMYMOT_BOARD_BOARDRANKB,
    AMYMOT_BOARD_BOARDRANKA,
    AMYMOT_BOARD_BOARDSPECIAL,
    SONICMOT_BOARD_BOARDSPECIAL,
    SONICMOT_BOARD_BOARDRANKA,
    SONICMOT_BOARD_BOARDRANKB,
    TERIOSMOT_STAND,
    TERIOSMOT_KAMAE,
    TERIOSMOT_JOG,
    TERIOSMOT_RUN,
    TERIOSMOT_RUSH,
    TERIOSMOT_DASH,
    TERIOSMOT_TURN,
    TERIOSMOT_IRITATED1,
    TERIOSMOT_IRITATED2,
    TERIOSMOT_IRITATED3,
    TERIOSMOT_LAND2,
    TERIOSMOT_WINPOSE,
    TERIOSMOT_LOSEPOSE,
    TERIOSMOT_WAZAPOSE,
    TERIOSMOT_2PSTARTPOSE,
    TERIOSMOT_2PSTARTWAIT,
    SONICMOT_TUTA_CATCH,
    SONICMOT_TUTA_HOLD,
    SONICMOT_TUTA_FALL,
    SONICMOT_TUTA_FALL_RISE,
    SONICMOT_TUTA_STARTFALL,
    SONICMOT_MISSILE_HANG,
    SONICMOT_MISSILE_FALL,
    SONICMOT_TETSUBO_HANGF,
    SONICMOT_TETSUBO_HANGB,
    SONICMOT_TETSUBO_JUMPBL,
    SONICMOT_TETSUBO_JUMPFL,
    SONICMOT_TETSUBO_JUMPBS,
    SONICMOT_TETSUBO_JUMPFS,
    SONICMOT_TETSUBO_FINISH,
    SONICMOT_RYUSA_FALL,
    SONICMOT_HANDRAIL_GLIDE,
    SONICMOT_GRAVITY_SWITCH,
    SONICMOT_SUIRYU_NAGASARE,
    AMYMOT_STAND,
    AMYMOT_WALK,
    AMYMOT_JOG,
    AMYMOT_RUN,
    AMYMOT_RUSH,
    AMYMOT_DASH,
    AMYMOT_AIR0,
    AMYMOT_AIR1,
    AMYMOT_AIR2,
    AMYMOT_TUTA_CATCH,
    AMYMOT_TUTA_HOLD,
    AMYMOT_WINPOSE,
    AMYMOT_LOSEPOSE,
    AMYMOT_IRITATED1,
    AMYMOT_IRITATED2,
    AMYMOT_IRITATED3,
    AMYMOT_WAZAPOSE,
    AMYMOT_2PSTARTPOSE,
    AMYMOT_2PSTARTWAIT,
    METALSONICMOT_JOG,
    METALSONICMOT_RUN,
    METALSONICMOT_RUSH,
    METALSONICMOT_DASH,
    METALSONICMOT_2PSTARTPOSE,
    METALSONICMOT_2PSTARTWAIT,
    AMYMOT_HMR_JUMP0,
    AMYMOT_HMR_JUMP0_HMR,
    AMYMOT_HMR_JUMP1,
    AMYMOT_HMR_JUMP1_HMR,
    AMYMOT_HMR_JUMP2,
    AMYMOT_HMR_JUMP2_HMR,
    AMYMOT_HMR_JUMP3,
    AMYMOT_SOAPJUMP2,
    METALSONICMOT_SOAPJUMP1,
    METALSONICMOT_WINPOSE,
    AMYMOT_LAND2,
    METALSONICMOT_LOSEPOSE,
    AMYMOT_SOMERSAULT,
    AMYMOT_DASHSOMER,
    AMYMOT_DASHSOMER3,
    METALSONICMOT_GUARD0,
    METALSONICMOT_GUARD1,
    AMYMOT_DASHSOMER3F,
    SHADOWMOT_TRICKJUMP,
    METALSONICMOT_TRICKJUMP,
    AMYMOT_TRICKJUMP,

    SONICMOT_END,
};

/********************************/
/*  Structures                  */
/********************************/
/****** Player Work *****************************************************************************/
#define GET_SONICWK(_tp)    ((sonicwk*)(_tp)->awp)

typedef struct sonicwk
{
    playerwk        pw;             /* player work                                          */

    i8              field_35C[4];
    i16             flag;
    i8              field_35C_[4];
    i16             unks_1;
    i16             SpindashCounter;
    i32             field_36A;
    i32             field_36E;
    i32             field_372;
    i16             field_376;
    NJS_VECTOR      setpos;
    i32             field_386;
    i32             field_38A;
    reformwk*       rw_head;
    NJS_TEXLIST*    tlist;          /* texlist                                                  */
    playerobj*      freeobj;        /* free object list                                         */
    playermot*      freemtn;        /* free motion list                                         */
}
sonicwk; // 928

/********************************/
/*  Variables                   */
/********************************/
/****** Player Work *****************************************************************************/
#define SonicWorkPointer            DATA_REF(sonicwk*  , 0x01A51A9C)

/****** Matrix **********************************************************************************/
#define mtx_SonicBase               DATA_REF(NJS_MATRIX, 0x01A51A00)
#define mtx_SonicHandL              DATA_REF(NJS_MATRIX, 0x01A51A3C)
#define mtx_SonicHandR              DATA_REF(NJS_MATRIX, 0x01A51AA0)
#define mtx_SonicFootL              DATA_REF(NJS_MATRIX, 0x01A51A6C)
#define mtx_SonicFootR              DATA_REF(NJS_MATRIX, 0x01A519D0)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     Sonic's main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    SonicMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define SonicMotionCallBack_p               FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071EAA0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_SONIC*/
