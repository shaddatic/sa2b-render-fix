#pragma once

struct task;

enum eAL_EYE_NUM
{
	AL_EYE_NUM_NORMAL = 0x0,
	AL_EYE_NUM_KYA = 0x1,
	AL_EYE_NUM_NAMU = 0x2,
	AL_EYE_NUM_TOHOHO = 0x3,
	AL_EYE_NUM_NIKO = 0x4,
	AL_EYE_NUM_BIKKURI = 0x5,
	AL_EYE_NUM_GURUGURU = 0x6,
	AL_EYE_NUM_SUYASUYA = 0x7,
	AL_EYE_NUM_SHIROME = 0x8,
	AL_EYE_NUM_TRON = 0x9,
	AL_EYE_NUM_ANGER = 0xA,
	AL_EYE_NUM_NCHAOS = 0xB,
	AL_EYE_NUM_HCHAOS = 0xC,
	AL_EYE_NUM_DCHAOS = 0xD,
	AL_EYE_NUM_END = 0xE,
};

enum eAL_MOUTH_NUM
{
	AL_MOUTH_NUM_NONE = 0x0,
	AL_MOUTH_NUM_SHARK = 0x1,	// "TOOTHY GRIN"
	AL_MOUTH_NUM_HOYO = 0x2,	// "OPEN"
	AL_MOUTH_NUM_NIKO = 0x3,	// "V SMILE"
	AL_MOUTH_NUM_MUSU = 0x4,	// "V FROWN"
	AL_MOUTH_NUM_WAAI = 0x5,	// "OPEN SMILE"
	AL_MOUTH_NUM_UEEN = 0x6,	// "OPEN FROWN"
	AL_MOUTH_NUM_NEE = 0x7,
	AL_MOUTH_NUM_KOIKE = 0x8,	// "SQUIGGLE"
	AL_MOUTH_NUM_GEE = 0x9,		// "TOOTHY FROWN"
	AL_MOUTH_NUM_MUU = 0xA,
	AL_MOUTH_NUM_UWAAN = 0xB,	// "WIDE OPEN"
	AL_MOUTH_NUM_INO = 0xC,
	AL_MOUTH_NUM_END = 0xD,
};

DataAry(sint16, AL_EyeTexIdList, 0x008A7A70, [14]);
DataAry(sint16, EyeColorTexIdList, 0x008A7AC0, [12]);

DataAry(sint16, AL_MouthTexIdList, 0x008A7A8C, [13][2]);

void AL_FaceSetEye(task* tp, eAL_EYE_NUM EyeNum, sint32 timer);

void AL_FaceChangeEye(task* tp, eAL_EYE_NUM EyeNum);
void AL_FaceReturnDefaultEye(task* tp);

void AL_FaceSetMouth(task* tp, eAL_MOUTH_NUM MouthNum, sint32 timer);

void AL_FaceChangeMouth(task* tp, eAL_MOUTH_NUM MouthNum);
void AL_FaceReturnDefaultMouth(task* tp);

FuncPtr(void, __cdecl, AL_FaceEyeLidControl, (task* tp), 0x0053A1E0);

