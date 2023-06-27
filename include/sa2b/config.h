/*
*	Sonic Adventure Mod Toolkit
*
*	Config.h
*/

#ifndef _SAMT_CONFIG_H_
#define _SAMT_CONFIG_H_

typedef struct _config	config;

[[nodiscard]]
config*		ConfigOpen(const utf8* fn);
void		ConfigClose(config* pconf);
void		ConfigSave(const config* pconf);

sint32		ConfigGetInt(const config* pconf, const utf8* sect, const utf8* key, sint32 def);
bool		ConfigGetBool(const config* pconf, const utf8* sect, const utf8* key, bool def);
utf8*		ConfigGetString(const config* pconf, const utf8* sect, const utf8* key, const utf8* def);

void		ConfigSetInt(config* pconf, const utf8* sect, const utf8* key, sint32 set);
void		ConfigSetBool(config* pconf, const utf8* sect, const utf8* key, bool set);
void		ConfigSetString(config* pconf, const utf8* sect, const utf8* key, const utf8* set);

void		ConfigPrint(const config* pconf);

config*		ConfigOpen2(const utf8* path, const utf8* name);

#endif /* _SAMT_CONFIG_H_ */