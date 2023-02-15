#include "SceneOver.h"
#include "GraphicEngine.h"
SceneOver::SceneOver()
{
    //back_ = GraphicEngine::get()->createSprite(L"./Data/Asset/Images/Background/over.png");
}

void SceneOver::init()
{
    ObjectManager::get()->CreateOver2DButton();

}

void SceneOver::update(float elapsed_time)
{
    ObjectManager::get()->ObjectUpdate(elapsed_time);
}

void SceneOver::draw()
{
    ObjectManager::get()->ObjectDraw();
    GraphicEngine* graph = GraphicEngine::get();
    //graph->drawBackgroudSpriteLate(back_, { 0,0 }, { 1920,1080 }, 0);
}

void SceneOver::release()
{
    ObjectManager::get()->resetObject();
}

SceneOver::~SceneOver()
{
}