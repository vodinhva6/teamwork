#include "OBJ2D.h"
#include "MyMath.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "SceneManager.h"

OBJ2D::OBJ2D()
{
    timer = 0;
    spr_ = nullptr;
}

void OBJ2D::update()
{
    timer++;
}

void OBJ2D::draw()
{
    GraphicEngine::get()->drawSpriteLate(spr_, position_, scale_, color_, texturePosition_, textureSize_, 0, 10);
}

OBJ2D::~OBJ2D()
{

}

Button::Button()
{
}

void Button::update()
{

}

void Button::draw()
{
}

Button::~Button()
{
}

// SceneTitle
#if 1
TitleButton::TitleButton()
{
}

void TitleButton::update()
{
    if (!unlocked)
        color_ = { 0.3f,0.3f,0.3f,1 };
    else color_ = { 1,1,1,1 };
}

void TitleButton::draw()
{
    GraphicEngine::get()->drawSpriteLate(spr_, position_, scale_ * size_, color_, { texturePosition_.x, textureSize_.y }, textureSize_, 0, 10);
}

TitleButton::~TitleButton()
{
}

StartButton::StartButton()
{
}

void StartButton::update()
{
    if (InputManager::get()->getMousePoint()->onClickTrigger(*this))
    {
        SceneManager::get()->changeScene(SCENEGAME, 0);
    }
    if (InputManager::get()->getMousePoint()->onTriggerNoMoveEnble(*this))
    {
        color_ = { 0.5f, 0.5f, 0.5f, 1 };
    }
    else color_ = { 1, 1, 1, 1 };
}

void StartButton::draw()
{
    TitleButton::draw();
}

StartButton::~StartButton()
{
}

EndButton::EndButton()
{
}

void EndButton::update()
{
    if (InputManager::get()->getMousePoint()->onClickTrigger(*this))
    {
        GraphicEngine::get()->setExitGame(true);
    }
    if (InputManager::get()->getMousePoint()->onTriggerNoMoveEnble(*this))
    {
        color_ = { 0.5f, 0.5f, 0.5f, 1 };
    }
    else color_ = { 1, 1, 1, 1 };
}

void EndButton::draw()
{
    TitleButton::draw();
}

EndButton::~EndButton()
{
}
#endif

// SceneStage
#if 1
StageButton::StageButton()
{
    clearStar_ = 0;
    unlocked = false;
}

void StageButton::update()
{
    OBJ2D::update();
    if (!unlocked)
        color_ = { 0.5f,0.5f,0.5f,1 };
    else color_ = { 1,1,1,1 };
    if (selected)
        size_ = 1.5f;
    
}

void StageButton::draw()
{
    GraphicEngine::get()->drawSpriteLate(spr_, position_, scale_, color_, texturePosition_, textureSize_, 0, 1);
    
    for (int i = 0; i < clearStar_; i++)
    {
        VECTOR2 pos = { position_.x + 6.5f + 64*i,position_.y + 115.0f };
        GraphicEngine::get()->drawSpriteLate(starSpr, pos, scale_ , color_, { 0,0 }, { 60,60 }, 0, 1);
    }
    
}

// Stage1
Stage1Button::Stage1Button()
{
    stageNum = 1;
}

void Stage1Button::update()
{
#ifdef _DEBUG
    ImGui::InputInt("stage", &stageNum);
#endif // _DEBUG

    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENEGAME, 0);
    //    SceneManager::get()->setStage(stageNum);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void Stage1Button::draw()
{
    StageButton::draw();
}

Stage1Button::~Stage1Button()
{

}

// Stage2
Stage2Button::Stage2Button()
{
    stageNum = 2;
}

void Stage2Button::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENEGAME, 0);
    //    SceneManager::get()->setStage(stageNum);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void Stage2Button::draw()
{
    StageButton::draw();
}

Stage2Button::~Stage2Button()
{

}

// Stage3
Stage3Button::Stage3Button()
{
    stageNum = 3;
}

void Stage3Button::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENEGAME, 0);
    //    SceneManager::get()->setStage(stageNum);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void Stage3Button::draw()
{
    StageButton::draw();
}

Stage3Button::~Stage3Button()
{

}
#endif

// Pause
#if 1
PauseButton::PauseButton()
{
}

void PauseButton::update()
{
    timer++;
}

void PauseButton::draw()
{
    GraphicEngine::get()->drawSpriteLate(spr_, position_, scale_, color_, { texturePosition_.x, textureSize_.y * selected }, textureSize_, 0, 10);
}

PauseButton::~PauseButton()
{
}

ContinueButton::ContinueButton()
{
}

void ContinueButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->getSceneNow()->setPause(false);
    //    
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void ContinueButton::draw()
{
    PauseButton::draw();
}

ContinueButton::~ContinueButton()
{
}

RetryButton::RetryButton()
{
}

void RetryButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->getSceneNow()->setgameReset(true);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void RetryButton::draw()
{
    PauseButton::draw();
}

RetryButton::~RetryButton()
{
}

BackToTitleButton::BackToTitleButton()
{
}

void BackToTitleButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENETITLE, 0);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void BackToTitleButton::draw()
{
    PauseButton::draw();
}

BackToTitleButton::~BackToTitleButton()
{
}
#endif

// SceneClear
#if 1
ClearButton::ClearButton()
{
}

void ClearButton::update()
{
}

void ClearButton::draw()
{
    GraphicEngine::get()->drawSpriteLate(spr_, position_, scale_ * size_, color_, { texturePosition_.x, textureSize_.y * selected }, textureSize_, 0, 10);
}

ClearButton::~ClearButton()
{
}

NextButton::NextButton()
{
}

void NextButton::update()
{
    //if (SceneManager::get()->getStage() < 10)
    //{
    //    if (MousePoint::get()->onClickTrigger(*this))
    //    {
    //        SceneManager::get()->setStage(SceneManager::get()->getStage() + 1);
    //        SceneManager::get()->changeScene(SCENEGAME, 0);
    //    }
    //    if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //    {
    //        color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //    }
    //    else color_ = { 1, 1, 1, 1 };
    //}
}

void NextButton::draw()
{
    //if (SceneManagerOld::get()->getStage() < 10)
    //{
    //    ClearButton::draw();
    //}
}

NextButton::~NextButton()
{
}

ClearRetryButton::ClearRetryButton()
{
}

void ClearRetryButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENEGAME, 0);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void ClearRetryButton::draw()
{
    ClearButton::draw();
}

ClearRetryButton::~ClearRetryButton()
{
}

ClearBackToStageButton::ClearBackToStageButton()
{
}

void ClearBackToStageButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENESTAGE, 0);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void ClearBackToStageButton::draw()
{
    ClearButton::draw();
}

ClearBackToStageButton::~ClearBackToStageButton()
{
}

ClearBackToTitleButton::ClearBackToTitleButton()
{
}

void ClearBackToTitleButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENETITLE, 0);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void ClearBackToTitleButton::draw()
{
    ClearButton::draw();
}

ClearBackToTitleButton::~ClearBackToTitleButton()
{
}
#endif

// SceneOver
#if 1
OverButton::OverButton()
{
}

void OverButton::update()
{
}

void OverButton::draw()
{
    GraphicEngine::get()->drawSpriteLate(spr_, position_, scale_ * size_, color_, { texturePosition_.x, textureSize_.y * selected }, textureSize_, 0, 10);
}

OverButton::~OverButton()
{

}

OverRetryButton::OverRetryButton()
{
}

void OverRetryButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENEGAME, 0);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void OverRetryButton::draw()
{
    OverButton::draw();
}

OverRetryButton::~OverRetryButton()
{
}

OverBackToStageButton::OverBackToStageButton()
{
}

void OverBackToStageButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENESTAGE, 0);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void OverBackToStageButton::draw()
{
    OverButton::draw();
}

OverBackToStageButton::~OverBackToStageButton()
{
}

OverBackToTitleButton::OverBackToTitleButton()
{
}

void OverBackToTitleButton::update()
{
    //if (MousePoint::get()->onClickTrigger(*this))
    //{
    //    SceneManager::get()->changeScene(SCENETITLE, 0);
    //}
    //if (MousePoint::get()->onTriggerNoMoveEnble(*this))
    //{
    //    color_ = { 0.5f, 0.5f, 0.5f, 1 };
    //}
    //else color_ = { 1, 1, 1, 1 };
}

void OverBackToTitleButton::draw()
{
    OverButton::draw();
}

OverBackToTitleButton::~OverBackToTitleButton()
{
}
#endif

ControllerSelectButton::ControllerSelectButton()
{
}

void ControllerSelectButton::update()
{
    if (selected)
    {
        float val = fabsf(cosf(MyMath::get()->convertToRadian(timer)));
        color_.x = 0.5f + val;
        color_.y = 0.5f + val;
        color_.z = 0.5f + val;
    }
    else
    {
        color_.x = 0.8f ;
        color_.y = 0.8f ;
        color_.z = 0.8f ;
    }
        timer++;
}

void ControllerSelectButton::draw()
{
    GraphicEngine::get()->drawSpriteLate(spr_, position_, scale_ * size_, color_, { texturePosition_.x, textureSize_.y * selected }, textureSize_, 0, 10);
}

ControllerSelectButton::~ControllerSelectButton()
{
}

void StageNumber::update()
{
    position_ += speed_;
    speed_ *= 0.98f;
    if (speed_.y -0.01f <= 0.0001f)
        speed_.y = -10.0f;
}

TutorialTable::TutorialTable()
{
    active = false;
    used = false;
    goOut = false;
}

void TutorialTable::init()
{
    position_ = { -800, 250 };
    scale_ = { 0.3f,0.3f };
    speed_ = { 17,0 };
    active = false;
    used = false;
    goOut = false;
}

void TutorialTable::update()
{
    position_ += speed_;
    scale_ *= 1.01f;
    scale_.x = clamp(scale_.x, 0.3f, 1.0f);
    scale_.y = clamp(scale_.y, 0.3f, 1.0f);
    speed_ *= 0.98f;
    if (speed_.x - 0.01f <= 0.0001f || goOut)
    {
        speed_.x = -20.0f;
        scale_ /= 1.02f;
    }
}

TutorialTable::~TutorialTable()
{
}
