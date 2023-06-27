#pragma once

/*
*	Data References
*/

#define SHADERMODE_NONE		0
#define SHADERMODE_SHADOW	1
#define SHADERMODE_FOG		2
#define SHADERMODE_PALLETE	4

DataRef(bool,	LockShaders,	0x01A55709);
DataRef(sint32, ShaderMode,		0x01AF1960);
DataRef(sint32, ShaderLast,		0x01A5579C);

/*
*	Function Pointers
*/

FuncPtr(void, __stdcall, SetAndLoadShader, (sint32 idx), 0x00424050);

/*
*	User Functions
*/

void SetShaders(sint32 id);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* SetShaders_p;

#endif