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
/*  Opaque Types                */
/********************************/
/****** Chunk Object ****************************************************************************/
typedef struct cnkobj               NJS_CNK_OBJECT;

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

/********************************/
/*  Structures                  */
/********************************/
/****** Cart Info *******************************************************************************/
typedef struct
{
    s32             player;         /* player index                                             */
    s32             tex;            /* sprite tex index                                         */
    NJS_CNK_OBJECT* obj;            /* object                                                   */
    s8              spd;            /* speed stat                                               */
    s8              acl;            /* acceleration stat                                        */
    s8              brk;            /* break stat                                               */
    s8              grp;            /* grip stat                                                */
}
CAR_INFO; // unnamed

typedef struct
{
    s32             modelNumber;    /* model number                                             */
    NJS_CNK_OBJECT* carObj;         /* cart model                                               */
    NJS_CNK_OBJECT* carFarObj;      /* cart lod model                                           */
    NJS_TEXLIST*    carTls;         /* cart texlist                                             */
    void*           mdlAddress;     /* model address                         [unused in battle] */
    void*           tlsAddress;     /* texlist address                       [unused in battle] */
    s32             effectFlag;     /* effect flags                                             */
}
CAR_MODEL_INFO;

typedef struct
{
    s32             engineSe;       /* engine se number                                         */
    s32             breakSe;        /* break se number                                          */
    s32             goalAdx;        /* music on goal                                            */
    s32             first5;         /* ?????                                                    */
    s32             sixth5;         /* ?????                                                    */
    NJS_CNK_OBJECT* kageObject;     /* shadow object                                            */
}
CART_EXTRA_PARAM;

/********************************/
/*  Data                        */
/********************************/
/****** DataDll *********************************************************************************/
#define player00                    ( (CAR_INFO(*)[2][6])    GetDataDllProcAddr("player00")     )
#define specialInfo                 ( (CAR_MODEL_INFO(*)[9]) GetDataDllProcAddr("specialInfo")  )
#define exModels                    ( (NJS_CNK_OBJECT(*)[6]) GetDataDllProcAddr("exModels")     )

EXTERN_END

#endif/*H_SA2B_CART_CARTCAR*/
