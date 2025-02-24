/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/magic/math.h'
*
*   Description:
*       Magic's MATH namespace.
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
