#include "SceneTitle.h"
#include "ObjectManager.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "SceneManager.h"

SceneTitle::SceneTitle()
{
    sceneName = SceneName::Title;
}

void SceneTitle::init()
{
    state = 0;
    Scene::init();
}

void SceneTitle::update(float elapsed_time)
{
    //if (InputManager::get()->getMousePoint()->onClick())
    //    SceneManager::get()->changeScene(SCENEGAME, 30);
    Scene::update(elapsed_time);
}

void SceneTitle::draw()
{
    GraphicEngine* graph = GraphicEngine::get();

    Scene::draw();

    MousePoint* mousePoint = InputManager::get()->getMousePoint();

    static VECTOR2 beginPosition = {};
    static VECTOR2 endPosition = {};
    if (mousePoint->onClick())
    {
        beginPosition = mousePoint->getPos();
    }

    if (mousePoint->HoldClick())
    {
        endPosition = mousePoint->getPos();
    }
    else
    {
        beginPosition = { };
        endPosition = { };
    }

    graph->drawSquare( beginPosition, endPosition, 1, 1, 1, 1);

    graph->textOut(0, "TITLE", { 500,500 }, 1, { 1,1,1,1 }, 1, false);
}