/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/light.h'
*
*   Description:
*     Header for the game's lighting system.
*/
#ifndef H_SA2B_LIGHT
#define H_SA2B_LIGHT

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Light Struct ****************************************************************************/
typedef struct light
{
    f32         x,y,z;              /* light vector                                             */
    f32         inten;              /* light intensity                                          */
    f32         ambient;            /* light ambient intensity                                  */
    f32         r,g,b;              /* light color, rgb                                         */
}
LIGHT;

/****** Light Struct (GC) ***********************************************************************/
typedef struct lightgc
{
    f32         x,y,z;              /* light vector                                             */
    f32         lr,lg,lb;           /* light color, rgb                                         */
    f32         ar,ag,ab;           /* ambient color, rgb                                       */
    u32         flag;               /* light flag                                               */

    u32         pad[2];             /* padding                                                  */
}
LIGHT_GC;

/********************************/
/*  Data                        */
/********************************/
/****** Player Light Index **********************************************************************/
#define PlayerLight                 DATA_ARY(uint8_t   , 0x01DE4664, [2])

/****** Player Iron Bar Index *******************************************************************/
#define IronBarLights               DATA_ARY(uint8_t   , 0x01DE4662, [2])

/****** Light Data ******************************************************************************/
#define Lights                      DATA_ARY(LIGHT     , 0x01DE4280, [12])
#define LightsGC                    DATA_ARY(LIGHT_GC  , 0x01DE4420, [12])

/****** Default Light Index *********************************************************************/
#define DefaultPlayerLight          DATA_REF(uint8_t   , 0x01DE4660)
#define DefaultLight                DATA_REF(uint8_t   , 0x01DE4400)

/****** Unused Vector ***************************************************************************/
#define UnusedLightVec              DATA_REF(NJS_VECTOR, 0x1DD94A0)

/********************************/
/*  Functions                   */
/********************************/
/****** Load Light File *************************************************************************/
/*
*   Description:
*     Load a light binary file into 'Lights' array, and 'LightsGC' array if '_gc' variant is
*   found.
*
*   Notes:
*     - Light files are in the 'gd_PC' directory as '#_light.bin' or '#_light_gc.bin'.
*
*   Parameters:
*     - pcFileName  : light file name, including extension
*/
s32     LoadLightFile( const c7* pcFileName );

/****** Set Draw Light **************************************************************************/
/*
*   Description:
*     Set light info for drawing by index.
*
*   Parameters:
*     - light       : light index
*/
void    SetLight( s32 light );

/****** Set Player Draw Light *******************************************************************/
/*
*   Description:
*     Set default and draw light index for the players.
*
*   Parameters:
*     - pno         : player number
*     - light       : light index
*/
void    SetPlayerLight( s32 pno, int light );

/****** Set Light Data **************************************************************************/
/*
*   Description:
*     Set a light index to a given light structure.
*
*   Parameters:
*     - n           : light index
*     - light       : light structure
*/
void    SetLightStruct( s32 n, const LIGHT*    light );
/*
*   Description:
*     Set light vector for given light index.
*
*   Parameters:
*     - n           : light index
*     - x,y,z       : light vector
*/
void    SetLightVector( s32 n, f32 x, f32 y, f32 z );

/*
*   Description:
*     Set light intensity for given light index.
*
*   Parameters:
*     - n           : light index
*     - inten       : light intensity
*/
void    SetLightIntensity( s32 n, f32 inten );
/*
*   Description:
*     Set light ambient intensity for given light index.
*
*   Parameters:
*     - n           : light index
*     - ambient     : light ambient intensity
*/
void    SetLightAmbient( s32 n, f32 ambient );
/*
*   Description:
*     Set light color for given light index.
*
*   Parameters:
*     - n           : light index
*     - r,g,b       : light color
*/
void    SetLightColor( s32 n, f32 r, f32 g, f32 b );

/****** Set Light Data (GC) *********************************************************************/
/*
*   Description:
*     Set a light index to a given light structure.
*
*   Parameters:
*     - n           : light index
*     - light       : light structure
*/
void    SetLightStructGC( s32 n, const LIGHT_GC* light );
/*
*   Description:
*     Set light vector for given light index.
*
*   Parameters:
*     - n           : light index
*     - x,y,z       : light vector
*/
void    SetLightVectorGC( s32 n, f32 x, f32 y, f32 z );
/*
*   Description:
*     Set light color for given light index.
*
*   Parameters:
*     - n           : light index
*     - r,g,b       : light color
*/
void    SetLightColorGC( s32 n, f32 r, f32 g, f32 b );
/*
*   Description:
*     Set light ambient intensity for given light index.
*
*   Parameters:
*     - n           : light index
*     - r,g,b       : light ambient color
*/
void    SetLightAmbientGC( s32 n, f32 r, f32 g, f32 b );
/*
*   Description:
*     Set light on state for given light index.
*
*   Notes:
*     - if set to 'OFF', the underlying 'LIGHT' struct will be used.
*
*   Parameters:
*     - n           : light index
*     - sw          : light switch state                                               [ON/OFF]
*/
void    SetLightSwitchGC( s32 n, b32 sw );

/****** Set Default Light Index *****************************************************************/
/*
*   Description:
*     Set default light index for most objects, specifically ones that don't set their own.
*
*   Parameters:
*     - light       : light index
*/
void    SetDefaultLight( s32 light );
/*
*   Description:
*     Set default player light index, some objects use this too.
*
*   Parameters:
*     - light       : light index
*/
void    SetDefaultPlayerLight( s32 light );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define LoadLightFile_p             FUNC_PTR(int32_t, __fastcall, (const char*), 0x006C3AE0)

/****** Usercall Pointers ***********************************************************************/
#define SetLightIndex_p             ((void*)0x00487060) /* ###(EAX)                             */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_LIGHT*/
