/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/dll.h'
*
*   Description:
*     For mounting and getting exported symbols from DLL libraries
*/
#ifndef H_SAMT_DLL
#define H_SAMT_DLL

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** DLL Handle ******************************************************************************/
typedef struct mt_dllhandle             mt_dllhandle; /* windows hmodule                        */

/********************************/
/*  Structures                  */
/********************************/
/****** DLL Exports *****************************************************************************/
typedef struct mt_dllexport
{
    const void* ppExportDst;        /* pointer to pointer to write export address to            */
    const c7*   pcExportName;       /* name of DLL library export                               */
}
mt_dllexport;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Get Handle ******************************************************************************/
/*
*   Description:
*     Get handle of mounted DLL by its file name.
*
*   Examples:
*     - mtDllGetMountedHandle( "Data_DLL" );
*
*   Parameters:
*     - puDllName   : name of dll file, excluding the extension
*
*   Returns:
*     The DLL handle ###; or 'nullptr' on failure.
*/
mt_dllhandle* mtDllGetMountedHandle( const c8* puDllName );

/****** Mount/Unmount DLL ***********************************************************************/
/*
*   Description:
*     Mount a new DLL file. Either a direct path can be used, or simply the file name of the
*   DLL; if the name is used, the local game path is searched first followed by the system
*   files.
*
*   Examples:
*     - mtDllMount( "mymodule" );
*     - mtDllMount( "./my/path/mymodule.dll" );
*
*   Parameters:
*     - puDllNamePath : file name of/path to dll
*
*   Returns:
*     New handle for mounted DLL; or 'nullptr' on failure.
*/
mt_dllhandle* mtDllMount( const c8* puDllNamePath );
/*
*   Description:
*     Unmount a DLL file.
*
*   Notes:
*     - This will release all data and functions in the DLL also, so care should be taken to
*       not reference any released memory addresses.
*
*   Parameters:
*     - pDll        : dll handle
*/
void    mtDllUnmount( mt_dllhandle* pDll );
/*
*   Description:
*     Mount a new DLL file using two path parameters, combined as ('puDllPath'/'puDllFile').
*
*   Examples:
*     - mtDllMount2( mtGetModPath(), "mydlls/mymodule.dll" );
*
*   Parameters:
*     - puDllPath   : left part of path
*     - puDllFile   : right part of path
* 
*   Returns:
*     New handle for mounted DLL; or 'nullptr' on failure.
*/
mt_dllhandle* mtDllMount2( const c8* puDllPath, const c8* puDllFile );

/****** DLL Exports *****************************************************************************/
/*
*   Description:
*     Get a DLL export from a DLL handle.
*
*   Parameters:
*     - pDll         : dll handle
*     - pcExportName : export function/data name
*
*   Returns:
*     The DLL export; or 'nullptr' on failure.
*/
void*   mtDllGetExport( const mt_dllhandle* pDll, const c7* pcExportName );
/*
*   Description:
*     Get a list of DLL exports in one call.
*
*   Parameters:
*     - pDll         : dll handle
*     - pExportList  : export structure list
*     - nbExportList : number of export structures
*
*   Returns:
*     Number of exports successfully retrieved.
*/
size    mtDllGetExportList( const mt_dllhandle* pDll, mt_dllexport* pExportList, usize nbExportList );

EXTERN_END

#endif/*H_SAMT_DLL*/
