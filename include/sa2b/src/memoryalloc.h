#pragma once

/*
*	Structs
*/

struct MemoryCookie
{
	int cookie;
	int data;
};

struct MemoryManager
{
	void*	(__cdecl* malloc)(size_t size, char* file, int line);
	void	(__cdecl* free)(void* block, char* file, int line);
	void*	(__cdecl* calloc)(size_t num, size_t size);
	void*	(__cdecl* realloc)(void* block, size_t count);
};

/*
*	Data References
*/

DataRef(MemoryManager*, pMemoryManager, 0x01D19CAC);

/*
*	Function Pointers
*/

FuncPtr(void*, __cdecl, _new, (size_t Size), 0x007A5DA1);
FuncPtr(void, __cdecl, _delete, (void* _Block), 0x007A5974);

FuncPtr(void*, __cdecl, _malloc, (size_t Size), 0x007A84A5);
FuncPtr(void, __cdecl, _free, (void* _Block), 0x07A80DD);

/*
*	Remade Functions
*/

void*	syMalloc(size_t size);
void*	syCalloc(size_t num, size_t size);
void	syFree(void* block);

void*	syRealloc(void* block, size_t count);