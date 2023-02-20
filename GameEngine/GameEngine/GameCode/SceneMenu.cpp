#include "SceneMenu.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "SceneManager.h"

SceneMenu::SceneMenu()
{
}

void SceneMenu::init()
{
    sceneName = SceneName::Menu;

    Scene::init();
}

void SceneMenu::update(float elapsed_time)
{
    if (InputManager::get()->getControlPad()->PressBack(0))
        SceneManager::get()->changeScene(SCENEGAME, 0);

    Scene::update(elapsed_time);
}

void SceneMenu::draw()
{
    GraphicEngine* graph = GraphicEngine::get();

    Scene::draw();

    graph->textOut(0, "Menu", {500, 500}, 1, { 1, 1, 1, 1}, 1);
}

SceneMenu::~SceneMenu()
{
}
