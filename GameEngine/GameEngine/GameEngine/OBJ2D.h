#pragma once
#include "Sprite.h"

enum ButtonName1
{
    Continue,
    Retry,
    StageMenu,
    Home,
    Next,
    NewGame,
    LoadGame,
    ControlerSetting,
    Exit
};


enum Table
{
    Move,
    TouchTuto,
    Camera,
    Reset,
    BlockIntro,
    TouchIntro,
    Clear,
};

class OBJ2D
{
public:
    OBJ2D();
    Sprite* spr_;
    VECTOR2 position_;
    VECTOR2 speed_;
    float size_;
    VECTOR2 scale_;
    VECTOR2 texturePosition_;
    VECTOR2 textureSize_;
    VECTOR2 hSize_;
    VECTOR4 color_;


    int timer;


    virtual void update();
    virtual void draw();


    ~OBJ2D();
};

class TutorialTable : public OBJ2D
{
public:
    TutorialTable();
    void init();
    void update() override;
    void setActive(bool acti) { active = acti; }
    void setUsed(bool use) { used = use; }
    void setGoOut(bool out) { goOut = out; }

    bool getActive() { return active; }
    bool getUsed() { return used; }

    ~TutorialTable();
private:
    bool active;
    bool used;
    bool goOut;
};


class Button : public OBJ2D
{
public:
    Button();
    void update() override;
    void draw() override;
    void setUnlock(bool acti) { unlocked = acti; }
    void setSele(bool sele) { selected = sele; }
    bool getUnlock() { return unlocked; }
    ~Button();
protected:

    bool selected;
    bool unlocked;
};

// SceneTitle
#if 1
class TitleButton : public Button
{
public:
    TitleButton();
    void update() override;
    void draw() override;
    ~TitleButton();
};

class StartButton : public TitleButton
{
public:
    StartButton();
    void update() override;
    void draw() override;
    ~StartButton();
};

class EndButton : public TitleButton
{
public:
    EndButton();
    void update() override;
    void draw() override;
    ~EndButton();
};
#endif

// SceneStage
#if 1
class StageButton : public Button
{
public:
    StageButton();
    void update() override;
    void draw() override;
    int getStarNum() { return clearStar_; }
    void setStarNum(int num) { clearStar_ = num; }
    Sprite* starSpr;
protected:
    int clearStar_;
    int stageNum;
};

class Stage1Button : public StageButton
{
public:
    Stage1Button();
    void update() override;
    void draw() override;
    ~Stage1Button();
};

class Stage2Button : public StageButton
{
public:
    Stage2Button();
    void update() override;
    void draw() override;
    ~Stage2Button();
};

class Stage3Button : public StageButton
{
public:
    Stage3Button();
    void update() override;
    void draw() override;
    ~Stage3Button();
};
#endif

// Pause
#if 1
class PauseButton : public Button
{
public:
    PauseButton();
    void update() override;
    void draw() override;
    ~PauseButton();
};

class ContinueButton : public PauseButton
{
public:
    ContinueButton();
    void update() override;
    void draw() override;
    ~ContinueButton();
};

class RetryButton : public PauseButton
{
public:
    RetryButton();
    void update() override;
    void draw() override;
    ~RetryButton();
};

class BackToTitleButton : public PauseButton
{
public:
    BackToTitleButton();
    void update() override;
    void draw() override;
    ~BackToTitleButton();
};
#endif

//SceneGame
class Stage2D : public OBJ2D
{
public:
    void update() override {};
};

// SceneClear
#if 1
class ClearButton : public Button
{
public:
    ClearButton();
    void update() override;
    void draw() override;
    ~ClearButton();
};

class NextButton : public ClearButton
{
public:
    NextButton();
    void update() override;
    void draw() override;
    ~NextButton();
};

class ClearRetryButton : public ClearButton
{
public:
    ClearRetryButton();
    void update() override;
    void draw() override;
    ~ClearRetryButton();
};

class ClearBackToStageButton : public ClearButton
{
public:
    ClearBackToStageButton();
    void update() override;
    void draw() override;
    ~ClearBackToStageButton();
};

class ClearBackToTitleButton : public ClearButton
{
public:
    ClearBackToTitleButton();
    void update() override;
    void draw() override;
    ~ClearBackToTitleButton();
};
#endif

// SceneOver
#if 1
class OverButton : public Button
{
public:
    OverButton();
    void update() override;
    void draw() override;
    ~OverButton();
};

class OverRetryButton : public OverButton
{
public:
    OverRetryButton();
    void update() override;
    void draw() override;
    ~OverRetryButton();
};

class OverBackToStageButton : public OverButton
{
public:
    OverBackToStageButton();
    void update() override;
    void draw() override;
    ~OverBackToStageButton();
};

class OverBackToTitleButton : public OverButton
{
public:
    OverBackToTitleButton();
    void update() override;
    void draw() override;
    ~OverBackToTitleButton();
};
#endif

class ControllerSelectButton : public Button
{
public:
    ControllerSelectButton();
    void update() override;
    void draw() override;
    ~ControllerSelectButton();
};

class StageNumber : public OBJ2D
{
public:

    void update() override;

};
