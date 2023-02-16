#include "SceneStage.h"
#include "GraphicEngine.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "DataBase.h"
SceneStage::SceneStage()
{
    sceneName = SceneName::Stage;
}

void SceneStage::init()
{
    ObjectManager::get()->CreateAllObject(sceneName);

    GraphicEngine* graphicEngine = GraphicEngine::get();

    graphicEngine->getGameMode();
}

void SceneStage::update(float elapsed_time)
{
    // Transition To SceneGame
    if (InputManager::get()->getMousePoint()->onClick())
        SceneManager::get()->changeScene(SCENEGAME, 30);
    ObjectManager::get()->ObjectUpdate(elapsed_time);
}

void SceneStage::draw()
{
    //  ObjectManager::get()->ObjectDraw();
    //  GraphicEngine* graph = GraphicEngine::get();
    //  graph->drawBackgroudSpriteEarly(back_, { 0,0 }, { 1920,1080 }, 0);

    GraphicEngine* graph = GraphicEngine::get();
    ObjectManager::get()->ObjectDraw();

    graph->textOut(0, "SceneStage", { 500,500 }, 1, { 1,1,1,1 }, 1, false);
}

void SceneStage::release()
{
    ObjectManager::get()->ClearAllObject();
}

SceneStage::~SceneStage()
{
    release();
    listStageButton = nullptr;
}