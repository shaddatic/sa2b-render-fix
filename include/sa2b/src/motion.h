#pragma once

struct MOTION_INFO
{
	short mode;
	uint8 UNDEF0;
	uint8 UNDEF1;
	float frame;
	float start;
	float end;
	float spd;
	void* pMotion;
};

struct MOTION_CTRL
{
	short flag;
	short posture;
	int curr_num;
	int next_num;
	float multi_spd;
	float link_spd;
	float ratio;
	MOTION_INFO minfo[2];
	int table;
};

struct MOTION_TABLE
{
	void* pMotion;
	short mode;
	short posture;
	int next;
	int link_step;
	float start;
	float end;
	float spd;
};

inline void SetMotionLink(MOTION_CTRL* pMtnCtrl, int MtnNum)
{
	const void* SetMotionLinkPtr = (void*)0x00793C40;
	__asm
	{
		mov edx, [MtnNum]
		mov eax, [pMtnCtrl]
		call SetMotionLinkPtr
	}
}

inline void SetMotionLinkStep(MOTION_CTRL* pMtnCtrl, int MtnNum, unsigned __int16 step)
{
	const void* pSetMotionLinkStep = (void*)0x00793D30;
	__asm
	{
		push step
		mov edx, MtnNum
		mov eax, pMtnCtrl
		call pSetMotionLinkStep
		add esp, 4
	}
}