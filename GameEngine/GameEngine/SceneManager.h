#pragma once
#include "SingletonPatternTemplate.h"
class SceneManager :public SingletonPatternTemplate< SceneManager>
{
    friend class SingletonPatternTemplate< SceneManager>;
public:

    Scene* getSceneNow()
    {
        return sceneNow;
    }
    Scene* getSceneNext()
    {
        return sceneNext;
    }
    Scene* getSceneGame()
    {
        return listScene["SCENEGAME"];
    }
    void updateChangeScene();
    void setSceneNext(Scene* sc) { sceneNext = sc; }
    bool exit;
    bool changeScene(std::string sceneName, int delayTimer)
    {
        if (sceneNext == listScene[sceneName])
            return false;
        timer = delayTimer;
        sceneNext = listScene[sceneName];
        return true;

    }
    Sprite* loadingScr[2];

    int getStage() { return stage; }
    void saveGame();
    void loadGame();
    bool checkHadFileLoadGame();
    std::vector<StageButton*>* getListStageButton() { return &listStageButton; }
    std::vector<Button*>* getListPauseButton() { return &listPauseButton; }
    std::vector<Button*>* getListClearButton() { return &listClearButton; }
    ~SceneManager();
private:

    SceneManager();
    std::map<std::string, Scene*> listScene;
    Scene* sceneNow;
    Scene* sceneNext;
    int stage;
    int timer;
    std::vector<StageButton*> listStageButton;
    std::vector<Button*> listPauseButton;
    std::vector<Button*> listClearButton;
    std::vector<TutorialTable*> table;
};

