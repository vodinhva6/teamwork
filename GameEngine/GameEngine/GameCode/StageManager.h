#pragma once
#include "OBJ2D.h"

class StageManager :public OBJ2D
{
public:
    StageManager();

    void draw() override;

    int getStage() { return stage; }



private:
    int stage;
};

