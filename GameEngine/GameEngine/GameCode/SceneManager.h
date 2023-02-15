#pragma once
#include "SingletonPatternTemplate.h"
#include "Scene.h"

#define SCENESTAGE "SCENESTAGE"
#define SCENETITLE "SCENETITLE"
#define SCENEOVER "SCENEOVER"
#define SCENEGAME  "SCENEGAME"
#define SCENECLEAR  "SCENECLEAR"
#define SCENEMENU "SCENEMENU"

class SceneManager : public SingletonPatternTemplate<SceneManager>
{
    friend class SingletonPatternTemplate<SceneManager>;
public:
    SceneManager();
    void Init();
    void Update(float elapsedTime);
    void Render();
    Scene* getSceneNow()
    {
        return sceneNow;
    }
    Scene* getSceneGame()
    {
        return listScene["SCENEGAME"].get();
    }
    void UpdateChangeScene();
    void setSceneNext(Scene* sc) { sceneNext = sc; }
    bool exit;
    bool changeScene(std::string sceneName, int delayTimer);
    Sprite* loadingScr[2];

    int getStage() { return stage; }
    void saveGame();
    void loadGame();
    bool checkHadFileLoadGame();
    ~SceneManager();
private:

    
    std::map<std::string, std::shared_ptr<Scene>> listScene;
    Scene* sceneNow;
    Scene* sceneNext;
    int stage;
    int timer;
};
