/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/njlight.h'
*
*   Contains structs and defines for Ninja lights
*
*   Contributors:
*     - SEGA,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _NINJA_LIGHT_H_
#define _NINJA_LIGHT_H_

/* light on light off */
#define NJD_LIGHT_OFF   (0)
#define NJD_LIGHT_ON    (1)

/* Light Motion type */
#define NJD_LTYPE_POINT         1        /* point light */
#define NJD_LTYPE_VECTOR        2        /* parallel light */
#define NJD_LTYPE_AMBIENT       3        /* ambient light */

/* draw model function */
#define NJD_MFUNC_UNDEFINE      0
#define NJD_MFUNC_EASY          1
#define NJD_MFUNC_SIMPLE        2
#define NJD_MFUNC_EASY_MULTI    3
#define NJD_MFUNC_SIMPLE_MULTI  4

typedef struct {
    Float       x, y, z;
    Float       r, g, b;
    Float       f1, f2;
    Sint32      func;
    Uint32      type;
}NJS_LIGHT;

#endif
