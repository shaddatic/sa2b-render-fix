#pragma once

struct task;
struct AL_GENE;
struct CCL_INFO;

enum EggColor : sint32
{
	EggColor_Normal = 0x0,
	EggColor_Yellow = 0x1,
	EggColor_White = 0x2,
	EggColor_Brown = 0x3,
	EggColor_SkyBlue = 0x4,
	EggColor_Pink = 0x5,
	EggColor_Blue = 0x6,
	EggColor_Gray = 0x7,
	EggColor_Green = 0x8,
	EggColor_Red = 0x9,
	EggColor_AppleGreen = 0xA,
	EggColor_Purple = 0xB,
	EggColor_Orange = 0xC,
	EggColor_Black = 0xD,
	EggColor_BlendYellow = 0xE,
	EggColor_BlendWhite = 0xF,
	EggColor_BlendBrown = 0x10,
	EggColor_BlendSkyBlue = 0x11,
	EggColor_BlendPink = 0x12,
	EggColor_BlendBlue = 0x13,
	EggColor_BlendGray = 0x14,
	EggColor_BlendGreen = 0x15,
	EggColor_BlendRed = 0x16,
	EggColor_BlendAppleGreen = 0x17,
	EggColor_BlendPurple = 0x18,
	EggColor_BlendOrange = 0x19,
	EggColor_BlendBlack = 0x1A,
	EggColor_ShinyNormal = 0x1B,
	EggColor_ShinyYellow = 0x1C,
	EggColor_ShinyWhite = 0x1D,
	EggColor_ShinyBrown = 0x1E,
	EggColor_ShinySkyBlue = 0x1F,
	EggColor_ShinyPink = 0x20,
	EggColor_ShinyBlue = 0x21,
	EggColor_ShinyGray = 0x22,
	EggColor_ShinyGreen = 0x23,
	EggColor_ShinyRed = 0x24,
	EggColor_ShinyAppleGreen = 0x25,
	EggColor_ShinyPurple = 0x26,
	EggColor_ShinyOrange = 0x27,
	EggColor_ShinyBlack = 0x28,
	EggColor_ShinyBlendYellow = 0x29,
	EggColor_ShinyBlendWhite = 0x2A,
	EggColor_ShinyBlendBrown = 0x2B,
	EggColor_ShinyBlendSkyBlue = 0x2C,
	EggColor_ShinyBlendPink = 0x2D,
	EggColor_ShinyBlendBlue = 0x2E,
	EggColor_ShinyBlendGray = 0x2F,
	EggColor_ShinyBlendGreen = 0x30,
	EggColor_ShinyBlendRed = 0x31,
	EggColor_ShinyBlendAppleGreen = 0x32,
	EggColor_ShinyBlendPurple = 0x33,
	EggColor_ShinyBlendOrange = 0x34,
	EggColor_ShinyBlendBlack = 0x35,
	EggColor_Gold = 0x36,
	EggColor_Silver = 0x37,
	EggColor_Ruby = 0x38,
	EggColor_Sapphire = 0x39,
	EggColor_Emerald = 0x3A,
	EggColor_Amethyst = 0x3B,
	EggColor_Aquamarine = 0x3C,
	EggColor_Garnet = 0x3D,
	EggColor_Onyx = 0x3E,
	EggColor_Peridot = 0x3F,
	EggColor_Topaz = 0x40,
	EggColor_Pearl = 0x41,
	EggColor_Env0 = 0x42, // Metal 1
	EggColor_Env1 = 0x43, // Metal 2
	EggColor_Env2 = 0x44, // Glass
	EggColor_Env3 = 0x45, // Moon
	EggColor_Env4 = 0x46, // Rare
	nbEggColor = 0x47,
};

struct EGG_WORK
{
	sint32 type;
	sint32 SwingFlag;
	sint32 nbSwing;
	sint32 HeldAng;
	float32 frame;
	sint32 BornTimer;
	float32 ScaleAll;
	float32 BuyoScale;
	float32 BuyoVelo;
	sint32 NoColliTimer;
	sint32 Color;
};

TaskFuncPtr(AL_EggExecutor, 0x0057B520);
TaskFuncPtr(AL_EggDisplayer, 0x0057B640);
TaskFuncPtr(AL_EggDestructor, 0x0057B9B0); // Same function as many other ALO objects

FuncPtr(task*, __cdecl, CreateEgg, (AL_GENE* pGene, CHAO_PARAM_GC* pParamGC, sint32 IsParamCopy, const NJS_POINT3* pPos, sint32 type), 0x57B9C0);

DataPtr(CCL_INFO, AL_EggColInfo, 0x008A5840);

DataPtr(NJS_CNK_MODEL, model_chao_egg, 0x0125D31C);