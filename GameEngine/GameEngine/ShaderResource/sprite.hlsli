#include "ColorFilterFunctions.hlsli"
struct VS_OUT
{
   float4 position : SV_POSITION;
   float4 color : COLOR;
   float2 texcoord : TEXCOORD;
};
cbuffer COLOR_FILTER : register(b2)
{
    float hueShift;
    float saturation;
    float brightness;
    float dummy;
};
cbuffer TEXTURE_CUSTOM_CONSTANT_BUFFER : register(b5)
{
    float2 scroll;
    float timer;
    float scroll_dummy;
}