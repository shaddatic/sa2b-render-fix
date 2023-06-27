#pragma once

void BGM_Play(const ansi* fadx);

FuncPtr(void, __cdecl, BGM_SetRound, (), 0x00442D90);
FuncPtr(void, __cdecl, BGM_Stop, (), 0x00442F50);

void Jingle_Play(const char* song);