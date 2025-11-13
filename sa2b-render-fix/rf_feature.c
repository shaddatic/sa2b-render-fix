/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Game ************************************************************************************/
#include <samt/sonic/player.h>      /* player                                                   */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rfu_file.h>               /* replace player prs                                       */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** Self ************************************************************************************/
#include <rf_feature.h>             /* self                                                     */

/********************************/
/*  Data                        */
/********************************/
/****** Settings ********************************************************************************/
static int  CheapShadowMode;
static bool CheapShadowPlayer;
static bool Chaos0TexAnim;
static bool DreamcastPlayerModels[NB_PLNO];
static bool DisablePlayerShadowing;

/********************************/
/*  Source                      */
/********************************/
/****** Feature *********************************************************************************/
bool
RFF_BackColorDraw(void)
{
    return true;
}

bool
RFF_SpotLightFix(void)
{
    return true;
}

bool
RFF_BackFaceCulling(void)
{
    return true;
}

bool
RFF_CheapShadow(void)
{
    return CheapShadowMode != CNFE_GLOBAL_CHSMD_DISABLED;
}

bool
RFF_CheapShadowPerformance(void)
{
    return CheapShadowMode == CNFE_GLOBAL_CHSMD_PERFORMANCE;
}

bool
RFF_CheapShadowPlayer(void)
{
    return CheapShadowPlayer;
}

f32
RFF_ShadowOpacityGlobal(void)
{
    return 0.6875f;
}

f32
RFF_ShadowOpacityChao(void)
{
    return 0.55078125f;
}

bool
RFF_NewEventRenderer(void)
{
    return true;
}

bool
RFF_Chaos0TexAnim(void)
{
    return Chaos0TexAnim;
}

bool
RFF_DreamcastPlayerModel(int pno)
{
    if (pno < 0 || pno >= NB_PLNO)
        return false;

    return DreamcastPlayerModels[pno];
}

bool
RFF_DisablePlayerShadowing(void)
{
    return DisablePlayerShadowing;
}

/****** SAMT ************************************************************************************/
void
RFF_Init(void)
{
    CheapShadowPlayer = ( CNF_GetInt(CNF_PLAYER_SHADOWMD) == CNFE_PLAYER_SHADOWMD_MODIFIER );
    CheapShadowMode   = CNF_GetInt(CNF_GLOBAL_CHSMD);

    Chaos0TexAnim     = ( CNF_GetInt(CNF_PLAYER_CHAOS0ANIM) == CNFE_BOOL_ENABLED );

    DisablePlayerShadowing = ( CNF_GetInt( CNF_PLAYER_MDLSHADOW ) == CNFE_BOOL_DISABLED );

    DreamcastPlayerModels[PLNO_SONIC]        = RFU_ReplacePlayerPrs("SONICMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_SHADOW]       = RFU_ReplacePlayerPrs("TERIOSMDL"    , nullptr);
    DreamcastPlayerModels[PLNO_MILES]        = RFU_ReplacePlayerPrs("MILESMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_EGGMAN]       = RFU_ReplacePlayerPrs("EGGMDL"       , nullptr);
    DreamcastPlayerModels[PLNO_KNUCKLES]     = RFU_ReplacePlayerPrs("KNUCKMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_ROUGE]        = RFU_ReplacePlayerPrs("ROUGEMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_TAILS_WALKER] = RFU_ReplacePlayerPrs("TWALKMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_EGG_WALKER]   = RFU_ReplacePlayerPrs("EWALKMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_AMY]          = RFU_ReplacePlayerPrs("AMYMDL"       , nullptr);
    DreamcastPlayerModels[PLNO_SUPER_SONIC]  = RFU_ReplacePlayerPrs("SSONICMDL"    , nullptr);
    DreamcastPlayerModels[PLNO_SUPER_SHADOW] = RFU_ReplacePlayerPrs("SSHADOWMDL"   , nullptr);
    DreamcastPlayerModels[PLNO_METAL_SONIC]  = RFU_ReplacePlayerPrs("METALSONICMDL", nullptr);
    DreamcastPlayerModels[PLNO_CHAO_WALKER]  = RFU_ReplacePlayerPrs("CWALKMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_TICAL]        = RFU_ReplacePlayerPrs("TICALMDL"     , nullptr);
    DreamcastPlayerModels[PLNO_CHAOS0]       = RFU_ReplacePlayerPrs("CHAOS0MDL"    , nullptr);
}
