#pragma once
#include "OBJ3D.h"
class Background:public OBJ3D
{
public:

    Background() {}
    Background(const Background& data);
    void draw() override;
    void update(float elapsedtime) override;
};

