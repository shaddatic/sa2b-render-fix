/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/particlecore.h'
*
*   Description:
*     Header for the game's particle system.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_PARTICLECORE
#define H_SA2B_PARTICLECORE

/************************/
/*  External Opaques    */
/************************/
#ifdef SAMT_INCL_INTERNAL

/****** Task ************************************************************************/
typedef struct task             task;

#endif/*SAMT_INCL_INTERNAL*/

EXTERN_START

/************************/
/*  Data                */
/************************/
#ifdef SAMT_INCL_INTERNAL

/****** Task Pointer ****************************************************************/
#define ParticleCoreTaskP       DATA_REF(task*, 0x01A5A3B8)

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Prototypes          */
/************************/
/****** Create/Free Particle Core ***************************************************/
/*
*   Description:
*     Create the Particle Core Task.
*
*   Notes:
*     - Only one can be created at a time.
*/
void    ParticleCoreCreate( void );
/*
*   Description:
*     Free the Particle Core Task.
*/
void    ParticleCoreFree( void );

/****** Clear Particles *************************************************************/
/*
*   Description:
*     Clear all particles.
*/
void    ParticleCoreClear( void );

#ifdef SAMT_INCL_INTERNAL

/****** Particle Core Init **********************************************************/
/*
*   Description:
*     Initiate Particle Core work data.
*/
void    ParticleCoreInit( void );

/****** Particle Core Task **********************************************************/
/*
*   Description:
*     Initiate Particle Core work data.
*
*   Parameters:
*     - tp          : task pointer
*/
void    ParticleCoreTask( task* tp );
/*
*   Description:
*     Particle Core Task executor.
*
*   Parameters:
*     - tp          : task pointer
*/
void    ParticleCoreExec( task* tp );
/*
*   Description:
*     Particle Core Task displayer.
*
*   Parameters:
*     - tp          : task pointer
*/
void    ParticleCoreDisp( task* tp );
/*
*   Description:
*     Particle Core Task destructor.
*
*   Parameters:
*     - tp          : task pointer
*/
void    ParticleCoreDest( task* tp );

/****** Particle Core Functions *****************************************************/
/*
*   Description:
*     Execute Particle Core.
*
*   Notes:
*     - Called inside Task function
*/
void    ParticleCoreExecute( void );
/*
*   Description:
*     Draw Particle Core.
*
*   Notes:
*     - Called inside Task function
*/
void    ParticleCoreDraw( void );

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Function Pointers   */
/************************/
#ifdef SAMT_INCL_FUNCPTRS

/****** Standard ********************************************************************/
#   define ParticleCoreClear_p          FUNC_PTR(void, __cdecl, (void) , 0x004925B0)
#   define ParticleCoreInit_p           FUNC_PTR(void, __cdecl, (void) , 0x004920A0)
#   define ParticleCoreTask_p           FUNC_PTR(void, __cdecl, (task*), 0x00491C20)
#   define ParticleCoreExec_p           FUNC_PTR(void, __cdecl, (task*), 0x00491BE0)
#   define ParticleCoreDisp_p           FUNC_PTR(void, __cdecl, (task*), 0x00491BF0)
#   define ParticleCoreDest_p           FUNC_PTR(void, __cdecl, (task*), 0x00491C00)
#   define ParticleCoreExecute_p        FUNC_PTR(void, __cdecl, (void) , 0x00492190)
#   define ParticleCoreDraw_p           FUNC_PTR(void, __cdecl, (void) , 0x00492390)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_PARTICLECORE*/
