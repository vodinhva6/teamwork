#pragma once
#include "ConstantBuffer.h"


#define MAX_SUPP_LIGHTS 20
class LightBuffer : public ConstantBuffer
{
public:
    void CreateBuffer(ID3D11Device* device) override;
    void UpdateBuffer(ID3D11DeviceContext* dcContext) override;
    ~LightBuffer() override {}
private:
    struct PointLightsConstant
    {
        DirectX::XMFLOAT4 position{ 0,0,0,0 };
        DirectX::XMFLOAT4 color{ 1,1,1,1 };
        float range{ 0 };
        float power{ 0 };
        DirectX::XMFLOAT2 dummy;
    };
    struct SpotLightsConstant
    {
        DirectX::XMFLOAT4 position{ 0, 0, 0, 0 };
        DirectX::XMFLOAT4 direction{ 0, 0, 1, 0 };
        DirectX::XMFLOAT4 color{ 1, 1, 1, 1 };
        float range{ 0 };
        float power{ 0 };
        float innerCorn{ 0.99f };
        float outerCorn{ 0.9f };
    };
    struct LightConstants
    {
        DirectX::XMFLOAT4 light_direction;
        DirectX::XMFLOAT4 light_color;
        PointLightsConstant point_lights[MAX_SUPP_LIGHTS];
        SpotLightsConstant	spot_lights[MAX_SUPP_LIGHTS];
        int pointLightsSize;
        int spotLightsSize;
        DirectX::XMFLOAT2 dummy;
    };
    LightConstants lightConstant;
    PointLightsConstant pointLights[MAX_SUPP_LIGHTS];
    SpotLightsConstant spotLights[MAX_SUPP_LIGHTS];

};
