/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/input.h'
* 
*   Description:
*       Contains structures and data related to game input.
* 
*   Contributors: 
*   -   SEGA - Sonic Team,
*   -   Shaddatic
* 
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_INPUT_H_
#define _SA2B_INPUT_H_

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
    int32_t  angle;
    float32_t stroke;
}
SONIC_INPUT;

/************************/
/*  Data                */
/************************/
/*  
*   'G' & external data is affected by 'ucInputStatus'
*/
/** Disable/Enable Input **/
#define ucInputStatus               DataRef(uint8_t        , 0x0174AFFE)
#define ucInputStatusForEachPlayer  DataAry(uint8_t        , 0x0174AFFF, [2])

/** Controller Input **/
#define per                         DataAry(PDS_PERIPHERAL*, 0x01DEFB60, [8])
#define perG                        DataAry(PDS_PERIPHERAL , 0x01DEFC00, [8])

/** Analog Input **/
#define input_data                  DataAry(SONIC_INPUT    , 0x01DEFAC0, [8])
#define input_dataG                 DataAry(SONIC_INPUT    , 0x01DEFBA0, [8])

/** Jump Input **/
#define jump_held                   DataAry(bool           , 0x01DEFAA4, [2])
#define jump_press                  DataAry(bool           , 0x01DEFB80, [2])
#define jump_off                    DataAry(bool           , 0x01DEFAA6, [2])
#define jump_release                DataAry(bool           , 0x01DEFB40, [2])

/** Action Input **/
#define action_held                 DataAry(bool           , 0x01DEFBF0, [2])
#define action_press                DataAry(bool           , 0x01DEFB00, [2])
#define action_off                  DataAry(bool           , 0x01DEFB20, [2])
#define action_release              DataAry(bool           , 0x01DEFB42, [2])

/** Advertize Switch Input Internal **/
#define SWDATA                      DataAry(uint32_t       , 0x01DEFB10, [4])
#define SWDATAE                     DataAry(uint32_t       , 0x01DEFAB0, [4])

/** Advertize Switch Input External **/
#define swdata                      DataAry(uint32_t       , 0x01DEFBE0, [4])
#define swdatae                     DataAry(uint32_t       , 0x01DEFB50, [4])

/** Advertize Repeat Timer Internal **/
#define SW_REP                      DataAry(int32_t        , 0x01934BF0, [4])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Global pad read set and check **/
void        PadReadOn(        void );
void        PadReadOff(       void );
bool32_t    CheckPadReadMode( void );

/** Player specific pad read set and check **/
void        PadReadOnP(        uint8_t pno );
void        PadReadOffP(       uint8_t pno );
bool32_t    CheckPadReadModeP( uint8_t pno );

EXTERN_END

#endif/*_SA2B_INPUT_H_*/
