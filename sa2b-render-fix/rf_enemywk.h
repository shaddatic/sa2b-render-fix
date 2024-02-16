/*
*   SA2 Render Fix - '/rf_enemywk.h'
*
*   Description:
*       Contains working version of the ENEMYWK struct while it's
*   not included in SAMT.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_ENEMYWK_H_
#define _RF_ENEMYWK_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task/motionwk.h>
#include <sa2b/src/shadow.h>

/************************/
/*  Structures           */
/************************/
typedef struct
{
    NJS_POINT3 pos;
    XSSUNIT hit[6];
}
xyyzzxsdwstr;

typedef struct 
{
    NJS_MOTION* mtnp;
    int16_t unks;
    char startMaybe;
    char unk;
    float mtnStep;
    float mtnAlsoStep;
}
ENEMY_MTN_UNK;

typedef struct 
{
    float nframe;
    float pframe;
    float lframe;
    float link_ratio;
    char unkc_type;
    char flag;
    char unkc_index;
    char unkc_unk3;
    char unkc_unk4;
    char unkc_unk5;
    int16_t unks;
    ENEMY_MTN_UNK* pMtnUnk;
    NJS_CNK_OBJECT* pObject;
    NJS_MOTION_LINK MotionLink;
}
ENEMY_MTN;

#define GET_ENEMYWK(_tp)    ((ENEMYWK*)tp->mwp)

typedef struct enemywk
{
    MOTIONWK();

    int unk3;
    char byte44;
    char byte45;
    char field_46;
    char field_47;
    __int16 field_48;
    __int16 field_4A;
    uint16_t flag;
    char f4E[6];
    float float54;
    NJS_POINT3 home;
    NJS_POINT3 vec0;
    char f64[24];
    NJS_VECTOR lightPos;
    float flt1;
    float field_98;
    float field_9C;
    NJS_VECTOR norm;
    NJS_ARGB argb;
    NJS_POINT3 colli_center;
    float colli_top;
    float colli_radius;
    float colli_bottom;
    float cliff_height;
    float bound_side;
    float bound_floor;
    float bound_friction;
    float bound_ceiling;
    int bound_add_angle;
    float shadow_scl;
    float shadow_scl_ratio;
    xyyzzxsdwstr shadow;
    float buyoscale;
    int angx_spd;
    int angy_spd;
    char f1CC[8];
    int view_angle;
    float view_range;
    float hear_range;
    ENEMY_MTN enemy_mtn;
}
ENEMYWK;

#endif/*_RF_ENEMYWK_H_*/
