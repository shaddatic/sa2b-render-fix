/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/cart/cartcar.h'
*
*   Description:
*     Cart info for the cart racing minigame/story stages.
*/
#ifndef H_SA2B_CART_CARTCAR
#define H_SA2B_CART_CARTCAR

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/datadll.h>     /* data_dll                                                 */

EXTERN_START

/********************************/
/*  Enums                       */
/********************************/
/****** Cart Index ******************************************************************************/
enum
{
    CART_CAR_TAILS_SPECIAL,         /* tails, route stages                                      */
    CART_CAR_ROUGE_SPECIAL,         /* rouge, route stages                                      */

    CART_CAR_SONIC,                 /* sonic                                                    */
    CART_CAR_KNUCKLES,              /* knuckles                                                 */
    CART_CAR_TAILS,                 /* tails                                                    */
    CART_CAR_EGGMAN,                /* eggman                                                   */
    CART_CAR_SHADOW,                /* shadow                                                   */
    CART_CAR_ROUGE,                 /* rouge                                                    */
    CART_CAR_DOWNLOAD,              /* downloadable cart                                        */

    CART_CAR_MAX,                   /* enum count                                               */
};

/****** Cart SE Index ***************************************************************************/
enum
{
    SE_CART_SONIC_DASH,             /* dash speech,  sonic                                      */
    SE_CART_SONIC_BOOST,            /* boost speech, sonic                                      */
    SE_CART_SHADOW_DASH,            /* dash speech,  shadow                                     */
    SE_CART_SHADOW_BOOST,           /* boost speech, shadow                                     */
    SE_CART_KNUCKLES_DASH,          /* dash speech,  knuckles                                   */
    SE_CART_KNUCKLES_BOOST,         /* boost speech, knuckles                                   */
    SE_CART_ROUGE_DASH,             /* dash speech,  rouge                                      */
    SE_CART_ROUGE_BOOST,            /* boost speech, rouge                                      */
    SE_CART_TAILS_DASH,             /* dash speech,  tails                                      */
    SE_CART_TAILS_BOOST,            /* boost speech, tails                                      */
    SE_CART_EGGMAN_DASH,            /* dash speech,  eggman                                     */
    SE_CART_EGGMAN_BOOST,           /* boost speech, eggman                                     */
    SE_CART_SPRCIAL_ENGINE,         /* special engine                                           */
    SE_CART_CART_ENGINE,            /* engine                                                   */
    SE_CART_IDLING,                 /* idle                                                     */
    SE_CART_WHEELSPINE,             /* wheel spin                                               */
    SE_CART_BREAK,                  /* break                                                    */
    SE_CART_COLLISION,              /* collision, 1                                             */
    SE_CART_COLLISION2,             /* collision, 2                                             */
    SE_CART_THROUGH,                /* through (?)                                              */
    SE_CART_BOM1,                   /* BOM, 1 (?)                                               */
    SE_CART_BOM2,                   /* BOM, 2 (?)                                               */
    SE_CART_PATCAR,                 /* pat car (?)                                              */
    SE_CART_TORNADE,                /* tornado (?)                                              */
    SE_CART_START1,                 /* start beep, 1                                            */
    SE_CART_START2,                 /* start beep, 2                                            */
    SE_CART_PYRON,                  /* pylon (?)                                                */
    SE_CART_BOOST,                  /* boost sound                                              */
    SE_CART_WIND,                   /* wind                                                     */
    SE_CART_TUNNEL,                 /* tunnel woosh                                             */

    SE_CART_EX_NORMAL_EGGMAN,       /* ????                                                     */
    SE_CART_EX_HIDE_SHADOW,         /* ????                                                     */
    SE_CART_EX_NORMAL_KNUCKLES,     /* ????                                                     */
    SE_CART_EX_NORMAL_ROUGE,        /* ????                                                     */
    SE_CART_EX_HIDE_TAILS,          /* ????                                                     */
    SE_CART_EX_HIDE_KNUCKLES,       /* ????                                                     */
    SE_CART_EX_NORMAL_EGGMAN2,      /* ????                                                     */
    SE_CART_EX_HIDE_CHAO,           /* ????                                                     */
    SE_CART_EX_ROBO_ACC,            /* robo accelerate                                          */
    SE_CART_EX_ROBO_BREAK,          /* robo break                                               */
};

/********************************/
/*  Structures                  */
/********************************/
/****** Cart Info *******************************************************************************/
typedef struct
{
    i32             player;         /* player index                                             */
    i32             tex;            /* sprite tex index                                         */
    NJS_CNK_OBJECT* obj;            /* object                                                   */
    i8              spd;            /* speed stat                                               */
    i8              acl;            /* acceleration stat                                        */
    i8              brk;            /* break stat                                               */
    i8              grp;            /* grip stat                                                */
}
CAR_INFO; // unnamed

typedef struct
{
    i32             modelNumber;    /* model number                                             */
    NJS_CNK_OBJECT* carObj;         /* cart model                                               */
    NJS_CNK_OBJECT* carFarObj;      /* cart lod model                                           */
    NJS_TEXLIST*    carTls;         /* cart texlist                                             */
    void*           mdlAddress;     /* model address                         [unused in battle] */
    void*           tlsAddress;     /* texlist address                       [unused in battle] */
    i32             effectFlag;     /* effect flags                                             */
}
CAR_MODEL_INFO;

typedef struct
{
    i32             engineSe;       /* engine se index                                          */
    i32             breakSe;        /* break se index                                           */
    i32             goalAdx;        /* goal serif number                                        */
    i32             first5;         /* first place serif number                                 */
    i32             sixth5;         /* last place serif number                                  */
    NJS_CNK_OBJECT* kageObject;     /* shadow object                                            */
}
CART_EXTRA_PARAM;

/********************************/
/*  DataDLL Defs                */
/********************************/
/****** DataDll *********************************************************************************/
#define datadll_player00            ( (CAR_INFO(*)[2][6])    GetDataDllProcAddr("player00")     )
#define datadll_specialInfo         ( (CAR_MODEL_INFO(*)[9]) GetDataDllProcAddr("specialInfo")  )
#define datadll_exModels            ( (NJS_CNK_OBJECT(*)[6]) GetDataDllProcAddr("exModels")     )

EXTERN_END

#endif/*H_SA2B_CART_CARTCAR*/
