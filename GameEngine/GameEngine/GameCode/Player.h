#pragma once
#include "Charater.h"

class Player :public Charater
{
public:
    Player();
    virtual OBJ3DType getTypeOBJ3D() override { return OBJ3DType::PLAYER; }
    void update(float elapsed_time) override;
    void draw() override;
    void updateMove(float elapsed_time) override;
    bool getOnGround() { return onGround; }
    void AutoGotoPos(const VECTOR3& pos, float elapsedTime);
    ~Player() override;
    int runUptimer = 0;
private:
    void inputMove();
    void updateVerticalHorizoncal(float elapsed_timer, bool autoMove);
    void jump(float elapsedTimer);
    VECTOR3 inputMoveValue;
    
    float moveSpeed;
    float MAXSpeed;
};


