/*
*   Sonic Adventure Mod Tools (SA2B) - '/ninja/ninja.h'
*
*   Ninja is the rendering API used for both adventure games
*
*   Contributors:
*   -   SEGA,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef    _NJNJA_H_
#define    _NJNJA_H_

EXTERN_START

#include <sa2b/ninja/njcommon.h>

#include <sa2b/ninja/njsystem.h>
#include <sa2b/ninja/njmath.h>

#include <sa2b/ninja/njchunk.h>

#include <sa2b/ninja/njmatrix.h>
#include <sa2b/ninja/njcamera.h>
#include <sa2b/ninja/njLight.h>
#include <sa2b/ninja/njmotion.h>
#include <sa2b/ninja/njtexture.h>
#include <sa2b/ninja/njdraw.h>
#include <sa2b/ninja/njeffect.h>
#include <sa2b/ninja/njcollision.h>

#include <sa2b/ninja/njparticle.h>

#include <sa2b/ninja/njdebug.h>

#include <sa2b/ninja/njbasic.h>
#include <sa2b/ninja/ginja.h>

EXTERN_END

#include <sa2b/extern/stdlib.h>

/** ANY_OBJECT is SAMT specific, and is to be used when 
    a pointer can represent more than one Object type **/
typedef union anyobj
{
    void* ptr;              /* raw pointer */
    NJS_OBJECT* obj;        /* basic object */
    NJS_CNK_OBJECT* cnk;    /* chunk object */
    GJS_OBJECT* gjs;        /* ginja object */
}
ANY_OBJECT;

#endif /* _NJNJA_H_ */
