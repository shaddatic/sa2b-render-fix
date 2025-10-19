/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4 c_FogParam           : register(c50);  /* mode, near, far, X                             */
float4 c_FogColor           : register(c51);  /* r, g, b, a                                     */
float4 c_ColShadow          : register(c200); /* shadow color + shadow tex                      */

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
/****** Fog Calcs *******************************************************************************/
#ifdef MOD_FOG

float
GetFogIntensity(const float w)
{
    const float fogDensity = 8;
    
    const float fog_mode = c_FogParam.x;
    const float fog_near = c_FogParam.y;
    const float fog_far = c_FogParam.z;

    float fog = (w - fog_near) / (fog_far - fog_near);
    
    float exp2fog = exp2(-fogDensity * fog * fog);
    float expfog = exp2(-fogDensity * fog);

    if (fog_mode > 4.5)
    {
        fog = saturate(1.0f - exp2fog);
    }
    else if (fog_mode > 2.5)
    {
        fog = saturate(1.0f - expfog);
    }

    return saturate(fog);
}

#endif/*MOD_FOG*/

/****** Main ************************************************************************************/
PS_OUT
main(PS_IN inpt)
{
    PS_OUT outp;

    outp.col = c_ColShadow;
    
#ifdef MOD_FOG
    
    const float fog_inten = GetFogIntensity(inpt.w);

    outp.col.rgb = lerp(outp.col.rgb, c_FogColor.rgb, fog_inten);

#endif/*MOD_FOG*/

    return outp;
}
