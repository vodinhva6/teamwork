#pragma once
#include <DirectXMath.h>
class ShadowManager
{
public:
    ShadowManager();
	void Init();
	void Update();
	DirectX::XMMATRIX& getSceneShadow() { return sceneShadowView3D; }
	float getBias() { return bias; }
    ~ShadowManager();
private:
	void UpdateProjection();
	float shadowmapViewDistance;
	float shadowmapViewSize;
	DirectX::XMMATRIX sceneShadowView3D;
	float bias = 0.001f;
	DirectX::XMMATRIX P;
};

