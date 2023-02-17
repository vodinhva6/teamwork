#include "DataBase.h"
#include "Scene.h"
#include "ControlPad.h"
#include "GraphicEngine.h"
void DataBase::CreateAllObject()
{
    GraphicEngine* graphicEngine = GraphicEngine::get();
    
    playerPos[0] = {0,5,0};
    playerPos[1] = {0,5,0};
    playerPos[2] = {0,5,0};
    playerPos[3] = {0,5,0};
    playerPos[4] = {0,5,0};
    playerPos[5] = { 9.8f, -15, 0 }; 
    playerPos[6] = { 0,5,0 };
    playerPos[7] = {0,5,0};
    playerPos[8] = {0,5,0};
    playerPos[9] = {0,5,0};

    ShaderData shaderData = { "./Data/Shaders/skinned_mesh_vs.cso", "./Data/Shaders/skinned_mesh_ps.cso" };
    
    

    //skyBox_ = new Background;
    //skyBox_->mesh_ = graphicEngine->createSkinnedMesh("./Data/Asset/3DObject/SkyBox/sky.fbx", true, SkinnedMeshObjectAxis::DEFAULT, shaderData);
    //skyBox_->drawStates_.blendState = BlendStates::Alpha;
    //skyBox_->drawStates_.depthState = DepthStencilStates::DepthTestOn_DepthWriteOn;
    //skyBox_->drawStates_.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn;
    //skyBox_->drawStates_.samplerState = SamplerStates::Anisotropic;
    //skyBox_->drawStates_.drawType = DrawType::SKYBOX;
    //skyBox_->position_ = { 0,0,0 };
    //skyBox_->speedRotation_ = { 0,0,0 };
    //skyBox_->offSet_ = { 0,0.1f,0 };
    //skyBox_->rotation_ = { 0,0,0 };
    //skyBox_->color_ = { 1,1,1,1 };
    //skyBox_->drawTurn_ = 0;
    //skyBox_->scale_ = { 1,1,1 };
    //skyBox_->size_ = 5;
    //skyBox_->gravityValue = 0;
    //
    //
    //
    //
    //player_ = new Player;
    //player_->mesh_ = graphicEngine->createSkinnedMesh("./Data/Asset/3DObject/Player/player.fbx", false, SkinnedMeshObjectAxis::DEFAULT, shaderData, { 0,0.0f,0 });
    //player_->position_ = { 0,10,0 };
    //player_->speedRotation_ = { 0,0,0 };
    //player_->offSet_ = { 0,0.1f,0 };
    //player_->rotation_ = { 0,0,0 };
    //player_->color_ = { 1,1,1,1 };
    //player_->drawTurn_ = 9;
    //player_->scale_ = { 1,1,1 };
    //player_->size_ = 5.7f;
    //player_->drawStates_.blendState = BlendStates::Alpha;
    //player_->drawStates_.depthState = DepthStencilStates::DepthTestOn_DepthWriteOn;
    //player_->drawStates_.rasterizerState = RasterizerStates::CullingOpposition;
    //player_->drawStates_.samplerState = SamplerStates::Anisotropic;
    //player_->gravityValue = -0.07f; 
    //player_->animation.animat = &player_->mesh_->animation_clips.at(0);
    //player_->animation.oldanimat = player_->animation.animat;
    //player_->animation.key_ = &player_->animation.animat->sequence.at(0);
    //player_->animation.frameStepSpeed = 1;
    //player_->animation.oldFrameStepSpeed = 1;
    //player_->animation.animationFrame = player_->animation.animat->sequence.size();
    //player_->animation.trigger = false;
    //player_->setAnimat(AnimatNum::Idle, 0.01f);
    //VECTOR3 minVertex = player_->mesh_->VertexMinMaxInfor[0];
    //VECTOR3 maxVertex = player_->mesh_->VertexMinMaxInfor[1];
    //VECTOR3 Hsize = { fabsf(minVertex.x - maxVertex.x), fabsf(minVertex.y - maxVertex.y) ,fabsf(minVertex.z - maxVertex.z) };
    //
    //    
    //player_->CreateRay({ 0,minVertex.y + Hsize.y / 2, minVertex.z / 3 },
    //    { 0, minVertex.y - 0.01f,minVertex.z / 3 }, { 1,0,0,1 }, RayType::GroundRay);
    //    
    //player_->CreateRay({ 0,minVertex.y + Hsize.y / 2, maxVertex.z / 4 },
    //    { 0, minVertex.y - 0.01f,maxVertex.z / 4 }, {1,0,0,1}, RayType::GroundRay);
    //    
    //player_->CreateRay({ 0,minVertex.y + Hsize.y / 8.0f,0 },
    //    { 0,minVertex.y + Hsize.y / 8.0f,maxVertex.z + maxVertex.z / 8 }, { 1,1,1,1 }, RayType::WallRay);
    //    
    //player_->CreateRay({ 0,Hsize.y / 3,0 },
    //    { 0,Hsize.y / 3,maxVertex.z + maxVertex.z / 8 }, { 1,1,1,1 }, RayType::WallRay);
    //   
    //player_->CreateRay({ 0,maxVertex.y - Hsize.y / 3,0 },
    //    { 0,maxVertex.y - Hsize.y / 3,maxVertex.z + maxVertex.z / 8 }, { 1,1,1,1 }, RayType::WallRay);
    //   
    //player_->CreateRay({ 0,maxVertex.y - Hsize.y / 10.0f,0 },
    //    { 0,maxVertex.y - Hsize.y / 10.0f,maxVertex.z + maxVertex.z / 8 }, { 1,1,1,1 }, RayType::WallRay);
    //
    //player_->CreateRay({ 0,maxVertex.y + 1,0 },
    //    { 0,maxVertex.y + 1 ,maxVertex.z + 0.4f }, { 0,1,0,1 }, RayType::TakingBlockWallRay);
    //
    //player_->CreateRay({ 0,maxVertex.y + 1,0 },
    //    { 0,maxVertex.y + 1 ,minVertex.z - 0.4f }, { 0,1,0,1 }, RayType::TakingBlockWallRay);
    //
    //player_->CreateRay({ 0,maxVertex.y + 0.9f,-0.8f },
    //    { 0,maxVertex.y + 1.9f ,-0.8f }, { 0,1,0,1 }, RayType::TakingBlockUpRay);
    //
    //player_->CreateRay({ 0,maxVertex.y + 0.9f, 0.8f},
    //    { 0,maxVertex.y + 1.9f , 0.8f }, { 0,1,0,1 }, RayType::TakingBlockUpRay);
    //
    //player_->CreateRay({ 0,(minVertex.y + maxVertex.y) / 3 * 2,maxVertex.z }, { 0,maxVertex.y,maxVertex.z }, { 0,0,1,1 }, RayType::UptopHeadRay);
    //
    //player_->CreateRay({ 0,(minVertex.y + maxVertex.y) / 3 * 2,minVertex.z }, { 0,maxVertex.y,minVertex.z }, { 0,0,1,1 }, RayType::UptopHeadRay);
    //
    //
    //player_->updateWorldTrans();
    //
    //



    // SceneTitle
#if 1
    startButton_ = new StartButton;
    startButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/Start.png");
    startButton_->position_ = { 460, 64 };
    startButton_->scale_ = { 1, 1 };
    startButton_->color_ = { 1, 1, 1, 1 };
    startButton_->size_ = 1;
    startButton_->texturePosition_ = { 0, 0 };
    startButton_->textureSize_ = { 482, 200 };
    startButton_->hSize_ = startButton_->textureSize_;

    endButton_ = new EndButton;
    endButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/End.png");
    endButton_->position_ = { 500, 200 };
    endButton_->scale_ = { 1, 1 };
    endButton_->color_ = { 1, 1, 1, 1 };
    endButton_->size_ = 1;
    endButton_->texturePosition_ = { 0, 0 };
    endButton_->textureSize_ = { 482, 200 };
    endButton_->hSize_ = endButton_->textureSize_;
#endif

    // SceneStage
#if 1
    //stage1Button_ = new Stage1Button;
    //stage1Button_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/1.png");
    //stage1Button_->position_ = { 400, 500 };
    //stage1Button_->scale_ = { 1, 1 };
    //stage1Button_->color_ = { 1, 1, 1, 1 };
    //stage1Button_->size_ = 1;
    //stage1Button_->texturePosition_ = { 0, 0 };
    //stage1Button_->textureSize_ = { 150, 150 };
    //stage1Button_->hSize_ = { 150, 150 };
    //
    //stage2Button_ = new Stage2Button;
    //stage2Button_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/2.png");
    //stage2Button_->position_ = { 800, 500 };
    //stage2Button_->scale_ = { 1, 1 };
    //stage2Button_->color_ = { 1, 1, 1, 1 };
    //stage2Button_->size_ = 1;
    //stage2Button_->texturePosition_ = { 0, 0 };
    //stage2Button_->textureSize_ = { 150, 150 };
    //stage2Button_->hSize_ = { 150, 150 };
    //
    //stage3Button_ = new Stage3Button;
    //stage3Button_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/3.png");
    //stage3Button_->position_ = { 1200, 500 };
    //stage3Button_->scale_ = { 1, 1 };
    //stage3Button_->color_ = { 1, 1, 1, 1 };
    //stage3Button_->size_ = 1;
    //stage3Button_->texturePosition_ = { 0, 0 };
    //stage3Button_->textureSize_ = { 150, 150 };
    //stage3Button_->hSize_ = { 150, 150 };
#endif

    // Pause
#if 1
    continueButton_ = new ContinueButton;
    continueButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/Continue.png");
    continueButton_->position_ = { 750, 250 };
    continueButton_->scale_ = { 1, 1 };
    continueButton_->color_ = { 1, 1, 1, 1 };
    continueButton_->size_ = 1;
    continueButton_->texturePosition_ = { 0, 0 };
    continueButton_->textureSize_ = { 635, 115 };
    continueButton_->hSize_ = { 635, 115 };

    retryButton_ = new RetryButton;
    retryButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/Retry.png");
    retryButton_->position_ = { 750, 450 };
    retryButton_->scale_ = { 1, 1 };
    retryButton_->color_ = { 1, 1, 1, 1 };
    retryButton_->size_ = 1;
    retryButton_->texturePosition_ = { 0, 0 };
    retryButton_->textureSize_ = { 505, 135 };
    retryButton_->hSize_ = { 400, 100 };

    backtotitleButton_ = new BackToTitleButton;
    backtotitleButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/BackToTitle.png");
    backtotitleButton_->position_ = { 750, 650 };
    backtotitleButton_->scale_ = { 1, 1 };
    backtotitleButton_->color_ = { 1, 1, 1, 1 };
    backtotitleButton_->size_ = 1;
    backtotitleButton_->texturePosition_ = { 0, 0 };
    backtotitleButton_->textureSize_ = { 450, 145 };
    backtotitleButton_->hSize_ = backtotitleButton_->textureSize_;
#endif

    // Light\

    // SceneClear
#if 1
    nextButton_ = new NextButton;
    nextButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/Next.png");
    nextButton_->position_ = { 750, 200 };
    nextButton_->scale_ = { 1, 1 };
    nextButton_->color_ = { 1, 1, 1, 1 };
    nextButton_->size_ = 1;
    nextButton_->texturePosition_ = { 0, 0 };
    nextButton_->textureSize_ = { 430, 135 };
    nextButton_->hSize_ = { 430, 135 };

    clearretryButton_ = new ClearRetryButton;
    clearretryButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/Retry.png");
    clearretryButton_->position_ = { 750, 400 };
    clearretryButton_->scale_ = { 1, 1 };
    clearretryButton_->color_ = { 1, 1, 1, 1 };
    clearretryButton_->size_ = 1;
    clearretryButton_->texturePosition_ = { 0, 0 };
    clearretryButton_->textureSize_ = { 505, 135 };
    clearretryButton_->hSize_ = { 505, 135 };

    clearbacktostageButton_ = new ClearBackToStageButton;
    clearbacktostageButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/BackToStage.png");
    clearbacktostageButton_->position_ = { 750, 600 };
    clearbacktostageButton_->scale_ = { 1, 1 };
    clearbacktostageButton_->color_ = { 1, 1, 1, 1 };
    clearbacktostageButton_->size_ = 1;
    clearbacktostageButton_->texturePosition_ = { 0, 0 };
    clearbacktostageButton_->textureSize_ = { 1030, 130 };
    clearbacktostageButton_->hSize_ = { 1030, 130 };

    clearbacktotitleButton_ = new ClearBackToTitleButton;
    clearbacktotitleButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/BackToTitle.png");
    clearbacktotitleButton_->position_ = { 750, 800 };
    clearbacktotitleButton_->scale_ = { 1, 1 };
    clearbacktotitleButton_->color_ = { 1, 1, 1, 1 };
    clearbacktotitleButton_->size_ = 1;
    clearbacktotitleButton_->texturePosition_ = { 0, 0 };
    clearbacktotitleButton_->textureSize_ = { 450, 145 };
    clearbacktotitleButton_->hSize_ = { 450, 145 };
#endif

    // SceneOver
#if 1
    overretryButton_ = new OverRetryButton;
    overretryButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/Retry.png");
    overretryButton_->position_ = { 750, 250 };
    overretryButton_->scale_ = { 1, 1 };
    overretryButton_->color_ = { 1, 1, 1, 1 };
    overretryButton_->size_ = 1;
    overretryButton_->texturePosition_ = { 0, 0 };
    overretryButton_->textureSize_ = { 400, 100 };
    overretryButton_->hSize_ = { 400, 100 };

    overbecktostageButton_ = new OverBackToStageButton;
    overbecktostageButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/BackToStage.png");
    overbecktostageButton_->position_ = { 750, 450 };
    overbecktostageButton_->scale_ = { 1, 1 };
    overbecktostageButton_->color_ = { 1, 1, 1, 1 };
    overbecktostageButton_->size_ = 1;
    overbecktostageButton_->texturePosition_ = { 0, 0 };
    overbecktostageButton_->textureSize_ = { 400, 100 };
    overbecktostageButton_->hSize_ = { 400, 100 };

    overbecktotitleButton_ = new OverBackToTitleButton;
    overbecktotitleButton_->spr_ = graphicEngine->createSprite(L"./Data/Asset/Images/Sprites/BackToTitle.png");
    overbecktotitleButton_->position_ = { 750, 650 };
    overbecktotitleButton_->scale_ = { 1, 1 };
    overbecktotitleButton_->color_ = { 1, 1, 1, 1 };
    overbecktotitleButton_->size_ = 1;
    overbecktotitleButton_->texturePosition_ = { 0, 0 };
    overbecktotitleButton_->textureSize_ = { 400, 100 };
    overbecktotitleButton_->hSize_ = { 400, 100 };

#endif


    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/test.efkefc", "TEST");
    //
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/goal_effect.efkefc", "GOAL");
    //
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/warp_blue.efkefc", "SWAP_BLUE");
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/warp_blue_out.efkefc", "SWAP_BLUE_OUT");
    //
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/warp_purple.efkefc", "SWAP_PURPLE");
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/warp_purple_out.efkefc", "SWAP_PURPLE_OUT");
    //
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/warp_green.efkefc", "SWAP_GREEN");
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/warp_green_out.efkefc", "SWAP_GREEN_OUT");
    //
    //GraphicEngine::get()->createEffect("./Data/Asset/3DObject/Effect/warp_Yellow.efkefc", "SWAP_YELLOW");
}

DataBase::DataBase()
{
    
}


//Rock* DataBase::createRock();
//{
//    if (!rock_) return nullptr;
//    Enemy* e = new Enemy(*enemy_);
//
//    return e;
//}

Background* DataBase::CreateBackground()
{
    Background* back = new Background(*skyBox_);
    return back;
}

Player* DataBase::CreatePlayer(int stage)
{
    Player* p = new Player(*player_);
    p->position_ = playerPos[stage-1];
    return p;
}

// SceneTitle
#if 1
StartButton* DataBase::CreateStartButton()
{
    StartButton* button = nullptr;
    button = new StartButton(*startButton_);
    return button;
}

EndButton* DataBase::CreateEndButton()
{
    EndButton* button = nullptr;
    button = new EndButton(*endButton_);
    return button;
}
#endif

// SceneStage
#if 1
Stage1Button* DataBase::CreateStage1Button()
{
    Stage1Button* button = nullptr;
    button = new Stage1Button(*stage1Button_);
    return button;
}

Stage2Button* DataBase::CreateStage2Button()
{
    Stage2Button* button = nullptr;
    button = new Stage2Button(*stage2Button_);
    return button;
}

Stage3Button* DataBase::CreateStage3Button()
{
    Stage3Button* button = nullptr;
    button = new Stage3Button(*stage3Button_);
    return button;
}
#endif

// Pause
#if 1
ContinueButton* DataBase::CreateContinueButton()
{
    ContinueButton* button = nullptr;
    button = new ContinueButton(*continueButton_);
    return button;
}

RetryButton* DataBase::CreateRetryButton()
{
    RetryButton* button = nullptr;
    button = new RetryButton(*retryButton_);
    return button;
}

BackToTitleButton* DataBase::CreateBackToTitleButton()
{
    BackToTitleButton* button = nullptr;
    button = new BackToTitleButton(*backtotitleButton_);
    return button;
}
#endif

// SceneClear
#if 1
NextButton* DataBase::CreateNextButton()
{
    NextButton* button = nullptr;
    button = new NextButton(*nextButton_);
    return button;
}

ClearRetryButton* DataBase::CreateClearRetryButton()
{
    ClearRetryButton* button = nullptr;
    button = new ClearRetryButton(*clearretryButton_);
    return button;
}

ClearBackToStageButton* DataBase::CreateClearBackToStageButton()
{
    ClearBackToStageButton* button = nullptr;
    button = new ClearBackToStageButton(*clearbacktostageButton_);
    return button;
}

ClearBackToTitleButton* DataBase::CreateClearBackToTitleButton()
{
    ClearBackToTitleButton* button = nullptr;
    button = new ClearBackToTitleButton(*clearbacktotitleButton_);
    return button;
}
#endif

// SceneOver
#if 1
OverRetryButton* DataBase::CreateOverRetryButton()
{
    OverRetryButton* button = nullptr;
    button = new OverRetryButton(*overretryButton_);
    return button;
}

OverBackToStageButton* DataBase::CreateOverBackToStageButton()
{
    OverBackToStageButton* button = nullptr;
    button = new OverBackToStageButton(*overbecktostageButton_);
    return button;
}

OverBackToTitleButton* DataBase::CreateOverBackToTitleButton()
{
    OverBackToTitleButton* button = nullptr;
    button = new OverBackToTitleButton(*overbecktotitleButton_);
    return button;
}
#endif

void DataBase::CreateSpotLight(SpotLight* spotlgt[10],int stageNum)
{
    for (int i = 0; i < 11; i++)
    {
        if (spotLights[i])
        {
            //spotlgt[i] = new SpotLight({ spotLights[i]->position.x,spotLights[i]->position.y,spotLights[i]->position.z },
            //    { spotLights[i]->direction.x, spotLights[i]->direction.y, spotLights[i]->direction.z },
            //    spotLights[i]->color, spotLights[i]->range, spotLights[i]->power, spotLights[i]->innerCorn, spotLights[i]->outerCorn);
            //spotlgt[i]->position.x += mapOffsetPos[stageNum].x;
            //spotlgt[i]->position.y += mapOffsetPos[stageNum].y;
            //spotlgt[i]->position.z += mapOffsetPos[stageNum].z;
        }
        else break;
    }
}

void DataBase::CreatePointLight(PointLight* pointlgt[10], int stageNum)
{
    for (int i = 0; i < 10; i++)
    {
        if (pointLights[i])
        {
            //pointlgt[i] = new PointLight({ pointLights[i]->position.x,pointLights[i]->position.y,pointLights[i]->position.z }, pointLights[i]->color, pointLights[i]->range, pointLights[i]->power);
            //pointlgt[i]->position.x  += mapOffsetPos[stageNum].x;
            //pointlgt[i]->position.y  += mapOffsetPos[stageNum].y;
            //pointlgt[i]->position.z  += mapOffsetPos[stageNum].z;
        }
        else break;
    }
}


DataBase::~DataBase()
{
    SafeDelete(player_);

    SafeDelete(startButton_);
    SafeDelete(endButton_);
    SafeDelete(stage1Button_);
    SafeDelete(stage2Button_);
    SafeDelete(stage3Button_);
    SafeDelete(continueButton_);
    SafeDelete(retryButton_);
    SafeDelete(backtotitleButton_);
    SafeDelete(nextButton_);
    SafeDelete(clearretryButton_);
    SafeDelete(clearbacktostageButton_);
    SafeDelete(clearbacktotitleButton_);
    SafeDelete(overretryButton_);
    SafeDelete(overbecktostageButton_);
    SafeDelete(overbecktotitleButton_);

    SafeDelete(skyBox_);

    for (int i = 0; i < MAX_SUPP_LIGHTS; i++)
    {
        if (pointLights[i])
        {
            SafeDelete(pointLights[i]);
        }
        if (spotLights[i])
        {
            SafeDelete(spotLights[i]);
        }
    }
   
    if (table_)
    {
        SafeDelete(table_);
    }
}
