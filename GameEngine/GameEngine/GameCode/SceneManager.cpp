#include "SceneManager.h"
#include "GraphicEngine.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneClear.h"
#include "SceneStage.h"
#include "SceneOver.h"
#include "SceneMenu.h"
#include "DataBase.h"
void SceneManager::saveGame()
{
    std::ofstream myfile;
    myfile.open(L"./Data/Save/savegame.txt");
    //Save Game



    //

    myfile.close();
}

void SceneManager::loadGame()
{

    std::ifstream input;
    input.open(L"./Data/Save/savegame.txt");
    //Load Game




    //
    input.close();

}

bool SceneManager::checkHadFileLoadGame()
{
    std::ifstream input;
    input.open(L"./Data/Save/savegame.txt");

    if (input.fail())
    {
        return false;
    }
    return true;
}


SceneManager::~SceneManager()
{


    listScene.clear();
    delete ObjectManager::get();
    //delete DataBase::get();
    //delete Button2DManager::get();
   
    
   
}

SceneManager::SceneManager()
{
   

}

void SceneManager::Init()
{
    timer = 0;
    //DataBase* dataBase = DataBase::get();
    //dataBase->CreateAllObject();
    listScene =
    {
        {"SCENESTAGE",std::make_shared<SceneStage>()},
        {"SCENETITLE",std::make_shared<SceneTitle>()},
        {"SCENEGAME",std::make_shared<SceneGame>()},
        {"SCENEMENU",std::make_shared<SceneMenu>()},
        {"SCENECLEAR",std::make_shared<SceneClear>()},
        {"SCENEOVER", std::make_shared<SceneOver>()}
    };
    sceneNow = listScene[SCENETITLE].get();
    sceneNext = listScene[SCENETITLE].get();

    sceneNow->init();
    exit = false;

    stageManager = std::make_unique<StageManager>();
}

void SceneManager::Update(float elapsedTime)
{
    sceneNow->update(elapsedTime);
}

void SceneManager::Render()
{
    sceneNow->draw();
}

void SceneManager::UpdateChangeScene()
{
    if (timer <= 0)
    {
        if (sceneNow != sceneNext)
        {
            if (sceneNext != listScene["SCENEMENU"].get())
            {
                sceneNow->release();
            }

            sceneNow = sceneNext;
            sceneNow->init();
            //sceneNow->release();
            //sceneNext->init();
            //sceneNow = sceneNext;
        }
    }
    else timer--;
}

bool SceneManager::changeScene(std::string sceneName, int delayTimer)
{
    if (sceneNext == listScene[sceneName].get())
        return false;
    timer = delayTimer;
    sceneNext = listScene[sceneName].get();
    return true;
}