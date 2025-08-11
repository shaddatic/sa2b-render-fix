/*
*   SA2 Render Fix - '/rfapi_config.h'
*
*   Description:
*     The 'Config' API module is for retrieving user configuration settings directly. This is
*   not recommended for longterm use outside of very specific circumstances, as config
*   definitions change frequently.
*     If you do use it, restrict it to certain versions of Render Fix to ensure it works
*   correctly.
* 
*   Version History:
*     - v1.3.0.0: Version 0, initial release
* 
*   Availability:
*     - RF_EarlyInit    : Yes
*     - RF_Init         : Yes
*     - After Init      : No
*/
#ifndef H_RFAPI_CONFIG
#define H_RFAPI_CONFIG

/********************************/
/*  API Structures              */
/********************************/
/****** Config API ******************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Config Settings ***********************************/
    /*
    *   Description:
    *     Read user-settings inside Render Fix's configuration (config.ini) file. It's
    *   important to remember that strings are stored in UTF-8 format, not basic ASCII.
    *
    *   Parameters:
    *     - section   : The section of the config option (eg. "main")
    *     - key       : The key of the config option (eg. "backface_cull")
    *     - deflt     : The default value for the option
    *
    *   Returns:
    *     The value of the config entry.
    */
    int32_t   (__cdecl* ConfigGetInt)(    const char* section, const char* key, int32_t   deflt );
    bool      (__cdecl* ConfigGetBool)(   const char* section, const char* key, bool      deflt );
    f64       (__cdecl* ConfigGetFloat)(  const char* section, const char* key, f64       deflt );
    const c8* (__cdecl* ConfigGetString)( const char* section, const char* key, const c8* deflt );
}
RFAPI_CONFIG;

#endif/*H_RFAPI_CONFIG*/
