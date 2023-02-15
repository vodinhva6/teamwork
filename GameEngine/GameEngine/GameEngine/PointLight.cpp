#include "LightManager.h"
PointLight::PointLight(const VECTOR3& pos, const VECTOR4& colr, const float& rag, const float& pow)
{
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    color = colr;

    range = rag;
    power = pow;
}
PointLight::PointLight()
{

}

PointLight::~PointLight()
{

}
