#include "SceneGame.h"
#include "SceneManager.h"
#include "DataBase.h"
#include "GraphicEngine.h"
#include "InputManager.h"
SceneGame::SceneGame()
{
}

void SceneGame::reset()
{
    release();
}

static int at = 4;
void SceneGame::init()
{
    state = 0;
    timer = 0;
    int stage = SceneManager::get()->getStage();
    //ObjectManager::get()->createObject3D(stage);
    pause = false;
}

void SceneGame::update(float elapsed_time)
{
    ToSpawnEnemy();
    ObjectManager::get()->ObjectUpdate(elapsed_time);
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
    ObjectManager::get()->resetObject();
}


SceneGame::~SceneGame()
{

}

void SceneGame::ToSpawnEnemy()
{

}
