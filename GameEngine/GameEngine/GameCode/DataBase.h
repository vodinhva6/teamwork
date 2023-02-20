#pragma once
#include "DataFormat.h"
#include "SingletonPatternTemplate.h"
#include "Player.h"
#include "OBJ2D.h"
#include "Background.h" 
#include "LightManager.h"

class DataBase :public SingletonPatternTemplate<DataBase>
{
    friend class SingletonPatternTemplate<DataBase>;
public:
    DataBase();

    void CreateAllObject();
    Background* CreateBackground();
    Player* CreatePlayer(int stage);
   
    // SceneTitle
    StartButton* CreateStartButton();
    EndButton* CreateEndButton();
    // SceneStage
    Stage1Button* CreateStage1Button();
    Stage2Button* CreateStage2Button();
    Stage3Button* CreateStage3Button();
    //SceneGame
    Stage2D* CreateStage2D1();
    // Pause
    ContinueButton* CreateContinueButton();
    RetryButton* CreateRetryButton();
    BackToTitleButton* CreateBackToTitleButton();
    // SceneClear
    NextButton* CreateNextButton();
    ClearRetryButton* CreateClearRetryButton();
    ClearBackToStageButton* CreateClearBackToStageButton();
    ClearBackToTitleButton* CreateClearBackToTitleButton();
    // SceneOver
    OverRetryButton* CreateOverRetryButton();
    OverBackToStageButton* CreateOverBackToStageButton();
    OverBackToTitleButton* CreateOverBackToTitleButton();


    void CreateSpotLight(SpotLight* spotlgt[10], int stageNum);
    void CreatePointLight(PointLight* pointlgt[10], int stageNum);
    ~DataBase();
private:
    Player* player_;
    TutorialTable* table_;
    Background* skyBox_;
    // SceneTitle
    StartButton* startButton_;
    EndButton* endButton_;
    // SceneStage
    Stage1Button* stage1Button_;
    Stage2Button* stage2Button_;
    Stage3Button* stage3Button_;
    //SceneGame
    Stage2D* stage2d1_;
    // Pause
    ContinueButton* continueButton_;
    RetryButton* retryButton_;
    BackToTitleButton* backtotitleButton_;
    // SceneClear
    NextButton* nextButton_;
    ClearRetryButton* clearretryButton_;
    ClearBackToStageButton* clearbacktostageButton_;
    ClearBackToTitleButton* clearbacktotitleButton_;
    // SceneOver
    OverRetryButton* overretryButton_;
    OverBackToStageButton* overbecktostageButton_;
    OverBackToTitleButton* overbecktotitleButton_;

    VECTOR3 playerPos[10];
    float blockSize;
    PointLight* pointLights[MAX_SUPP_LIGHTS];
    SpotLight* spotLights[MAX_SUPP_LIGHTS];
};

