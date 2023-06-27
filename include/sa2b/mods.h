/*
*	Sonic Adventure Mod Tools - Other Mod Tools Header
*/

#ifndef _SAMT_MODS_H_
#define _SAMT_MODS_H_

typedef void ModHandle;

ModHandle*	GetModHandle(const char* pDllName);
ModHandle*	GetModHandleW(const wchar_t* pDllName);

bool		CheckForMod(const char* pDllName);
bool		CheckForModW(const wchar_t* pDllName);

void*		GetModAddress(ModHandle* pModHandle, const char* pAddrName);

#endif /* _SAMT_MODS_H_ */