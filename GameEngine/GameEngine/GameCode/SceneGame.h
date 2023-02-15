#pragma once
#include "Scene.h"
class SceneGame : public Scene
{
public:
    SceneGame();
    void reset() override;
    void init() override;
    void update(float elapsed_time)override;
    void draw()override;
    void release() override;
    ~SceneGame() override;
private:

    void ToSpawnEnemy();

};