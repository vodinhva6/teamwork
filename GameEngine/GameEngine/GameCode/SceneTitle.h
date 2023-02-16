#pragma once
#include "Scene.h"
class SceneTitle :public Scene
{
public:
    SceneTitle();
    void init()  override;
    void update(float elapsed_time)override;
    void draw()  override;
    //void release() override;
    ~SceneTitle()override {}
private:
    Sprite* title;
    Sprite* logo;
};
