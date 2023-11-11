/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_face.h'
*
*   Contains functions and enums related to Chao face states.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
}
eAL_EYE_NUM;

typedef enum
{
    AL_MOUTH_NUM_NONE = 0x0,
    AL_MOUTH_NUM_SHARK = 0x1,    // "TOOTHY GRIN"
    AL_MOUTH_NUM_HOYO = 0x2,    // "OPEN"
    AL_MOUTH_NUM_NIKO = 0x3,    // "V SMILE"
    AL_MOUTH_NUM_MUSU = 0x4,    // "V FROWN"
    AL_MOUTH_NUM_WAAI = 0x5,    // "OPEN SMILE"
    AL_MOUTH_NUM_UEEN = 0x6,    // "OPEN FROWN"
    AL_MOUTH_NUM_NEE = 0x7,
    AL_MOUTH_NUM_KOIKE = 0x8,    // "SQUIGGLE"
    AL_MOUTH_NUM_GEE = 0x9,        // "TOOTHY FROWN"
    AL_MOUTH_NUM_MUU = 0xA,
    AL_MOUTH_NUM_UWAAN = 0xB,    // "WIDE OPEN"
    AL_MOUTH_NUM_INO = 0xC,
    AL_MOUTH_NUM_END = 0xD,
}
eAL_MOUTH_NUM;

/************************/
/*  Data                */
/************************/
#define AL_EyeTexIdList         DataAry(sint16, 0x008A7A70, [14])
#define EyeColorTexIdList       DataAry(sint16, 0x008A7AC0, [12])

#define AL_MouthTexIdList       DataAry(sint16, 0x008A7A8C, [13][2])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set eye for number of frames **/
void    AL_FaceSetEye(TASK* tp, eAL_EYE_NUM EyeNum, sint32 timer);
/** Change eye perminantly **/
void    AL_FaceChangeEye(TASK* tp, eAL_EYE_NUM EyeNum);
/** Return eye to Chao's default **/
void    AL_FaceReturnDefaultEye(TASK* tp);

/** Set mouth for number of frames **/
void    AL_FaceSetMouth(TASK* tp, eAL_MOUTH_NUM MouthNum, sint32 timer);
/** Change mouth perminantly **/
void    AL_FaceChangeMouth(TASK* tp, eAL_MOUTH_NUM MouthNum);
/** Return mouth to Chao's default **/
void    AL_FaceReturnDefaultMouth(TASK* tp);

/** Internal functions **/
void    AL_FaceEyeLidControl(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_FaceEyeLidControl_p      FuncPtr(void, __cdecl, (TASK*), 0x0053A1E0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_FACE_H_ */