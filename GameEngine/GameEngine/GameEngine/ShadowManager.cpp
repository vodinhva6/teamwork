#include "ShadowManager.h"
#include "GraphicEngine.h"

#include <d3d11.h>
ShadowManager::ShadowManager()
{
	P = {};
	shadowmapViewDistance = 0;
	shadowmapViewSize = 0;
	sceneShadowView3D = {};
}

void ShadowManager::Init()
{
	shadowmapViewDistance = -267.1f;
	shadowmapViewSize = 142.4f;

	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	GraphicEngine::get()->getDeviceContext()->RSGetViewports(&num_viewports, &viewport);
	float aspect_ratio = viewport.Width / viewport.Height;
	P = DirectX::XMMatrixOrthographicLH(shadowmapViewSize * aspect_ratio, shadowmapViewSize, 0.1f, 500.0f);
}

void ShadowManager::Update()
{
#ifdef _DEBUG
	ImGui::SliderFloat("Shadow Map View Distance", &shadowmapViewDistance, 0, 100);
#endif // _DEBUG

	UpdateProjection();
	LightManager* lightManager = GraphicEngine::get()->getLightManager();
	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat4(&lightManager->getVitualPos());
	VECTOR3 lightdirect = { lightManager->getDirection().x,lightManager->getDirection().y,lightManager->getDirection().z };
	DirectX::XMVECTOR Forward = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&lightdirect));
	DirectX::XMVECTOR Focus = DirectX::XMVectorAdd(Eye, Forward);
	Eye = DirectX::XMVectorAdd(Eye, DirectX::XMVectorScale(Forward, shadowmapViewDistance));
	DirectX::XMVECTOR Up = { 0,1,0,0 };
	DirectX::XMVECTOR Right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(Up, Forward));
	Up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(Forward, Right));
	sceneShadowView3D = DirectX::XMMatrixLookAtLH(Eye, Focus, Up) * P;





#ifdef _DEBUG
	ImGui::End();
#endif // _DEBUG

}

ShadowManager::~ShadowManager()
{
}

void ShadowManager::UpdateProjection()
{
#ifdef _DEBUG
	ImGui::SliderFloat("Shadow Map Size", &shadowmapViewSize, 1, 1000);
#endif // _DEBUG

	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	GraphicEngine::get()->getDeviceContext()->RSGetViewports(&num_viewports, &viewport);
	float aspect_ratio = viewport.Width / viewport.Height;
	P = DirectX::XMMatrixOrthographicLH(shadowmapViewSize * aspect_ratio, shadowmapViewSize, 0.1f, 500.0f);
}
