/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_emotion.h'
* 
*   Description:
*     Chao emotion parameters header.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_CHAO_EMOTION
#define H_SA2B_CHAO_EMOTION

/************************/
/*  Opaque Types        */
/************************/
/****** Task ************************************************************************/
typedef struct task             task;

/****** Chao ************************************************************************/
typedef struct chao_param_gc    CHAO_PARAM_GC;

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Get Emotion Number **********************************************************/
/*
*   Description:
*     Get individual emotion number from master enum for interfacing directly with
*   Emotion data arrays.
*
*   Parameters:
*     - num         : master enum value
*
*   Returns:
*     Individual emotion number.
*/
#define GET_EM_MD(num)          ((num) - EM_MD_PLEASURE)
#define GET_EM_ST(num)          ((num) - EM_ST_SLEEPY)
#define GET_EM_PER(num)         ((num) - EM_PER_CURIOSITY)

/****** Emotion Number **************************************************************/
enum
{
    /****** Emotion Mood ********************************************************/
    /*
    *   Range: (0~200)
    */
    EM_MD_PLEASURE,                 /* pleasure                                 */
    EM_MD_ANGER,                    /* anger                                    */
    EM_MD_SORROW,                   /* sorrow                                   */
    EM_MD_FEAR,                     /* fear                                     */
    EM_MD_SURPRISE,                 /* surpise                                  */
    EM_MD_PAIN,                     /* pain                                     */
    EM_MD_RELAX,                    /* relax                                    */
    EM_MD_TOTAL,                    /* total                                    */

    /****** Emotion State *******************************************************/
    /*
    *   Range: (0~10'000)
    */
    EM_ST_SLEEPY,                   /* sleepy                                   */
    EM_ST_SLEEP_DEPTH,              /* sleep depth                              */
    EM_ST_HUNGER,                   /* hunger                                   */
    EM_ST_BREED,                    /* breed                                    */
    EM_ST_TEDIOUS,                  /* tedius                                   */
    EM_ST_LONELY,                   /* lonely                                   */
    EM_ST_TIRE,                     /* tire                                     */
    EM_ST_STRESS,                   /* stress                                   */
    EM_ST_NOURISHMENT,              /* nourishment                              */
    EM_ST_CONDITION,                /* condition                                */
    EM_ST_THIRSTY,                  /* thirsty                                  */

    /****** Emotion Personality *************************************************/
    /*
    *   Range: (-100~100)
    */
    EM_PER_CURIOSITY,               /* curiosity                                */
    EM_PER_KINDNESS,                /* kindness                                 */
    EM_PER_AGRESSIVE,               /* agressive/energetic                      */
    EM_PER_SLEEPY_HEAD,             /* sleepy head                              */
    EM_PER_SOLITUDE,                /* solitude                                 */
    EM_PER_VITALITY,                /* vitality                                 */
    EM_PER_GLUTTON,                 /* glutton                                  */
    EM_PER_REGAIN,                  /* regain                                   */
    EM_PER_SKILLFUL,                /* skillful                                 */
    EM_PER_CHARM,                   /* charm                                    */
    EM_PER_CHATTY,                  /* chatty                                   */
    EM_PER_CALM,                    /* calm/carefree                            */
    EM_PER_FICKLE,                  /* fickle                                   */

    /****** Number Emotion ******************************************************/
    NB_EMOTION,                     /* enum count                               */
};

/************************/
/*  Prototypes          */
/************************/
/****** Emotion Add *****************************************************************/
/*
*   Description:
*     Add to an emotion valuie of a Chao via a Task.
*
*   Parameters:
*     - tp          : chao task pointer
*     - EmotionNum  : emotion enum value
*     - add         : value to add, result will be clamped to ranges defined in enum
*/
void    AL_EmotionAdd( task* tp, u32 EmotionNum, s32 add );

/****** Emotion Set *****************************************************************/
/*
*   Description:
*     Set an emotion value of a Chao via a Task.
*
*   Parameters:
*     - tp          : chao task pointer
*     - EmotionNum  : emotion enum value
*     - value       : value to set, will be clamped to ranges defined in enum
*/
void    AL_EmotionSetValue( task* tp, u32 EmotionNum, s32 value );

/****** Emotion Get *****************************************************************/
/*
*   Description:
*     Get an emotion value from a Chao via a Task.
*
*   Parameters:
*     - tp          : chao task pointer
*     - EmotionNum  : emotion enum value
*
*   Returns:
*     The given emotion value of the Chao; or, '-1' if 'EmotionNum' is invalid.
*/
s32     AL_EmotionGetValue( const task* tp, u32 EmotionNum );
/*
*   Description:
*     Get an emotion value from a Chao via a Chao param.
*
*   Parameters:
*     - pParam      : chao param pointer
*     - EmotionNum  : emotion enum value
*
*   Returns:
*     The given emotion value of the Chao; or, '-1' if 'EmotionNum' is invalid.
*/
s32     AL_EmotionGetValue2( const CHAO_PARAM_GC* pParam, u32 EmotionNum );

EXTERN_END

#endif/*H_SA2B_CHAO_EMOTION*/
