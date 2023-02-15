#include "ConstantBufferManager.h"
#include "LightConstant.h"

void ConstantBufferManager::Init(ID3D11Device* device)
{
    SceneBuffer* sceneBuffer = new SceneBuffer;
    constantBufferList.push_back(sceneBuffer);
    LightBuffer* lightBuffer = new LightBuffer;
    constantBufferList.push_back(lightBuffer);
    ColorFilterBuffer* colorFilterBuffer = new ColorFilterBuffer;
    constantBufferList.push_back(colorFilterBuffer);
    ShadowBuffer* shadowBuffer = new ShadowBuffer;
    constantBufferList.push_back(shadowBuffer);
    FogBuffer* fogBuffer = new FogBuffer;
    constantBufferList.push_back(fogBuffer);

    CreateConstantBuffer(device);
    int a = 1;
    a = 2;
}

void ConstantBufferManager::setPSSlotNum(ID3D11DeviceContext* dcContext)
{
    for (UINT32 i = 0; i < constantBufferList.size(); i++)
    {
        int slot = constantBufferList[i]->getPSSlotNum();
        if (slot > 0)
            dcContext->PSSetConstantBuffers(slot, 1, constantBufferList[i]->getAddrBuffer());
    }

}

void ConstantBufferManager::setVSSlotNum(ID3D11DeviceContext* dcContext)
{
    for (UINT32 i = 0; i < constantBufferList.size(); i++)
    {
        int slot = constantBufferList[i]->getVSSlotNum();
        if (slot > 0)
            dcContext->VSSetConstantBuffers(slot, 1, constantBufferList[i]->getAddrBuffer());
    }
}

void ConstantBufferManager::updateResource(ID3D11DeviceContext* dcContext)
{
    for (UINT32 i = 0; i < constantBufferList.size(); i++)
    {
        constantBufferList[i]->UpdateBuffer(dcContext);
    }
}

ConstantBufferManager::~ConstantBufferManager()
{
    for (UINT32 i = 0; i < constantBufferList.size(); i++)
    {
        SafeDelete(constantBufferList[i]);
    }
}

void ConstantBufferManager::CreateConstantBuffer(ID3D11Device* device)
{
    for (UINT32 i = 0; i < constantBufferList.size(); i++)
    {
        constantBufferList[i]->CreateBuffer(device);
    }
}
