#pragma once
#include "Scene.h"
class SceneOver : public Scene
{
public:
    SceneOver();
    void init() override;
    void update(float elapsed_time) override;
    void draw() override;
    void release() override;
    ~SceneOver() override;

private:
    Sprite* back_;

};
