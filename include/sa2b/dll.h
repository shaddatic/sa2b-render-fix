/*
*   Sonic Adventure Mod Tools (SA2B) - '/dll.h'
*
*   Description:
*     For mounting and getting exported symbols from DLL libraries
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_DLL
#define H_SAMT_DLL

EXTERN_START

/************************/
/*  Opaque Types        */
/************************/
/****** DLL Handle ******************************************************************/
typedef struct dll_handle   dll_handle; /* HMODULE                                  */

/************************/
/*  Structures          */
/************************/
/****** DLL Exports *****************************************************************/
typedef struct dll_export
{
    const void* pPtr;   /* pointer to pointer to write export address to            */
    const char* cName;  /* name of DLL library export                               */
}
dll_export;

/************************/
/*  Prototypes          */
/************************/
/****** Get Handle ******************************************************************/
/*
*   Description:
*     Get handle of already mounted DLL by file name.
*
*   Examples:
*     DLL_GetHandle( "name-of-dll" );
*
*   Parameters:
*     - uName   : name of the DLL file
*
*   Returns:
*     The DLL handle, or nullptr if a DLL of that name is not mounted
*/
dll_handle* DLL_GetHandle( const utf8* uName );

/****** Mount/Unmount DLL ***********************************************************/
/*
*   Description:
*     Mount a DLL from either the main system files or a local path. The local path
*   will be searched first. If the DLL is not found locally, the system files will
*   then be searched.
*
*   Examples:
*     DLL_Mount( "file" );
*     DLL_Mount( "./path/to/dll/file.dll" );
*
*   Parameters:
*     - uPath   : name/path to DLL file
*
*   Returns:
*     The DLL handle, or nullptr if the file is not found
*/
dll_handle* DLL_Mount( const utf8* uPath );
/*
*   Description:
*     Mount a DLL like above, but instead using two strings which are then
*   concatonated together ("'uPathL'/'uPathR'").
*
*   Examples:
*     DLL_Mount2( GetModPath(), "file.dll" );
*
*   Parameters:
*     - uPathL  : string to use on the left side of the path
*     - uPathR  : string to use on the right side of the path
*
*   Returns:
*     The DLL handle, or nullptr if the file is not found
*/
dll_handle* DLL_Mount2( const utf8* uPathL, const utf8* uPathR );
/*
*   Description:
*     Unmount a DLL file. This will also release any data/functions from the
*   library; care should be taken to correctly clean up any references to them.
*
*   Parameters:
*     - pHdl    : handle to a dll to unmount
*/
void    DLL_Unmount( dll_handle* pHdl );

/****** Get Exports *****************************************************************/
/*
*   Description:
*     Get an exported pointer from a mounted DLL library, which may include
*   functions or data.
*
*   Parameters:
*     - pHdl    : handle to a dll to unmount
*     - cExName : name of the export in ASCII
* 
*   Returns:
*     A pointer to the DLL export, or nullptr if no export is found
*/
void*   DLL_GetExport(const dll_handle* pHdl, const char* cExName);
/*
*   Description:
*     Get a list of exported pointers from a mounted DLL library, which may include
*   functions or data.
*
*   Parameters:
*     - pHdl     : handle to a dll to unmount
*     - pExList  : pointer to an export list
*     - nbExList : number of entries in the export list
*/
void    DLL_GetExportList(const dll_handle* pHdl, const dll_export* pExList, size_t nbExList);

EXTERN_END

#endif/*H_SAMT_DLL*/
