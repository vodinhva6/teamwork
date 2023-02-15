#include "ConstantBuffer.h"
#include "Misc.h"
#include "GraphicEngine.h"
void SceneBuffer::CreateBuffer(ID3D11Device* device)
{
	HRESULT hr{ S_OK };
	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	buffer_desc.ByteWidth = sizeof(SceneConstant);
	hr = device->CreateBuffer(&buffer_desc, nullptr, constantBuffer.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	PSSlotNum = 1;
	VSSlotNum = 1;
}

void SceneBuffer::UpdateBuffer(ID3D11DeviceContext* dcContext)
{
	CameraManager* cameraManager = GraphicEngine::get()->getCameraManager();
	sceneConstant.cameraPosition = cameraManager->getGameCameraPosition4();
	XMStoreFloat4x4(&sceneConstant.viewProjection, cameraManager->getSceneView3D());
	dcContext->UpdateSubresource(constantBuffer.Get(), 0, 0, &sceneConstant, 0, 0);
}


void ColorFilterBuffer::CreateBuffer(ID3D11Device* device)
{
	HRESULT hr{ S_OK };
	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	buffer_desc.ByteWidth = sizeof(ColorFilter);
	hr = device->CreateBuffer(&buffer_desc, nullptr, constantBuffer.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	PSSlotNum = 2;
	VSSlotNum = 2;
}

void ColorFilterBuffer::UpdateBuffer(ID3D11DeviceContext* dcContext)
{
	//ColorFilter filter{};
	//filter.hueShift = color_filter_parameter.x;
	//filter.saturation = color_filter_parameter.y;
	//filter.brightness = color_filter_parameter.z;
	dcContext->UpdateSubresource(constantBuffer.Get(), 0, 0, &colorFilerConstant, 0, 0);
}

void ShadowBuffer::CreateBuffer(ID3D11Device* device)
{
	HRESULT hr{ S_OK };
	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	buffer_desc.ByteWidth = sizeof(ShadowConstant);
	hr = device->CreateBuffer(&buffer_desc, nullptr, constantBuffer.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	PSSlotNum = 3;
	VSSlotNum = 3;
}

void ShadowBuffer::UpdateBuffer(ID3D11DeviceContext* dcContext)
{
	ShadowManager* shadowManager = GraphicEngine::get()->getLightManager()->getShadowManager();
	shadowConstant.shadow_bias = shadowManager->getBias();
	XMStoreFloat4x4(&shadowConstant.shadowmap_view_projection, shadowManager->getSceneShadow());
	dcContext->UpdateSubresource(constantBuffer.Get(), 0, 0, &shadowConstant, 0, 0);
}


void FogBuffer::CreateBuffer(ID3D11Device* device)
{
	HRESULT hr{ S_OK };
	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;
	buffer_desc.ByteWidth = sizeof(FogConstant);
	hr = device->CreateBuffer(&buffer_desc, nullptr, constantBuffer.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));
	PSSlotNum = 6;
	VSSlotNum = 6;
}

void FogBuffer::UpdateBuffer(ID3D11DeviceContext* dcContext)
{
	//FogConstant fogConstant;
	//fogConstant.fogRange = fogRange_;
	//fogConstant.fogColor = fogColor_;
	dcContext->UpdateSubresource(constantBuffer.Get(), 0, 0, &fogConstant, 0, 0);
}

