#include "SceneStage.h"
#include "GraphicEngine.h"
#include "SceneManager.h"
#include "DataBase.h"
SceneStage::SceneStage()
{
    back_ = GraphicEngine::get()->createSprite(L"./Data/Asset/Images/Background/stage.png");
}

void SceneStage::init()
{
    //CameraManager* cameraManager = CameraManager::get();
    GraphicEngine* graphicEngine = GraphicEngine::get();

    graphicEngine->getGameMode();

    //cameraManager->setActiveControl(false);
    //cameraManager->Change3DTo2D(1.0f);

   
    choss = 0;
    oldchoss = 0;

    //AudioManager::get()->stopAll();
    //AudioManager::get()->playMusic(MAINBGM, true);
    //AudioManager::get()->setMusicVolume(MAINBGM, 0.1f);
}

void SceneStage::update(float elapsed_time)
{
    oldchoss = choss;
    ObjectManager::get()->ObjectUpdate(elapsed_time);
}

void SceneStage::draw()
{
    ObjectManager::get()->ObjectDraw();
    GraphicEngine* graph = GraphicEngine::get();
    graph->drawBackgroudSpriteEarly(back_, { 0,0 }, { 1920,1080 }, 0);
}

void SceneStage::release()
{
    ObjectManager::get()->resetObject();
}

SceneStage::~SceneStage()
{
    release();
    listStageButton = nullptr;
}