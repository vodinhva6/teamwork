#pragma once
#include "OBJ2D.h"
#include "DebuggerMouse.h"

class MousePoint 
{
public:

    MousePoint(const HWND* hwnd);
    void update();
    float getCulPos()
    {
        return mousePosition.x - oldPos.x;
    }
    bool onClick();
    bool HoldClick();
    void draw();
    void setStopSetWheelValue(bool set) { stopSetWheelValue = set; }
    void setFirstPersonMouseNotShow(bool set) { firstPersonMouseNotShow = set; }
    bool getFirstPersonMouseNotShow() { return firstPersonMouseNotShow; }
    bool getStopWheelValue() { return stopSetWheelValue; }
    bool onTrigger(const OBJ2D&);
    bool onTriggerNoMoveEnble(const OBJ2D&);
    bool onClickTrigger(const OBJ2D&);
    bool onMove();
    void setEnable(bool ena) { enableUsing = ena; }
    void resetPosition();
    VECTOR2 getPos()
    {
        return mousePosition;
    }
    VECTOR2 getOldPos()
    {
        return oldPos;
    }
    POINT getPosLong()
    {
        return point_;
    }
    VECTOR2 getIns()
    {
        
            return mousePosition - oldPos;
    }

    float getWheelValue() { return wheelValue; }
    void setWheelValue(float value) { wheelValue = value; }
    void setWheel(float wheel) { wheel_ = wheel; }
    const HWND* hwnd;
    ~MousePoint();
protected:
    void init(const HWND* hwnd);
    void NotUsingMouseNow();
    void resetCountDown();
    int notUingMouseTimer;
    bool mouseInHere(const VECTOR2& mousPos, const OBJ2D& here);
    void wheelSet();
    bool enableUsing;
    VECTOR2 oldPos;
    POINT point_;
    bool smooth;
    VECTOR2 mousePosition;
    Sprite* mouse;
    float oldWheel_;
    float wheel_;
    bool stopSetWheelValue;
    float wheelValue;
    bool firstPersonMouseNotShow;
};
