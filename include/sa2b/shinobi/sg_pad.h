/*
*   Sonic Adventure Mod Tools (SA2B) - '/shinobi/sg_pad.h'
*
*   Definition:
*     System peripheral constants & structures.
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/

#ifndef H_SG_PAD
#define H_SG_PAD

/************************/
/*  Includes            */
/************************/
/** System **/
#include <sa2b/shinobi/sg_xpt.h>

/************************/
/*  Constants           */
/************************/
/****** Port Numbers ****************************************************************/
#define PDD_PORT_A0    0                   /* Port A0                               */
#define PDD_PORT_A1    1                   /* Port A1                               */
#define PDD_PORT_A2    2                   /* Port A2                               */
#define PDD_PORT_A3    3                   /* Port A3                               */
#define PDD_PORT_A4    4                   /* Port A4                               */
#define PDD_PORT_A5    5                   /* Port A5                               */
#define PDD_PORT_B0    6                   /* Port B0                               */
#define PDD_PORT_B1    7                   /* Port B1                               */
#define PDD_PORT_B2    8                   /* Port B2                               */
#define PDD_PORT_B3    9                   /* Port B3                               */
#define PDD_PORT_B4   10                   /* Port B4                               */
#define PDD_PORT_B5   11                   /* Port B5                               */
#define PDD_PORT_C0   12                   /* Port C0                               */
#define PDD_PORT_C1   13                   /* Port C1                               */
#define PDD_PORT_C2   14                   /* Port C2                               */
#define PDD_PORT_C3   15                   /* Port C3                               */
#define PDD_PORT_C4   16                   /* Port C4                               */
#define PDD_PORT_C5   17                   /* Port C5                               */
#define PDD_PORT_D0   18                   /* Port D0                               */
#define PDD_PORT_D1   19                   /* Port D1                               */
#define PDD_PORT_D2   20                   /* Port D2                               */
#define PDD_PORT_D3   21                   /* Port D3                               */
#define PDD_PORT_D4   22                   /* Port D4                               */
#define PDD_PORT_D5   23                   /* Port D5                               */

/****** Button/Trigger Support Flags ************************************************/
#define PDD_DEV_SUPPORT_AY2   (1 << 21)    /* Has analog axis Y2                    */
#define PDD_DEV_SUPPORT_AX2   (1 << 20)    /* Has analog axis X2                    */
#define PDD_DEV_SUPPORT_AY1   (1 << 19)    /* Has analog axis Y1                    */
#define PDD_DEV_SUPPORT_AX1   (1 << 18)    /* Has analog axis X1                    */
#define PDD_DEV_SUPPORT_AL    (1 << 17)    /* Has analog axis L                     */
#define PDD_DEV_SUPPORT_AR    (1 << 16)    /* Has analog axis R                     */
#define PDD_DEV_SUPPORT_KRB   (1 << 15)    /* Has D-pad right B                     */
#define PDD_DEV_SUPPORT_KLB   (1 << 14)    /* Has D-pad left B                      */
#define PDD_DEV_SUPPORT_KDB   (1 << 13)    /* Has D-pad down B                      */
#define PDD_DEV_SUPPORT_KUB   (1 << 12)    /* Has D-pad up B                        */
#define PDD_DEV_SUPPORT_TD    (1 << 11)    /* Has D button                          */
#define PDD_DEV_SUPPORT_TX    (1 << 10)    /* Has X button                          */
#define PDD_DEV_SUPPORT_TY    (1 <<  9)    /* Has Y button                          */
#define PDD_DEV_SUPPORT_TZ    (1 <<  8)    /* Has Z button                          */
#define PDD_DEV_SUPPORT_KR    (1 <<  7)    /* Has D-pad right A                     */
#define PDD_DEV_SUPPORT_KL    (1 <<  6)    /* Has D-pad left A                      */
#define PDD_DEV_SUPPORT_KD    (1 <<  5)    /* Has D-pad down A                      */
#define PDD_DEV_SUPPORT_KU    (1 <<  4)    /* Has D-pad up A                        */
#define PDD_DEV_SUPPORT_ST    (1 <<  3)    /* Has Start button                      */
#define PDD_DEV_SUPPORT_TA    (1 <<  2)    /* Has A button                          */
#define PDD_DEV_SUPPORT_TB    (1 <<  1)    /* Has B button                          */
#define PDD_DEV_SUPPORT_TC    (1 <<  0)    /* Has C button                          */

/****** Button Flags ****************************************************************/
#define PDD_DGT_TL    (1 << 17)             /* L button                  (emulated) */
#define PDD_DGT_TR    (1 << 16)             /* R button                  (emulated) */
#define PDD_DGT_KRB   (1 << 15)             /* D-pad right B                        */
#define PDD_DGT_KLB   (1 << 14)             /* D-pad left B                         */
#define PDD_DGT_KDB   (1 << 13)             /* D-pad down B                         */
#define PDD_DGT_KUB   (1 << 12)             /* D-pad up B                           */
#define PDD_DGT_TD    (1 << 11)             /* D button                             */
#define PDD_DGT_TX    (1 << 10)             /* X button                             */
#define PDD_DGT_TY    (1 <<  9)             /* Y button                             */
#define PDD_DGT_TZ    (1 <<  8)             /* Z button                             */
#define PDD_DGT_KR    (1 <<  7)             /* D-pad right A                        */
#define PDD_DGT_KL    (1 <<  6)             /* D-pad left A                         */
#define PDD_DGT_KD    (1 <<  5)             /* D-pad down A                         */
#define PDD_DGT_KU    (1 <<  4)             /* D-pad up A                           */
#define PDD_DGT_ST    (1 <<  3)             /* Start button                         */
#define PDD_DGT_TA    (1 <<  2)             /* A button                             */
#define PDD_DGT_TB    (1 <<  1)             /* B button                             */
#define PDD_DGT_TC    (1 <<  0)             /* C button                             */

/************************/
/*  Peripheral Info     */
/************************/
/****** Peripheral type *************************************************************/
#define PDD_DEVTYPE_CONTROLLER  (1 << 0)    /* Controller                           */
#define PDD_DEVTYPE_STORAGE     (1 << 1)    /* Storage                              */
#define PDD_DEVTYPE_LCD         (1 << 2)    /* LCD                                  */
#define PDD_DEVTYPE_TIMER       (1 << 3)    /* Timer                                */
#define PDD_DEVTYPE_SOUNDINPUT  (1 << 4)    /* Sound input                          */
#define PDD_DEVTYPE_KEYBOARD    (1 << 6)    /* Keyboard                             */
#define PDD_DEVTYPE_LIGHTGUN    (1 << 7)    /* Light gun                            */
#define PDD_DEVTYPE_VIBRATION   (1 << 8)    /* Vibration device                     */

/****** Area Code *******************************************************************/
#define PDD_DEVAREA_USA         (1 << 0)    /* North America region                 */
#define PDD_DEVAREA_JAPAN       (1 << 1)    /* Japan region                         */
#define PDD_DEVAREA_ASIA        (1 << 2)    /* Asia region                          */
#define PDD_DEVAREA_EUROPE      (1 << 3)    /* Europe region                        */
#define PDD_DEVAREA_RESERVED1   (1 << 4)    /* Reserved region 1                    */
#define PDD_DEVAREA_RESERVED2   (1 << 5)    /* Reserved region 2                    */
#define PDD_DEVAREA_RESERVED3   (1 << 6)    /* Reserved region 3                    */
#define PDD_DEVAREA_RESERVED4   (1 << 7)    /* Reserved region 4                    */

/************************/
/*  Structures          */
/************************/
/****** Peripheral information ******************************************************/
typedef struct
{
    Uint32 type;                /* Peripheral type                                  */

    Uint32 reserved[3];         /* Reserved                                         */

    Uint8 is_root;              /* Root device flag                                 */

    Uint8 area_code;            /* Area code                                        */

    Uint8 connector_dir[2];     /* Connector orientation                            */

    char product_name[32];      /* Product name                                     */
    char license[64];           /* License string                                   */

    Uint16 stdby_pow;           /* Standby power                                    */
    Uint16 max_pow;             /* Max power                                        */
}
PDS_PERIPHERALINFO;

/****** Peripheral ******************************************************************/
typedef struct
{
    Uint32 id;                          /* Device ID                 (Do not refer) */

    Uint32 support;                     /* Button support flags                     */

    Uint32 on;                          /* Buttons pressed currently                */
    Uint32 off;                         /* Buttons released currently               */

    Uint32 press;                       /* Buttons pressed this moment              */
    Uint32 release;                     /* Buttons released this moment             */

    Uint16 r;                           /* Axis R                   (   0 <-> +255) */
    Uint16 l;                           /* Axis L                   (   0 <-> +255) */

    Sint16 x1;                          /* Axis X1                  (-128 <-> +127) */
    Sint16 y1;                          /* Axis Y1                  (-128 <-> +127) */
    Sint16 x2;                          /* Axis X2                  (-128 <-> +127) */
    Sint16 y2;                          /* Axis Y2                  (-128 <-> +127) */

    char* name;                         /* Device name                              */

    void* extend;                       /* Extended data address                    */

    Uint32 old;                         /* Reserved                                 */

    PDS_PERIPHERALINFO* info;           /* Pointer to peripheral info               */
}
PDS_PERIPHERAL;

/************************/
/*  Data                */
/************************/
/****** Peripheral ******************************************************************/
#define PeripheralData          DATA_ARY(PDS_PERIPHERAL    , 0x01A52918, [4])
#define PeripheralInfo          DATA_ARY(PDS_PERIPHERALINFO, 0x01A52A68, [4])

#endif/*H_SG_PAD*/
