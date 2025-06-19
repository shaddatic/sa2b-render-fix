/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/modinfo.h'
*
*   Description:
*     For getting mod information on other currently active mods.
*
*   Notes:
*     - Requires Mod Loader version >= 9
*/
#ifndef H_SAMT_MODINFO
#define H_SAMT_MODINFO

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** DLL Handle ******************************************************************************/
typedef struct mt_dllhandle             mt_dllhandle; /* windows hmodule                        */

/****** Config **********************************************************************************/
typedef struct mt_config                mt_config; /* config file                               */

/********************************/
/*  Structures                  */
/********************************/
/****** Mod Dependency Entry ********************************************************************/
typedef struct ml_moddeps
{
    const c8*              puID;        /* mod ID, from mod.ini                                 */
    const c8*              puPath;      /* expected mod path                                    */
    const c8*              puName;      /* mod name, from mod.ini                               */
    const c8*              puLink;      /* mod download link                                    */
}
ml_moddeps;

/****** Mod Info ********************************************************************************/
typedef struct ml_modinfo
{
    const c8*            puName;        /* mod name, from mod.ini                               */
    const c8*            puAuthor;      /* mod authors, from mod.ini                            */
    const c8*            puDesc;        /* mod description, from mod.ini                        */
    const c8*            puVersion;     /* mod version, from mod.ini                            */
    const c8*            puPath;        /* mod path                                             */
    const c8*            puID;          /* mod ID, from mod.ini                                 */

    const mt_dllhandle*      pDll;      /* pointer to DLL handle                                */

    bool        bSaveRedirectMain;      /* mod has redirected the main save path                */
    bool        bSaveRedirectChao;      /* mod has redirected the chao save path                */

    const ml_moddeps*   pDepsList;      /* pointer to mod dependency list                       */
    int                nbDepsList;      /* number of dependency entries                         */
}
ml_modinfo;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Mod Loader Support **********************************************************************/
/*
*   Description:
*     Check if the 'Mod' helper functions are supported by the current Mod Loader version.
*
*   Returns:
*     'true' if the Mod Loader version is >= 9; or 'false' if not.
*/
bool    miCheckSupport( void );

/****** Total Mod Count *************************************************************************/
/*
*   Description:
*     Get the total number of currently active mods, and by extension the number of mod slots
*   in use.
*/
size    miGetModCount( void );

/****** Get Mod Info ****************************************************************************/
/*
*   Description:
*     Get a mod info via its set ID string (recommended).
*
*   Parameters:
*     - puID        : mod id string
*
*   Returns:
*     Mod info structure; or 'nullptr' if the mod is not active.
*/
const ml_modinfo* miGetInfoByID( const c8* puID );
/*
*   Description:
*     Get a mod info via its position in the mod list.
*
*   Parameters:
*     - index       : mod position index value, starting at 0
*
*   Returns:
*     Mod info structure; or 'nullptr' if the mod is not active.
*/
const ml_modinfo* miGetInfoByIndex( usize index );
/*
*   Description:
*     Get a mod info via its DLL handle.
*
*   Parameters:
*     - pDll        : dll handle
*
*   Returns:
*     Mod info structure; or 'nullptr' if the dll is not linked to a mod.
*/
const ml_modinfo* miGetInfoByDll( const mt_dllhandle* pDll );
/*
*   Description:
*     Get a mod info via its DLL file name.
*
*   Parameters:
*     - puDllName   : name of the dll file, excluding the extension
*
*   Returns:
*     Mod info structure; or 'nullptr' if the mod is not active.
*/
const ml_modinfo* miGetInfoByDllName( const c8* puDllName );
/*
*   Description:
*     Get a mod info via its name.
*
*   Parameters:
*     - puName      : mod name
*
*   Returns:
*     Mod info structure; or 'nullptr' if the mod is not active.
*/
const ml_modinfo* miGetInfoByName( const c8* puName );
/*
*   Description:
*     Get a mod info via its filesystem path, starting at the game directory.
*
*   Parameters:
*     - puPath      : mod path
*
*   Returns:
*     Mod info structure; or 'nullptr' if the mod is not active.
*/
const ml_modinfo* miGetInfoByPath( const c8* puPath );

/****** Additional Info Functions ***************************************************************/
/*
*   Description:
*     Get the position index of a mod via its mod info structure.
*
*   Returns:
*     Position index in the mod list; or '-1' on failure.
*/
size    miGetIndex( const ml_modinfo* pModInfo );
/*
*   Description:
*     Get a DLL export of a mod via its mod info structure.
*
*   Returns:
*     Exported function or data; or 'nullptr' on failure.
*/
void*   miGetExport( const ml_modinfo* pModInfo, const c7* pcExportName );
/*
*   Description:
*     Get 
*
*   Returns:
*     User config of mod; or 'nullptr' on failure.
*/
mt_config* miGetConfig( const ml_modinfo* pModInfo );

EXTERN_END

#endif/*H_SAMT_MODINFO*/
