/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/memutil.h>   /* WriteData, WriteJump, WritePointer                   */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_mod.h>             /* RFMOD_SetAlpha                                   */

/****** Self ************************************************************************/
#include <rf_ninja.h>           /* self                                             */

/************************/
/*  Constants           */
/************************/
/****** DrawTextureEx ***************************************************************/
#define TexExCount          DataRef(int32_t, 0x0077F6BF)

/****** DrawPolygon2D ***************************************************************/
#define Poly2DN             DataRef(int32_t, 0x00490FA8)

/************************/
/*  Source              */
/************************/
void
rjDrawTextureEx(NJS_TEXTURE_VTX* polygon, Int count, Int trans)
{
    TexExCount = count;
    njDrawTextureEx(polygon, 4, trans);
    TexExCount = 4;
}

void
rjDrawPolygon2D(NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr)
{
    Poly2DN = n;
    njDrawPolygon2D(p, 4, pri, attr);
    Poly2DN = 4;
}

void
rjSetCheapShadowMode(int32_t mode)
{
    if (mode < 0)
    {
        RFMOD_SetAlpha(0.0f);
        return;
    }
    else if (mode > 255)
        mode = 255;

    RFMOD_SetAlphaI(255 - mode);
}

/****** Init ************************************************************************/
void
RF_NinjaInit(void)
{
    /** Allow 'count' argument to be writeable **/
    WriteData(&TexExCount, 4, int32_t);

    /** Allow 'n' argument to be writeable **/
    WriteData(&Poly2DN, 4, int32_t);
}
