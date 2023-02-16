#pragma once
#include "SpotLight.h"
#include "PointLight.h"
#include "ShadowManager.h"
#include <memory>

#define MAX_SUPP_LIGHTS 20

class LightManager 
{
public:

    LightManager();
    void init(const VECTOR3& dir, const VECTOR4& colr, const VECTOR3& vitualPos);
    void Update();
    void setLightPos(const VECTOR3& pos);
    void setLightDir(const VECTOR3& dir);
    ShadowManager* getShadowManager() { return shadowManager.get(); }
    void DeleteList();

    ~LightManager();

    VECTOR4& getVitualPos() { return vitualPosition; }
    VECTOR4& getDirection() { return lightDirection; }
    VECTOR4& getLightColor() { return lightColor; }

    size_t getSizePointLightList() { return listPointLights.size(); }
    size_t getSizeSpotLightList() { return listSpotLights.size(); }

private:
    VECTOR4 lightDirection;
    VECTOR4 lightColor;
    VECTOR4 vitualPosition;
    std::vector<PointLight*> listPointLights;
    std::vector<SpotLight*> listSpotLights;
    std::unique_ptr<ShadowManager> shadowManager;

};

