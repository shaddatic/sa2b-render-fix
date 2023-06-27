#pragma once

enum : sint32
{
	MD_GAME_PAUSE = 0x11,
	NUM_GAMEMD,
};

/*
	MD_GAME_INIT = 0x0,
	MD_GAME_INIT2 = 0x1,
	MD_GAME_REINIT = 0x2,
	MD_GAME_REINIT2 = 0x3,
	MD_GAME_FADEIN = 0x4,
	MD_GAME_FADEOUT_CLEAR = 0x5,
	MD_GAME_FADEOUT_MISS = 0x6,
	MD_GAME_FADEOUT_MISS_RESTART = 0x7,
	MD_GAME_FADEOUT_OVER = 0x8,
	MD_GAME_FADEOUT_CHANGE = 0x9,
	MD_GAME_FADEOUT_CHANGE2 = 0xA,
	MD_GAME_FADEOUT_RESTART = 0xB,
	MD_GAME_FADEOUT_RENEW = 0xC,
	MD_GAME_FADEOUT_TITLE = 0xD,
	MD_GAME_FADEOUT_STAFFROLL = 0xE,
	MD_GAME_MAIN = 0xF,
	MD_GAME_PAUSE = 0x10,
	MD_GAME_END = 0x11,
	MD_GAME_OVER = 0x12,
	MD_GAME_CONTINUE = 0x13,
	MD_GAME_ABORT = 0x14,
	MD_GAME_STAGENAME_INIT = 0x15,
	MD_GAME_STAGENAME = 0x16,
	MD_GAME_TRIAL_OVER = 0x17,
	MD_GAME_END2 = 0x18,
	MD_GAME_MAIN_KEY_RELEASE_WAIT = 0x19,
	NUM_GAMEMD = 0x1A,
*/

enum : sint32
{
	JAPANESE,
	ENGLISH,
	GERMAN,
	FRENCH,
	SPANISH,
	ITALIAN,
	NUM_LANGUAGE,
};

DataRef(__int16, ulGlobalMode, 0x01934BE0);

DataRef(__int16, ssGameModeChange, 0x01A558A4);

DataRef(sint16, ssStageNumber, 0x01934B70);
DataRef(uint8, ssActNumber, 0x0174AFE3);

DataRef(sint8, Language, 0x174AFD1);
DataRef(sint8, Speech, 0x0174AFD2);

DataRef(sint8, ucPauseSelect, 0x01933EB1);

DataRef(sint8, pause_flg, 0x174AFD7);

void RestartStageWithFadeOut();

bool32 ChkPause();

/*
ssLastActNumber
ssNextActNumber
ssEntranceNumber
ssNumKilledPlayer
ssPauseSelect
ssPauseEnable
sprite_task_buffer
pReturnPositionAngle
palloop
RoundMasterList
BackColorList
ScrollMasterList
JAPANESE
starteventtable
cleareventtable
paSonicIP
paMilesIP
paKnucklesIP
paBigIP
paAmyIP
paE102IP
nextTrialBossSonic
nextTrialBossMiles
nextTrialBossKnuckles
nextTrialBossAmy
nextTrialBossE102
nextTrialBossBig
paSonicRP
paMilesRP
paKnucklesRP
paAmyRP
paBigRP
paE102RP
paRPTable
nextadvSonic
nextadvMiles
nextadvKnuckles
nextadvAmy
nextadvE102
nextadvBig
nextadv_table
D3DLIGHT9
PauseEnable
PauseDisable
GM_WaitEvent
GM_WaitEventS
GM_CheckStartEvent
GM_WaitEventEDestruct
GM_WaitEventE
GM_CheckClearEvent
GM_CheckMode
InitGame
SetChangeGameMode
InitGameWorks
GameLoop
GameLoop_with_SyoriOchiTaisaku
ActionEnd
EndStage
GM_SEControle
GM_SECall
GM_BGM_Play
WaitLandPlayer
SetRoundMaster
SetScrollTask
SetPlayerNumberForGame
SetPlayerNumber
GetPlayerNumber
GetCountKilledPlayer
SetNextStageNumberForReturn
SetStageNumber
SetNextStageNumber
ChangeStageWithFadeOut
RestartStageWithFadeOut
GetStageNumber
GetLastStageNumber
GetNextStageNumber
NP_ChkStageChaoGarden
AdvanceActLocal
SetEntranceNumber
GetEntranceNumber
SetPlayerInitialPosition
GM_SetNextAdventureStage
SetNextTrialStage
ChkPause
ChkGameMode
GameQuitYesNo
isMissionClearDisp
StartTheFirstGame
GoNextAction
GoNextAdventure
InitializeStage
PauseLoop
SetFinishAction
SetPlayer
AdvanceAct
IsNeedForcePause
GameInit
MissionInit
Mission
Action
Adventure
*/