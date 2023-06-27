#pragma once

struct task;

FuncUsr(AL_CalcIconColor, 0x0053B940);
inline sint32 AL_CalcIconColor(task* tp)
{
	sint32 result;
	__asm
	{
		mov eax, [tp]
		call ptrs::AL_CalcIconColor
		mov [result], eax
	}
	return result;
}