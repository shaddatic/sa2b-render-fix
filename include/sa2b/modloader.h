/*
*   Sonic Adventure Mod Tools (SA2B) - '/modloader.h'
*
*   Contains functions and definitions for the Mod Loader and its HelperFunctions
*
*   Contributors:
*   -   SA2 Mod Loader/Manager Team
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/

#ifndef _SAMT_MODLOADER_H_
#define _SAMT_MODLOADER_H_

/************************/
/*  Mod Loader Version  */
/************************/
#define	MOD_LOADER_VER  (8)

/************************/
/*  Abstract Types      */
/************************/
typedef int		ModInfo[10];
typedef void	HelperFunctions;

/************************/
/*  Functions           */
/************************/
EXTERN_START

int			ML_GetVersion( void );

const char* ML_GetMainSavePath( void );
const char* ML_GetChaoSavePath( void );

const char* ML_GetReplaceablePath( const char* path );

void		ML_ReplaceFile( const char* path, const char* pathNew );

void		ML_SetWindowTitle( const wchar_t* wTitle );

void		ML_SetDebugFontParams( float scale, int color );

void		ML_SetDebugFontScale( float scale );
void		ML_SetDebugFontColor( int color );

void		ML_DisplayDebugString( int njmLocation, const char* string );
void		ML_DisplayDebugStringF( int njmLocation, char* buffer, const char* format, ... );
void		ML_DisplayDebugInt( int njmLocation, int val, int nbDigits );

EXTERN_END

#endif /* _SAMT_MODLOADER_H_ */

/*
*	Execute at game startup:
*
	extern "C" __declspec(dllexport)
	void __cdecl
	Init(const char* path, const HelperFunctions* pHelperFunctions)
	{
		SAMT_Init(path, pHelperFunctions);
	}
*
*	Execute every rendered frame:
*
	extern "C" __declspec(dllexport)
	void __cdecl
	OnFrame()
	{
		
	}
*
*	Execute before the game processes input:
*
	extern "C" __declspec(dllexport)
	void __cdecl
	OnInput()
	{
		
	}
*
*	Execute when the game processes input:
*
	extern "C" __declspec(dllexport)
	void __cdecl
	OnControl()
	{
		
	}
*
*	Execute on game close:
*
	extern "C" __declspec(dllexport)
	void __cdecl
	OnExit(uint32 uExitCode, int a1, int a2)
	{
		
	}
*
*	Valid Mod Info ($ == SA2 or SADX):
* 
	extern "C" __declspec(dllexport)
	ModInfo $ModInfo = { MOD_LOADER_VER };
*/