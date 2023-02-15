#include "LightConstant.h"
#include "GraphicEngine.h"
#include "Misc.h"
void LightBuffer::CreateBuffer(ID3D11Device* device)
{
	HRESULT hr{ S_OK };
	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	buffer_desc.ByteWidth = sizeof(LightConstants);
	hr = device->CreateBuffer(&buffer_desc, nullptr, constantBuffer.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	PSSlotNum = 4;
	VSSlotNum = -1;
}

void LightBuffer::UpdateBuffer(ID3D11DeviceContext* dcContext)
{
	LightManager* lightManager = GraphicEngine::get()->getLightManager();
	
	lightConstant.light_direction = lightManager->getDirection();
	lightConstant.light_color = lightManager->getLightColor();
	lightConstant.pointLightsSize = static_cast<int>(lightManager->getSizePointLightList());
	lightConstant.spotLightsSize = static_cast<int>(lightManager->getSizeSpotLightList());
	//memcpy_s(lightConstant.point_lights, sizeof(lightConstant.point_lights), pointLights, sizeof(pointLights));
	//memcpy_s(lightConstant.spot_lights, sizeof(lightConstant.spot_lights), spotLights, sizeof(spotLights));
	dcContext->UpdateSubresource(constantBuffer.Get(), 0, 0, &lightConstant, 0, 0);

}