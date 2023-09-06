/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/game.h'
*
*   ~~ Under Construction ~~
*   Contains data and functions related to core game elements
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Enums               */
/************************/
enum /* ulGlobalMode */
{
    MD_ACTION_INIT = 0x04,
    MD_ACTION,
    MD_MOVIE_INIT = 0x07,
    MD_MOVIE,
    MD_ADVERTISE_INIT = 0xD,
    MD_ADVERTISE,
    MD_ENDING = 0x10,
    MD_EGET_INIT = 0x11,
    MD_EGET,
    MD_MCWARN_INIT = 0x18,
    MD_MCWARN,
    NUM_MODE,
};

/*
    MD_START = 0x0,
    MD_LOGO = 0x1,
    MD_TITLE = 0x2,
    MD_SELECTPLAYER = 0x3,
    MD_ACTION = 0x4,
    MD_ADVENTURE = 0x5,
    MD_CONTINUE = 0x6,
    MD_END = 0x7,
    MD_MOVIE = 0x8,
    MD_TRIAL = 0x9,
    MD_MISSION = 0xA,
    MD_TITLE2_INIT = 0xB,
    MD_TITLE2 = 0xC,
    MD_NOVMSWND_INIT = 0xD,
    MD_NOVMSWND = 0xE,
    MD_CHARA_SELECT_INIT = 0xF,
    MD_CHARA_SELECT = 0x10,
    MD_SUMMARY_INIT = 0x11,
    MD_SUMMARY = 0x12,
    MD_TUTORIAL_INIT = 0x13,
    MD_TUTORIAL = 0x14,
    MD_STAFFROLL_INIT = 0x15,
    MD_STAFFROLL = 0x16,
    MD_TVSETTING_END = 0x17,
    MD_LOGO_INIT = 0x18,
    NUM_MODE = 0x19,
*/

enum /* ssGameMode */
{
    MD_GAME_INIT,
    MD_GAME_FADEIN = 0x07,
    MD_GAME_FADEOUT_CLEAR = 0x08,
    MD_GAME_FADEOUT_MISS,
    MD_GAME_FADEOUT_RESTART = 0x0D,
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

enum
{
	JAPANESE,
	ENGLISH,
	GERMAN,
	FRENCH,
	SPANISH,
	ITALIAN,
	NUM_LANGUAGE,
};

/************************/
/*  Data                */
/************************/
DataRef(uint32, ulGlobalMode, 0x0174B040);

DataRef(sint16, ssGameMode, 0x01934BE0);

DataRef(sint16, ssGameModeChange, 0x01A558A4);

DataRef(sint16, ssStageNumber, 0x01934B70);
DataRef(uint8, ssActNumber, 0x0174AFE3);

DataRef(sint8, Language, 0x174AFD1);
DataRef(sint8, Speech, 0x0174AFD2);

DataRef(sint8, ucPauseSelect, 0x01933EB1);

DataRef(sint8, pause_flg, 0x174AFD7);

/************************/
/*  Functions           */
/************************/
void    RestartStageWithFadeOut();

bool32  ChkPause();

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