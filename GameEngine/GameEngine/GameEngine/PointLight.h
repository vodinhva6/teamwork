#pragma once
#include "DataFormat.h"
#include <vector>

class PointLight
{
public:
    PointLight(const VECTOR3& pos, const VECTOR4& colr, const float& rag, const float& pow);
    PointLight();
    ~PointLight();


public:
    VECTOR3& getPosition() { return position; }
    VECTOR4& getColor() { return color; }

    float& getRange() { return range; }
    float& getPower() { return power; }


public:
    void setPosition(const VECTOR3& pos) { position = pos; }
    void setColor(const VECTOR4& color) { this->color = color; }


    void setRange(const float& range) { this->range = range; }
    void setPower(const float& power) { this->power = power; }

private:

    VECTOR3 position{ 0,0,0 };
    VECTOR4 color{ 1,1,1,1 };
    float range{ 1 };
    float power{ 1 };
};
