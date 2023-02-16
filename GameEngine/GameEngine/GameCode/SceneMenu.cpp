#include "SceneMenu.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "SceneManager.h"

SceneMenu::SceneMenu()
{
}

void SceneMenu::init()
{
    timer = 0;

    sceneName = SceneName::Menu;

    ObjectManager::get()->CreateAllObject(sceneName);
}

void SceneMenu::update(float elapsed_time)
{
    ObjectManager::get()->ObjectUpdate(elapsed_time);

    if (InputManager::get()->getControlPad()->PressBack(0))
        SceneManager::get()->changeScene(SCENEGAME, 0);
}

void SceneMenu::draw()
{
    GraphicEngine* graph = GraphicEngine::get();
    ObjectManager::get()->ObjectDraw();

    graph->textOut(0, "Menu", {500, 500}, 1, { 1, 1, 1, 1}, 1);
}

void SceneMenu::release()
{
}

SceneMenu::~SceneMenu()
{
}
