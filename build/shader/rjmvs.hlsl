/********************************/
/*  Constant Registers          */
/********************************/
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

    return outp;
}
