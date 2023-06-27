#pragma once

/*
*	Define Functions
*/

#define AL_IsGarden() (ChaoStageNumber >= CHAO_STG_NEUT && ChaoStageNumber <= CHAO_STG_DARK)

/*
*	Enums
*/

enum eCHAO_STAGE_NUMBER
{	
	CHAO_STG_NONE = 0,
	CHAO_STG_NEUT = 1,
	CHAO_STG_HERO = 2,
	CHAO_STG_DARK = 3,
	CHAO_STG_RACE = 4,
	CHAO_STG_ENTRANCE = 5,
	CHAO_STG_KINDER = 6,
	CHAO_STG_LOBBY = 7,
	CHAO_STG_ENTRANCE_2P = 8,
	CHAO_STG_STADIUM = 9,
	CHAO_STG_KARATE = 10,
	CHAO_STG_KARATE_2P = 11,
	CHAO_STG_ODEKAKE = 12

/*	SADX ENUM
* 
* 	CHAO_STG_NONE = 0x0,
*	CHAO_STG_RACE = 0x1,
*	CHAO_STG_ENTRANCE = 0x2,
*	CHAO_STG_ODEKAKE = 0x3,
*	CHAO_STG_SS = 0x4,
*	CHAO_STG_EC = 0x5,
*	CHAO_STG_MR = 0x6,
*	CHAO_STG_BLACKMARKET = 0x7,
*	CHAO_STG_QUIT = 0x8,
*/
};

DataRef(eCHAO_STAGE_NUMBER, ChaoOldStageNumber, 0x13402AC);
DataRef(eCHAO_STAGE_NUMBER, ChaoStageNumber, 0x134046C);
DataRef(eCHAO_STAGE_NUMBER, ChaoNextStageNumber, 0x134062C);

FuncPtr(void, __cdecl, AL_ChangeStage, (sint32 NextStage), 0x0052B5B0);

eCHAO_STAGE_NUMBER AL_GetLastStageNumber();
eCHAO_STAGE_NUMBER AL_GetStageNumber();
eCHAO_STAGE_NUMBER AL_GetNextStageNumber();

sint32	AL_GetLocalChaoCount(sint32 stage);

sint32	AL_GetCurrGardenChaoCount();