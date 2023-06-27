#pragma once

DataRef(bool32, alCtrlMove, 0x01DBE634); // Chao Enable

void AL_EnableMove();
void AL_DisableMove();
bool32 AL_IsMovable();