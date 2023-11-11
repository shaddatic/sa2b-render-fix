/*
*   Sonic Adventure Mod Tools (SA2B) - '/config.h'
*
*   Contains functions for loading, reading, and saving Mod Configuration/Ini files
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_CONFIG_H_
#define _SAMT_CONFIG_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct _config    config;

/************************/
/*  Functions           */
/************************/
EXTERN_START
config*     ConfigOpen(const utf8* fn);
void        ConfigClose(config* pconf);
void        ConfigSave(const config* pconf);

/** Get Functions **/
sint32      ConfigGetInt(const config* pconf, const utf8* sect, const utf8* key, sint32 def);
bool        ConfigGetBool(const config* pconf, const utf8* sect, const utf8* key, bool def);
utf8*       ConfigGetString(const config* pconf, const utf8* sect, const utf8* key, const utf8* def);

/** Set Functions **/
void        ConfigSetInt(config* pconf, const utf8* sect, const utf8* key, sint32 set);
void        ConfigSetBool(config* pconf, const utf8* sect, const utf8* key, bool set);
void        ConfigSetString(config* pconf, const utf8* sect, const utf8* key, const utf8* set);

/** Debug Printout **/
void        ConfigPrint(const config* pconf);

/*
*   Quick Open
*/
config*     ConfigOpen2(const utf8* path, const utf8* name);

EXTERN_END

#endif /* _SAMT_CONFIG_H_ */