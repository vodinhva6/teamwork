#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <iostream>
#include "ObjectManager.h"
#include "LightManager.h"
#include "SpawnEnemyManager.h"
enum class SceneName
{
    Title,
    Game,
    Over,
    Clear,
    Menu
};

class Scene
{
public:

    Scene();
    virtual void reset() {}
    virtual void init();
    virtual void update(float elapsed_time);
    virtual void draw();
    virtual void release();
    virtual ~Scene();
    void setPause(bool pause) { this->pause = pause; }

protected:
    int timer;
    int state;
    bool pause;
    SceneName sceneName;
};





#endif // !SCENE_H

