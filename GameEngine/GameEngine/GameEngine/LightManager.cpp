#include "LightManager.h"
#include "GraphicEngine.h"
void LightManager::init(const VECTOR3& dir, const VECTOR4& colr, const VECTOR3& vitualPos)
{
    lightDirection = { dir.x,dir.y,dir.z,0 };
    vitualPosition = vitualPos;
    lightColor = colr;
    shadowManager.reset(new ShadowManager);
    shadowManager.get()->Init();
}
void LightManager::Update()
{
#ifdef _DEBUG
    ImGui::Begin("Light Manager");
    ImGui::SliderFloat3("Light Direct", &lightDirection.x, -50, 50);
    ImGui::SliderFloat3("Light position", &vitualPosition.x, -50, 50);
#endif // _DEBUG

   
   

    shadowManager.get()->Update();
    
}

void LightManager::setLightPos(const VECTOR3& pos)
{
    vitualPosition.x = pos.x;
    vitualPosition.y = pos.y;
    vitualPosition.z = pos.z;
}

void LightManager::setLightDir(const VECTOR3& dir)
{
    lightDirection.x = dir.x;
    lightDirection.y = dir.y;
    lightDirection.z = dir.z;
}


void LightManager::DeleteList()
{
    listPointLights.clear();
    listSpotLights.clear();
}

LightManager::LightManager()
{
    lightDirection = { 0,0,-1,0 };
    vitualPosition = { 0,0,1 };
    lightColor = { 1,1,1,1 };
}

LightManager::~LightManager()
{
    DeleteList();
}


