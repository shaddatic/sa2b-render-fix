/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/input.h'
* 
*   Contains structures and data related to game input.
* 
*   Contributors: 
*   -   SEGA - Sonic Team,
*   -   Shaddatic
* 
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Includes            */
/************************/
#include <sa2b/shinobi/sg_pad.h>

/************************/
/*  Button Defines      */
/************************/
#define BTN_L       PDD_DGT_TL
#define BTN_R       PDD_DGT_TR
#define BTN_Y       PDD_DGT_TY
#define BTN_RIGHT   PDD_DGT_KR
#define BTN_LEFT    PDD_DGT_KL
#define BTN_DOWN    PDD_DGT_KD
#define BTN_UP      PDD_DGT_KU
#define BTN_START   PDD_DGT_ST
#define BTN_A       PDD_DGT_TA
#define BTN_B       PDD_DGT_TB

/************************/
/*  Structures          */
/************************/
typedef struct
{
    sint32  angle;
    float32 stroke;
}
SONIC_INPUT;

/************************/
/*  Data                */
/************************/
/*  
*   External data is affected by ucInputStatus, Internal data is not
*   'G' is internal
*/
/** Disable/Enable Input **/
DataRef(uint8, ucInputStatus,               0x0174AFFE);
DataAry(uint8, ucInputStatusForEachPlayer,  0x0174AFFF, [2]);

/** Analog Input **/
DataAry(SONIC_INPUT, input_data,    0x01DEFAC0, [8]);
DataAry(SONIC_INPUT, input_dataG,   0x01DEFBA0, [8]);

/** Switch Input **/
DataAry(PDS_PERIPHERAL*,    per,    0x01DEFB60, [8]);
DataAry(PDS_PERIPHERAL,     perG,   0x01DEFC00, [8]);

/** Advertize Switch Input Internal **/
DataAry(uint32, SWDATA,     0x01DEFB10, [4]);
DataAry(uint32, SWDATAE,    0x01DEFAB0, [4]);

/** Advertize Switch Input External **/
DataAry(uint32, swdata,     0x01DEFBE0, [4]);
DataAry(uint32, swdatae,    0x01DEFB50, [4]);

/** Advertize Repeat Timer Internal **/
DataAry(sint32, SW_REP,     0x01934BF0, [4]);
