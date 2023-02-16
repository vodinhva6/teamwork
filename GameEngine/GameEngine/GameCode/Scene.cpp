#include "Scene.h"
#include "MousePoint.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Audio.h"
#include "DataBase.h"
#include "GraphicEngine.h"
#include "Button3DManager.h"
#include "Button2DManager.h"
#include "AudioManager.h"

Scene::Scene()
{
    state = 0;

}

void Scene::init()
{
    timer = 0;
    ObjectManager::get()->CreateAllObject(sceneName);
}

void Scene::update(float elapsed_time)
{
    ObjectManager::get()->ObjectUpdate(elapsed_time);

    timer++;
}

void Scene::draw()
{
    ObjectManager::get()->ObjectDraw();
}

void Scene::release()
{
    ObjectManager::get()->ClearAllObject();
}

Scene::~Scene()
{
}


