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

/************************/
/*  Opaque Types        */
/************************/
/****** DLL Handle ******************************************************************/
typedef struct dll_handle       dll_handle;

/****** Config **********************************************************************/
typedef struct mt_config           mt_config;

EXTERN_START

/************************/
/*  Structures          */
/************************/
/****** Mod Dependency Entry ********************************************************/
typedef struct mod_dependency
{
    const char* cID;
    const char* cPath;
    const char* cName;
    const char* cLink;
}
mod_dependency;

/****** Mod Info ********************************************************************/
typedef struct mod_info
{
    const char* cName;              /* mod name, from mod.ini                       */
    const char* cAuthor;            /* mod authors, from mod.ini                    */
    const char* cDescription;       /* mod description, from mod.ini                */
    const char* cVersion;           /* mod version, from mod.ini                    */
    const char* cPath;              /* mod path                                     */
    const char* cID;                /* mod ID, from mod.ini                         */

    const dll_handle* pDll;         /* pointer to DLL handle                        */

    bool bSaveRedirectMain;         /* mod has redirected the main save path        */
    bool bSaveRedirectChao;         /* mod has redirected the chao save path        */

    const mod_dependency* pDepList; /* pointer to mod dependency list               */
    int                  nbDepList; /* number of dependency entries                 */
}
mod_info;

/************************/
/*  Prototypes          */
/************************/
/****** Mod Loader Support **********************************************************/
/*
*   Description:
*     If the ModInfo functions are supported by the currently installed Mod Loader
*   version.
*
*   Returns:
*     If the Mod Loader HelperFunctions version is >= 9
*/
bool    MI_IsSupported( void );

/****** Mod Count *******************************************************************/
/*
*   Description:
*     Get the total number of mods enabled by the user.
*
*   Returns:
*     The total number of mods currently active
*/
int     MI_GetTotalNumber( void );

/****** Get Info ********************************************************************/
/*
*   Description:
*     Get mod info via ID string
*
*   Parameters:
*     - cID     : ID of the mod as defined in it's mod.ini
*
*   Returns:
*     A 'mod_info' pointer, or nullptr if no mod is found
*/
const mod_info* MI_GetInfoByID( const char* cID );
/*
*   Description:
*     Get mod info via DLL name
*
*   Parameters:
*     - uDLL    : name of the mod's DLL file
*
*   Returns:
*     A 'mod_info' pointer, or nullptr if no mod is found
*/
const mod_info* MI_GetInfoByDLL( const c8* uDLL );
/*
*   Description:
*     Get mod info via mod name
*
*   Parameters:
*     - cName   : name of the mod as defined in it's mod.ini
*
*   Returns:
*     A 'mod_info' pointer, or nullptr if no mod is found
*/
const mod_info* MI_GetInfoByName( const char* cName );
/*
*   Description:
*     Get mod info via mod path
*
*   Parameters:
*     - cPath   : path to the mod
*
*   Returns:
*     A 'mod_info' pointer, or nullptr if no mod is found
*/
const mod_info* MI_GetInfoByPath( const char* cPath );
/*
*   Description:
*     Get mod info via mod position in the user's mod list
*
*   Parameters:
*     - index   : mod list index of the mod
* 
*   Returns:
*     A 'mod_info' pointer, or nullptr if no mod is found
*/
const mod_info* MI_GetInfoByPosition( int index );

/****** Info Function ***************************************************************/
/*
*   Description:
*     Get a mod DLL export via it's mod_info. Calls 'DLL_GetExport' internally.
*
*   Parameters:
*     - pMod    : mod info pointer
*     - cExName : DLL export identifier
* 
*   Returns:
*     A pointer to the DLL export, or nullptr if no export is found
*/
void*   MI_GetExport( const mod_info* pMod, const char* cExName );
/*
*   Description:
*     Open a mod's config file via it's mod info. Calls 'ConfigOpen2' internally.
*
*   Parameters:
*     - pMod    : mod info pointer
* 
*   Returns:
*     A config pointer created from the mod's config.ini
*/
mt_config* MI_GetConfig( const mod_info* pMod );

EXTERN_END

#endif/*H_SAMT_MODINFO*/
