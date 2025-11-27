/********************************/
/*  Constant Registers          */
/********************************/
/****** Floats **********************************************************************************/
float4 c_ScreenInfo         : register(c201); /* 1/w_res, 1/h_res, X, X                         */

/****** Matrix **********************************************************************************/
float4x4 c_MtxProjection    : register(c8);   /* projection matrix                              */

/********************************/
/*  Structures                  */
/********************************/
/****** Vertex Input ****************************************************************************/
struct VS_IN
{
    float3 pos              : POSITION;     /* vertex postion                                   */
};

/****** Vertex Output ***************************************************************************/
struct VS_OUT
{
    float4 pos              : SV_POSITION;  /* vertex postion                                   */

#ifdef MOD_FOG
    float  w                : TEXCOORD0;    /* vertex w component                               */
#endif/*MOD_FOG*/
};

/********************************/
/*  Source                      */
/********************************/
/****** Main ************************************************************************************/
VS_OUT
main(VS_IN inpt)
{
    VS_OUT outp;

    outp.pos = mul(float4(inpt.pos, 1.0f), c_MtxProjection);
    
#ifdef MOD_FOG
    outp.w   = outp.pos.w;
#endif/*MOD_FOG*/

    // DirectX 9 pixel offset issue
    outp.pos.x -= ( c_ScreenInfo.x * outp.pos.w );
    outp.pos.y += ( c_ScreenInfo.y * outp.pos.w );

    return outp;
}
