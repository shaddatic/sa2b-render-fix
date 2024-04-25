/*
*   Sonic Adventure Mod Tools (SA2B) - '/magic/math.h'
*
*   Description:
*       Magic's MATH namespace.
*
*   Contributors:
*     - Magic Developers
*     - kellnc
*     - MainMemory
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _MAGIC_MATH_H_
#define _MAGIC_MATH_H_

#ifdef  __cplusplus

/************************/
/*  Math                */
/************************/
namespace Magic::MATH
{
    template <typename T>
    struct Vector4
    {
        T x;
        T y;
        T z;
        T w;
    };

    template <typename T>
    struct Vector3
    {
        T x;
        T y;
        T z;
    };

    template <typename T>
    struct Matrix4
    {
        union
        {
            T m[4][4];
            T m2[16];
        };
    };
}

#endif/*__cplusplus*/

#endif/*_MAGIC_MATH_H_*/
