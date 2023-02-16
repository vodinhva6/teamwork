#include "SceneGame.h"
#include "SceneManager.h"
#include "DataBase.h"
#include "GraphicEngine.h"
#include "InputManager.h"
SceneGame::SceneGame()
{
    sceneName = SceneName::Game;
}

//void SceneGame::reset()
//{
//    release();
//}

static int at = 4;
void SceneGame::init()
{
    int stage = SceneManager::get()->getStage();

    translationToMenuScene = false;

    Scene::init();
}

void SceneGame::update(float elapsed_time)
{
    ToSpawnEnemy();

    if (InputManager::get()->getControlPad()->PressBack(0))
    {
        SceneManager::get()->changeScene(SCENEMENU, 0);
        translationToMenuScene = true;
    }

    if (InputManager::get()->getMousePoint()->onClick())
        SceneManager::get()->changeScene(SCENECLEAR, 60);

    Scene::update(elapsed_time);
}

void SceneGame::draw()
{
    GraphicEngine* graph = GraphicEngine::get();

    Scene::draw();

    graph->textOut(0, "GAME", { 500,500 }, 1, { 1,1,1,1 }, 1, false);
}

void SceneGame::release()
{
    if (translationToMenuScene) return;

    Scene::release();
}

SceneGame::~SceneGame()
{

}

void SceneGame::ToSpawnEnemy()
{

}
