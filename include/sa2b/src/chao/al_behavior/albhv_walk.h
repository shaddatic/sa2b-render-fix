#pragma once

#include <sa2b/src/chao/al_behavior.h>

FuncUsr(void, AL_WalkSelect, (task* tp), 0x005A3650)
{
	__asm
	{
		mov esi, [tp]
		call AL_WalkSelect_p
	}
}

BhavFuncPtr(ALBHV_Move, 0x00562D20);