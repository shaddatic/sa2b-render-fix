#pragma once

TaskFuncPtr(ALO_NestFlowerExecutor, 0x005AABF0);
TaskFuncPtr(ALO_NestFlowerDisplayer, 0x005AAC60);

FuncUsr(task*, ALO_NestFlowerCreate, (task* pNestTask, NJS_POINT3* pPos), 0x005AAD90)
{
	task* result;
	__asm
	{
		mov eax, [pNestTask]
		mov ebx, [pPos]
		call ptrs::ALO_CreateNest
		mov[result], eax
	}
	return result;
}

TaskFuncPtr(ALO_NestExecutor, 0x005AAE20);

FuncUsr(task*, ALO_CreateNest, (task* pChaoTask), 0x005AAF60)
{
	task* result;
	__asm 
	{
		mov esi, [pChaoTask]
		call ptrs::ALO_CreateNest
		mov [result], eax
	}
	return result;
}
