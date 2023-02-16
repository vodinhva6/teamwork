#pragma once
#include "Scene.h"
class SceneStage : public Scene
{
public:
    SceneStage();
    void init() override;
    void update(float elapsed_time) override;
    void draw() override;
    // void release() override;
    ~SceneStage()override;

private:
    Sprite* back_;
    Sprite* selectText_;
    const VECTOR2 selectTextSize = { 1330, 190 };
    const VECTOR2 selectTextInitPos = { (1920 - selectTextSize.x) / 2, 0 };

    int choss;
    int oldchoss;
    std::vector<StageButton*>* listStageButton;

};