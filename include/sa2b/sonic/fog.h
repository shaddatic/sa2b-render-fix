/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/fog.h'
*
*   Description:
*     Game fog control, including setting and loading.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_FOG
#define H_SA2B_FOG

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Fog Density Mode ************************************************************/
enum
{
    FOG_MD_OFF,                 /* fog off                                          */
    FOG_MD_LINEAR,              /* linear fog                                       */
    FOG_MD_EXPONENT,            /* exponent                                         */
    FOG_MD_EXPONENT2,           /* exponent 2                                       */
    FOG_MD_REVEXPONENT,         /* reverse exponent                                 */
    FOG_MD_REVEXPONENT2,        /* reverse exponent 2                               */
};

/************************/
/*  Structures          */
/************************/
/****** Fog Data ********************************************************************/
typedef struct
{
    s32       mode;             /* fog mode                                         */
    NJS_COLOR color;            /* fog color                                        */
    f32       far;              /* far plane                                        */
    f32       near;             /* near plane                                       */
    f32       fogtable[128];    /* fog table                                        */
}
FOG_DATA;

/****** Fog Work ********************************************************************/
typedef struct
{
    FOG_DATA* pFogA;
    FOG_DATA* pFogB;
    f32       ratio;
    s32       lock;
}
FOG_WORK;

/************************/
/*  Data                */
/************************/
/****** Fog Work ********************************************************************/
#define FogWork                 DATA_REF(FOG_WORK , 0x01AEFEA4)
#define FogWorkP                DATA_REF(FOG_WORK*, 0x01A5A34C)

/************************/
/*  Prototypes          */
/************************/
/****** Create Manager **************************************************************/
/*
*   Description:
*     Create fog manager task and initiate system fog parameters.
*/
void    CreateFogManager( void );

/****** Create Manager Ex ***********************************************************/
/*
*   Description:
*     Create, load, and set fog manager task in one function call. This function is
*   equivalent to:
*
*       FOG_DATA fogdat;
* 
*       CreateFogManager();
*       LoadFogFile( "fog.bin", &fogdat );
*       SetFog( &fogdat );
*
*   Parameters:
*     - fname       : fog file
*     - pFog        : fog data buffer
*/
void    CreateFogManagerEx( const char* fname, FOG_DATA* pFog );

/****** Free Manager ****************************************************************/
/*
*   Description:
*     Free fog manager task and reset system fog parameters.
*/
void    FreeFogManager( void );

/****** Load Fog File ***************************************************************/
/*
*   Description:
*     Load a fog file into a fog data buffer.
*
*   Parameters:
*     - fname       : fog file
*     - pFog        : fog data buffer
* 
*   Returns:
*     '1' on success; or '0' on failure.
*/
s32     LoadFogFile( const char* fname, FOG_DATA* pFog );

/****** Set Fog *********************************************************************/
/*
*   Description:
*     Set a single fog to the fog work.
*
*   Parameters:
*     - pFog        : fog data buffer
*/
void    SetFog( FOG_DATA* pFog );
/*
*   Description:
*     Set multiple fogs to the fog work, linearly interpolating between at 'ratio';
*   a value of '0.f' being fog A, and '1.f' being fog B.
*
*
*   Parameters:
*     - pFogA       : fog data buffer, A
*     - pFogB       : fog data buffer, B
*     - ratio       : interpolation ratio from fog A to B                      [0~1]
*/
void    SetMultiFog( FOG_DATA* pFogA, FOG_DATA* pFogB, f32 ratio );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS

/****** Standard ********************************************************************/
#define FogManagerCreate_p          FUNC_PTR(void, __cdecl, (void), 0x006DFE90)
#define FreeFogManager_p            FUNC_PTR(void, __cdecl, (void), 0x006DFE10)


/****** Usercall ********************************************************************/
#define LoadFogFile_p               ((void*)0x006DF840)
#define FogManagerCreateEx_p        ((void*)0x006DFF00)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FOG*/
