#include "SceneClear.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "SceneManager.h"
SceneClear::SceneClear()
{
    
}

void SceneClear::init()
{

}

void SceneClear::update(float elapsed_time)
{
    ObjectManager::get()->ObjectUpdate(elapsed_time);
    if (InputManager::get()->getMousePoint()->onClick())
        SceneManager::get()->changeScene(SCENETITLE, 0);
    timer++;
}

void SceneClear::draw()
{
    GraphicEngine* graph = GraphicEngine::get();
    ObjectManager::get()->ObjectDraw();
    graph->textOut(0, "CLEAR", { 500,500 }, 1, { 1,1,1,1 }, 1, false);   
}

void SceneClear::release()
{
    ObjectManager::get()->resetObject();
}

SceneClear::~SceneClear()
{
}