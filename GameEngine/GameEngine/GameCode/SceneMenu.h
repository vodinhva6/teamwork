#pragma once
#include "Scene.h"
class SceneMenu : public Scene
{
public:
    SceneMenu();
    void init() override;
    void update(float elapsed_time) override;
    void draw() override;
    //void release() override;
    ~SceneMenu();

private:
    int choss;
    Sprite* pauseSpr_[2];
    std::vector<Button*>* listPauseButton;
};