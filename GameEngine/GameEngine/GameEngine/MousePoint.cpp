#include "MousePoint.h"
#include "Audio.h"
#include "InputManager.h"
#include "GraphicEngine.h"
MousePoint::MousePoint(const HWND* hwnd)
{
    init(hwnd);
    //mouse = GraphicEngine::get()->createSprite(L"./Data/Asset/Images/Mouse/cursor.png");
#if _DEBUG
    //DebuggerMouse::get()->init();
#endif // _DEBUG

    wheel_ = 0;
    notUingMouseTimer = 300;
    firstPersonMouseNotShow = false;
}

void MousePoint::update()
{
    NotUsingMouseNow();
#if !(_DEBUG)
    //ShowCursor(false);
#endif


    GetCursorPos(&point_);
    ScreenToClient(*hwnd, &point_);
    oldPos = mousePosition;
    mousePosition = { static_cast<float>(point_.x),static_cast<float>(point_.y) };
    wheelSet();
    oldWheel_ = 0;

#if _DEBUG
    //DebuggerMouse::get()->update();
    ImGui::SliderFloat2("mouse Position", &mousePosition.x, 0, 1);
#endif // _DEBUG
}


void MousePoint::init(const HWND* hwnd)
{
    this->hwnd = hwnd;
}

bool MousePoint::onClick()
{
    bool a = InputManager::get()->getControlPad()->PressA(0);
    if (a)
    {
        resetCountDown();
        //AudioManager::get()->play(EFFECT, EFFECT_SELECT);
    }
    return a;
}

bool MousePoint::HoldClick()
{
    bool a = InputManager::get()->getControlPad()->HoldeA(0);
    if (a)
    {
        resetCountDown();
        //AudioManager::get()->play(EFFECT, EFFECT_SELECT);
    }
    return a;
}

void MousePoint::draw()
{
    
#if _DEBUG
    //DebuggerMouse::get()->draw();
#else
    VECTOR2 offset = { 32,17 };
    GraphicEngine::get()->drawSpriteLate(mouse, mousePosition - offset, { 1.0f,1.0f }, { 1,1,1,1 }, { 0,0 }, { 100,100 }, 0, 10);
#endif // !_DEBUG

}
bool MousePoint::onTrigger(const OBJ2D& here)
{
    if (oldPos == mousePosition)
        return false;
    return mouseInHere(mousePosition, here);
}

bool MousePoint::onTriggerNoMoveEnble(const OBJ2D& here)
{
    return mouseInHere(mousePosition, here);
}

bool MousePoint::onClickTrigger(const OBJ2D& here)
{
    if (InputManager::get()->getControlPad()->PressA(0))
    {
        return mouseInHere(mousePosition, here);
        resetCountDown();
    }
        
    return false;
}

bool MousePoint::onMove()
{
    float dx = oldPos.x - mousePosition.x;
    float dy = oldPos.y - mousePosition.y;
    return (fabsf(dx) > 1.0f || fabsf(dy) > 10.0f );
}

void MousePoint::resetPosition()
{
    SetCursorPos(1920 / 2, 1080 / 2);
    GetCursorPos(&point_);
    ScreenToClient(*hwnd, &point_);
    mousePosition = { static_cast<float>(point_.x),static_cast<float>(point_.y) };
    oldPos = mousePosition;
}




MousePoint::~MousePoint()
{
    //delete DebuggerMouse::get();
}

void MousePoint::NotUsingMouseNow()
{
    if (oldPos == mousePosition)
        notUingMouseTimer--;
    else
    {
        resetCountDown();
    }
    if (notUingMouseTimer < 0)
        notUingMouseTimer = 0;
}

void MousePoint::resetCountDown()
{
    notUingMouseTimer = 300;
}

bool MousePoint::mouseInHere(const VECTOR2& mousPos, const OBJ2D& here)
{
    if (mousPos.x > here.position_.x && mousPos.x < here.position_.x + here.hSize_.x)
        if (mousPos.y > here.position_.y && mousPos.y < here.position_.y + here.hSize_.y)
            return true;
    return false;
}

void MousePoint::wheelSet()
{
    //ControlPad* conPad = ControlPad::get();
    //bool usingPad = false;
    //float subValue = 0;
   ///* if (conPad->getUsingControler())
    //    usingPad = true;*/
    //if (usingPad)
    //{
    //    float rightJoyY = conPad->getPosRightJoy(0).y;
    //    wheelValue += rightJoyY;
    //    if (rightJoyY == 0)
    //        subValue = 0.8f;
    //    else
    //    {
    //        subValue = 0.1f * rightJoyY;
    //    }
    //}
    //else
    //{
    //    if (wheel_ - oldWheel_ < 0)
    //    {
    //        wheelValue += -15;
    //        if (wheelValue < -30)
    //            wheelValue = -30;
    //    }
    //    else
    //        if (wheel_ - oldWheel_ > 0)
    //        {
    //            wheelValue += 15;
    //            if (wheelValue > 30)
    //                wheelValue = 30;
    //        }
    //    subValue = 1;
    //}
    //if (stopSetWheelValue)
    //    wheelValue = 0;
    //if (wheelValue < 0)
    //{
    //    wheelValue += subValue;
    //    if (wheelValue > 0)
    //        wheelValue = 0;
    //}
    //else
    //    if (wheelValue > 0)
    //    {
    //        wheelValue -= subValue;
    //        if (wheelValue < 0)
    //            wheelValue = 0;
    //    }
    //
    //stopSetWheelValue = false;
   
}
