#pragma once
#include "Scene.h"


class SceneClear : public Scene
{
public:
    SceneClear();
    void init() override;
    void update(float elapsed_time) override;
    void draw() override;
    void release() override;
    ~SceneClear()override;
private:
    Sprite* back_;
};

