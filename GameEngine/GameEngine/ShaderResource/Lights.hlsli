struct PointLights
{
    float4 position;
    float4 color;
    float range;
    float power;
    float2 dummy;
};
struct SpotLights
{
    float4 position;
    float4 direction;
    float4 color;
    float range;
    float power;
    float innerCorn;
    float outerCorn;
};