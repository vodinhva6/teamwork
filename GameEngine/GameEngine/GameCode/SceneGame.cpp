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
    Scene::init();

    int stage = SceneManager::get()->getStage();
}

void SceneGame::update(float elapsed_time)
{
    ToSpawnEnemy();
    ObjectManager::get()->ObjectUpdate(elapsed_time);
    if (InputManager::get()->getControlPad()->PressBack(0))
        SceneManager::get()->changeScene(SCENEMENU, 0);

    if (InputManager::get()->getMousePoint()->onClick())
        SceneManager::get()->changeScene(SCENECLEAR, 60);
    timer++;
}

void SceneGame::draw()
{
    GraphicEngine* graph = GraphicEngine::get();
    ObjectManager::get()->ObjectDraw();

    graph->textOut(0, "GAME", { 500,500 }, 1, { 1,1,1,1 }, 1, false);
}

void SceneGame::release()
{

}

SceneGame::~SceneGame()
{

}

void SceneGame::ToSpawnEnemy()
{

}
