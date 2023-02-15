#pragma once
#include <d3d11.h>
#include <wrl.h>

#include "DataFormat.h"
class ConstantBuffer
{
public:
    virtual void CreateBuffer(ID3D11Device* device) = 0;
    virtual void UpdateBuffer(ID3D11DeviceContext* dcContext) = 0;
    virtual ~ConstantBuffer() {};
    int getPSSlotNum() { return PSSlotNum; }
    int getVSSlotNum() { return VSSlotNum; }
    ID3D11Buffer** getAddrBuffer() { return constantBuffer.GetAddressOf(); }
protected:
    int PSSlotNum;
    int VSSlotNum;
    Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
};

class SceneBuffer: public ConstantBuffer
{
public:
    void CreateBuffer(ID3D11Device* device) override;
    void UpdateBuffer(ID3D11DeviceContext* dcContext) override;
    ~SceneBuffer() override {}
private:
    struct SceneConstant
    {
        DirectX::XMFLOAT4X4 viewProjection;
        DirectX::XMFLOAT4 cameraPosition;
    };
    SceneConstant sceneConstant;
    
};



class ColorFilterBuffer : public ConstantBuffer
{
public:
    void CreateBuffer(ID3D11Device* device) override;
    void UpdateBuffer(ID3D11DeviceContext* dcContext) override;
    ~ColorFilterBuffer() override {}

private:
    struct ColorFilter
    {
        float hueShift;  
        float saturation;
        float brightness;
        float dummy;
    };
    ColorFilter colorFilerConstant;

};


class ShadowBuffer : public ConstantBuffer
{
public:
    void CreateBuffer(ID3D11Device* device) override;
    void UpdateBuffer(ID3D11DeviceContext* dcContext) override;
    ~ShadowBuffer() override {}

private:
    struct ShadowConstant
    {
        DirectX::XMFLOAT4X4 shadowmap_view_projection;
        float shadow_bias;
        DirectX::XMFLOAT3 dummy;
    };
    ShadowConstant shadowConstant;

};


class FogBuffer : public ConstantBuffer
{
public:
    void CreateBuffer(ID3D11Device* device) override;
    void UpdateBuffer(ID3D11DeviceContext* dcContext) override;
    ~FogBuffer() override {}

private:
    struct FogConstant
    {
        VECTOR4 fogRange;
        VECTOR4 fogColor;
    };
    FogConstant fogConstant;

};