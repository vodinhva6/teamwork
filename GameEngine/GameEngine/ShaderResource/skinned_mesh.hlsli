#include "lights.hlsli"
struct VS_IN
{
    float4 position : POSITION;
    float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float2 texcoord : TEXCOORD;
    float4 bone_weights : WEIGHTS;
    uint4 bone_indices : BONES;
};
struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 world_position : POSITION;
    float4 world_normal : NORMAL;
    float4 world_tangent : TANGENT;
    float2 texcoord : TEXCOORD;
    float4 color : COLOR;
    float3 shadow_texcoord : TEXCOORD1;
};
static const int MAX_BONES = 256;
cbuffer OBJECT_CONSTANT_BUFFER : register(b0)
{
    row_major float4x4 world;
    float4 material_color;
    row_major float4x4 bone_transforms[MAX_BONES];
};
cbuffer SCENE_CONSTANT_BUFFER : register(b1)
{
    row_major float4x4 view_projection;
    float4 camera_position;
};

cbuffer COLOR_FILTER : register(b2)
{
    float hueShift;  
    float saturation;
    float brightness;
    float dummy;
};
cbuffer SHADOW_CONSTANT_BUFFER : register(b3)
{
    row_major float4x4 shadowmap_view_projection;
    float bias;
    float3 dummyShadow;
};

cbuffer LIGHT_CONSTANT_BUFFER : register(b4)
{
    float4 light_direction;
    float4 light_color;
    
    PointLights point_lights[20];
    SpotLights	spot_lights[20];
    int pointLightsUsingAt;
    int spotLightsUsingAt;
    float2 dummyLights;
}
cbuffer TEXTURE_CUSTOM_CONSTANT_BUFFER : register(b5)
{
    float2 scroll_direction;
    float timer;
    float scroll_dummy;
}
cbuffer FOG_CONSTANT_BUFFER : register(b6)
{
    float4 fogRange;
    float4 fogColor;
}

#include "ColorFilterFunctions.hlsli"
#include "ShadingFunctions.hlsli"