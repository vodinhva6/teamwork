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

void Scene::draw()
{
    //MousePoint::get()->draw();
}

Scene::~Scene()
{
}


