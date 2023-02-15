
struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

cbuffer TEXTURE_CUSTOM_CONSTANT_BUFFER : register(b5)
{
    float2 scroll_direction;
    float timer;
    float scroll_dummy;
    float2 positionOfFadeOut;
    float2 sizeOfFadeOut;
}

cbuffer BLUR_CONSTANT_BUFFER : register(b7)
{
    float3 extraction_color;
    int gaussian_half_kernel_size_t;
    float gaussian_sigma;
    float bloom_intensity;
    float2 dummy;
}