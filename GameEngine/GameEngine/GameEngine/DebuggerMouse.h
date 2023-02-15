#pragma once
#include "OBJ3D.h"
class DebuggerArrow;
class DebuggerMouse
{
public:
    void init();
    void update();
    void draw();
    ~DebuggerMouse();
private:
    void getTagert();
    bool setTagert();
    bool transforming();
    bool scaling();
    bool rotationning();

    DebuggerArrow* UpArrow_;
    DebuggerArrow* RightArrow_;
    DebuggerArrow* ForwardArrow_;
    
    DebuggerArrow* tagertArrow;
    OBJ3D* tagert;
    int sele;
};

class DebuggerArrow : public OBJ3D
{
public:
    VECTOR3 dir = { 0,0,0 };
    void draw() override;
private:

};