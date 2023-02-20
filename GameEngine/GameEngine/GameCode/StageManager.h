#pragma once
#include "OBJ2D.h"

class StageManager
{
public:
    StageManager();

    void CreateAllStage2D(int stageNo);

    int getStage() { return stage; }

    void StageDraw();

private:
    void Create2DStage1();
private:
    int stage;

    enum StageNo
    {
        Stage1,
        Stage2,
        Stage3
    };

    std::list<OBJ2D*> stage2DList;
};
