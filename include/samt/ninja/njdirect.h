/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njdirect.h'
*
*   Description:
*     Structures for Ninja's Direct draw.
*/
#ifndef H_NJ_DIRECT
#define H_NJ_DIRECT

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Direct Head *****************************************************************************/
typedef struct
{
    Float       x,y,z;              /* position                                                 */
    Float       r;                  /* radius                                                   */
    void*       next;               /* next pointer                                             */
    Uint32      nOP;                /* opaque polygon material count                            */
    Uint32      nTR;                /* transparent polygon material count                       */
    Uint32      mode;               /* direct mode                       [0: normals, 1: color] */
}
NJS_DIRECT_HEAD;

/****** Direct Light ****************************************************************************/
typedef struct
{
    Float	x,y,z;                  /* light vector                                             */
    Float	inten;                  /* intensity                                                */
    Float   ambient;                /* ambient                                                  */
    Float	r,g,b;                  /* color                                                    */
}
NJS_DIRECT_COMPILE_LIGHT;

EXTERN_END

#endif/*H_NJ_DIRECT*/
