/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4 c_FogParam           : register(c50);  /* mode, near, far, X                             */
float4 c_FogColor           : register(c51);  /* r, g, b, a                                     */
float4 c_ColShadow          : register(c202); /* shadow color + shadow tex                      */

/********************************/
/*  Constant Registers          */
/********************************/
/****** Pixel Input *****************************************************************************/
struct PS_IN
{
    float4 pos              : SV_POSITION;  /* vertex postion                                   */
    
#ifdef MOD_FOG
    float  w                : TEXCOORD0;    /* vertex w component                               */
#endif/*MOD_FOG*/
};

/****** Pixel Output ****************************************************************************/
struct PS_OUT
{
    half4 col               : COLOR;        /* vertex postion                                   */
};

/********************************/
/*  Source                      */
/********************************/
/****** Main ************************************************************************************/
PS_OUT main(PS_IN inpt)
{
    PS_OUT outp;

    outp.col = c_ColShadow;

    return outp;
}
