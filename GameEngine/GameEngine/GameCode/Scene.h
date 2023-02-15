#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <iostream>
#include "ObjectManager.h"
#include "LightManager.h"
#include "SpawnEnemyManager.h"


class Scene
{
public:

    Scene();
    virtual void reset() {}
    virtual void init() = 0;
    virtual void update(float elapsed_time) = 0;
    virtual void draw();
    virtual void release() {}
    virtual ~Scene();
    void setPause(bool pause) { this->pause = pause; }

protected:
    int timer;
    int state;
    bool pause;
};





#endif // !SCENE_H

