#include "SceneTitle.h"
#include "ObjectManager.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "SceneManager.h"

void SceneTitle::init()
{
    state = 0;

}

void SceneTitle::update(float elapsed_time)
{
    if (InputManager::get()->getMousePoint()->onClick())
        SceneManager::get()->changeScene(SCENEGAME, 30);
    ObjectManager::get()->ObjectUpdate(elapsed_time);
}

void SceneTitle::draw()
{
    GraphicEngine* graph = GraphicEngine::get();
    ObjectManager::get()->ObjectDraw();

    graph->textOut(0, "TITLE", { 500,500 }, 1, { 1,1,1,1 }, 1, false);


}

void SceneTitle::release()
{
    ObjectManager::get()->resetObject();
}