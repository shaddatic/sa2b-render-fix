/*
*   Sonic Adventure Mod Tools (SA2B) - '/config.h'
*
*   Description:
*       Loading, reading, & saving .ini configuration files.
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
config* ConfigOpen( const utf8* fpath );

/** Save & close **/
void    ConfigSave( const config* pConf );
void    ConfigClose(      config* pConf );


/** Get functions **/
int32_t ConfigGetInt(    const config* pConf, const utf8* sect, const utf8* key, int32_t     def );
bool    ConfigGetBool(   const config* pConf, const utf8* sect, const utf8* key, bool        def );
utf8*   ConfigGetString( const config* pConf, const utf8* sect, const utf8* key, const utf8* def );

/** Set functions **/
void    ConfigSetInt(    config* pConf, const utf8* sect, const utf8* key, int32_t     set );
void    ConfigSetBool(   config* pConf, const utf8* sect, const utf8* key, bool        set );
void    ConfigSetString( config* pConf, const utf8* sect, const utf8* key, const utf8* set );

/** Open via fpath & fname **/
config* ConfigOpen2( const utf8* fpath, const utf8* fname );

EXTERN_END

#endif/*_SAMT_CONFIG_H_*/
