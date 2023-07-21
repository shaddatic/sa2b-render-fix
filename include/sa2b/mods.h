/*
*   Sonic Adventure Mod Tools (SA2B) - '/mods.h'
*
*   Contains functions for interacting with other mods
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/

#ifndef _SAMT_MODS_H_
#define _SAMT_MODS_H_

typedef void        mod_handle;
typedef _config     config;

mod_handle*	GetModHandle(const char* pDllName);
mod_handle*	GetModHandleW(const wchar_t* pDllName);

bool		CheckForMod(const char* pDllName);
bool		CheckForModW(const wchar_t* pDllName);

void*		GetModAddress(mod_handle* pModHandle, const char* pAddrName);

config*     GetModConfig(mod_handle* pModHandle);

#endif /* _SAMT_MODS_H_ */