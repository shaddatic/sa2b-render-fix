/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_face.h'
*
*   Description:
*       Contains functions and enums related to Chao face
*   states.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_FACE_H_
#define _SA2B_CHAO_FACE_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task TASK;

/************************/
/*  Enums               */
/************************/
typedef enum
{
    AL_EYE_TEXID_NORMAL,
    AL_EYE_TEXID_KYA,
    AL_EYE_TEXID_NAMU,
    AL_EYE_TEXID_TOHOHO,
    AL_EYE_TEXID_NIKO,
    AL_EYE_TEXID_BIKKURI,
    AL_EYE_TEXID_GURUGURU,
    AL_EYE_TEXID_SUYASUYA,
    AL_EYE_TEXID_DARK,
    AL_EYE_TEXID_HERO,
    AL_EYE_TEXID_NCHAOS,
    AL_EYE_TEXID_HCHAOS,
    AL_EYE_TEXID_DCHAOS,
}
eAL_EYE_TEXNUM;

typedef enum
{
    AL_EYE_COLOR_NEUT,
    AL_EYE_COLOR_HERO,
    AL_EYE_COLOR_DARK,
    AL_EYE_COLOR_N_CHAOS,
    AL_EYE_COLOR_H_CHAOS,
    AL_EYE_COLOR_D_CHAOS,
    AL_EYE_COLOR_BLUE,
    AL_EYE_COLOR_GREEN,
    AL_EYE_COLOR_RED,
}
eAL_EYE_COLOR;

typedef enum
{
    AL_EYE_NUM_NORMAL,
    AL_EYE_NUM_KYA,
    AL_EYE_NUM_NAMU,
    AL_EYE_NUM_TOHOHO,
    AL_EYE_NUM_NIKO,
    AL_EYE_NUM_BIKKURI,
    AL_EYE_NUM_GURUGURU,
    AL_EYE_NUM_SUYASUYA,
    AL_EYE_NUM_SHIROME,
    AL_EYE_NUM_TRON,
    AL_EYE_NUM_ANGER,
    AL_EYE_NUM_NCHAOS,
    AL_EYE_NUM_HCHAOS,
    AL_EYE_NUM_DCHAOS,
    AL_EYE_NUM_END,
}
eAL_EYE_NUM;

typedef enum
{
    AL_MOUTH_NUM_NONE,
    AL_MOUTH_NUM_SHARK,
    AL_MOUTH_NUM_HOYO,
    AL_MOUTH_NUM_NIKO,
    AL_MOUTH_NUM_MUSU,
    AL_MOUTH_NUM_WAAI,
    AL_MOUTH_NUM_UEEN,
    AL_MOUTH_NUM_NEE,
    AL_MOUTH_NUM_KOIKE,
    AL_MOUTH_NUM_GEE,
    AL_MOUTH_NUM_MUU,
    AL_MOUTH_NUM_UWAAN,
    AL_MOUTH_NUM_INO,
    AL_MOUTH_NUM_END,
}
eAL_MOUTH_NUM;

/************************/
/*  Data                */
/************************/
#define AL_EyeTexIdList         DATA_ARY(int16_t, 0x008A7A70, [14])
#define EyeColorTexIdList       DATA_ARY(int16_t, 0x008A7AC0, [12])

#define AL_MouthTexIdList       DATA_ARY(int16_t, 0x008A7A8C, [13][2])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set eye for number of frames **/
void    AL_FaceSetEye(TASK* tp, eAL_EYE_NUM EyeNum, int32_t timer);
/** Change eye permanently **/
void    AL_FaceChangeEye(TASK* tp, eAL_EYE_NUM EyeNum);
/** Return eye to Chao's default **/
void    AL_FaceReturnDefaultEye(TASK* tp);

/** Set mouth for number of frames **/
void    AL_FaceSetMouth(TASK* tp, eAL_MOUTH_NUM MouthNum, int32_t timer);
/** Change mouth permanently **/
void    AL_FaceChangeMouth(TASK* tp, eAL_MOUTH_NUM MouthNum);
/** Return mouth to Chao's default **/
void    AL_FaceReturnDefaultMouth(TASK* tp);

/** Internal functions **/
void    AL_FaceEyeLidControl(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_FaceEyeLidControl_p       FUNC_PTR(void, __cdecl, (TASK*), 0x0053A1E0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_FACE_H_*/
