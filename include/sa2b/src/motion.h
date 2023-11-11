/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/motion.h'
*
*   Contains structs and functions related to object motion data
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_MOTION_H_
#define _SA2B_MOTION_H_

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    short mode;
    uint8 UNDEF0;
    uint8 UNDEF1;
    float frame;
    float start;
    float end;
    float spd;
    void* pMotion;
}
MOTION_INFO;

typedef struct 
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
}
MOTION_CTRL;

typedef struct 
{
    void* pMotion;
    short mode;
    short posture;
    int next;
    int link_step;
    float start;
    float end;
    float spd;
}
MOTION_TABLE;

/************************/
/*  Functions            */
/************************/
EXTERN_START
void    SetMotionLink(MOTION_CTRL* pMtnCtrl, sint32 MtnNum);
void    SetMotionLinkStep(MOTION_CTRL* pMtnCtrl, sint32 MtnNum, uint16 step);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** User-Function ptrs **/
EXTERN const void* SetMotionLink_p;
EXTERN const void* SetMotionLinkStep_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_MOTION_H_ */
