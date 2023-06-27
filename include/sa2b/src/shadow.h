#pragma once

struct shadowwk
{
    Angle angx;
    Angle angz;
    unsigned int Attr_top;
    unsigned int Attr_bottom;
    float y_top;
    float y_bottom;
    unsigned int _Attr_top;
    unsigned int _Attr_bottom;
    float scl;
};

struct xssunit
{
    int findflag;
    int objatt;
    int angx;
    int angz;
    float onpos;
    NJS_POINT3 normal;
};

struct zxsdwstr
{
    NJS_POINT3 pos;
    xssunit lower;
    xssunit upper;
};

FuncPtr(float32, __cdecl, GetShadowPos, (float x, float y, float z, Angle3* ang), 0x00494C30); // Calculate Falloff Position

FuncPtr(void, __cdecl, GetCharacterShadowInfo, (NJS_VECTOR* position, shadowwk* swk), 0x494DF0);

inline float32 GetShadowPosEx(NJS_POINT3* pPos) // non standard
{
    Angle3 ang;
    return GetShadowPos(pPos->x, pPos->y, pPos->z, &ang);
}

inline float32 GetShadowPosEx(NJS_POINT3* pPos, Angle3* ang) // non standard
{
    return GetShadowPos(pPos->x, pPos->y, pPos->z, ang);
}