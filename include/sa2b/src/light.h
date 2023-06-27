#pragma once

struct __declspec(align(4)) Light
{
	NJS_POINT3 direction;
	float intensity;
	float ambient;
	NJS_POINT3 color;
};

struct __declspec(align(4)) LightGC
{
	NJS_POINT3 direction;
	NJS_POINT3 lightColor;
	NJS_POINT3 ambientReg;
	int flags;
	int unused;
	int unk;
};

DataAry(char, LightIndex, 0x01DE4664, [2]);
DataRef(char, LightIndexBackupMaybe, 0x01DE4400);
DataAry(Light, Lights, 0x01DE4280, [12]);
DataAry(LightGC, LightsGC, 0x01DE4420, [12]);

FuncPtr(sint32, __fastcall, LoadStageLight, (const char* filename), 0x006C3AE0);