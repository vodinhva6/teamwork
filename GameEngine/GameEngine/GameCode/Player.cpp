#include "Player.h"
#include "GraphicEngine.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "Scene.h"
#include "AudioManager.h"
Player::Player()
{
    moveSpeed = 5;
    MAXSpeed = 6;
}

void Player::update(float elapsed_time)
{
#ifdef USE_IMGUI
    ImGui::SliderFloat3("Player Pos", &position_.x, -20, 20);
    ImGui::SliderFloat("Player Gravi", &gravityValue, -0.1f, 0);

#endif // USE_IMGUI
    color_ = MyMath::get()->Lerp({ color_.x, color_ .y,color_ .z}, { 1,1,1 }, 0.1f);
    //if (!GraphicEngine::get()->getGameMode())
    //{
    //    //if (CameraManager::get()->getChangedProjection2DView())
    //    //{
    //    //    GravityImpuse(elapsed_time);
    //    //    //if (ControlPad::get()->PressA(0))
    //    //    //{
    //    //    //}
    //    //}
    //    //updateMove(elapsed_time);
    //}
    Charater::update(elapsed_time);
    

    
    //WallRayCast(elapsed_time);
    
    animationUpdate();
    OBJ3D::update(elapsed_time);

}


void Player::draw()
{
    int frameSlot = 1;
    //if (CameraManager::get()->getChangedProjection2DView())
    //    frameSlot = 2;
    VECTOR3 t = { 1,1,1 };
    t.x -= color_.x;
    t.y -= color_.y;
    t.z -= color_.z;
    if (fabsf(t.x) > 0.01f || fabsf(t.y) > 0.01f || fabsf(t.z) > 0.01f)
        frameSlot = 3;
    //GraphicEngine::get()->drawSkinnedMesh(mesh_, worldTransform, color_, animation.key_, drawTurn_, drawStates_, frameSlot);
    //OBJ3D::draw();
    //GraphicEngine::get()->drawCube(position_, roration_, { 1,1,1,1 }, 0.5f, 2, drawStates_);
}



Player::~Player()
{

}

void Player::updateMove(float elapsed_time)
{
    //bool autoMove = !CameraManager::get()->getProjection2DViewNow();
    //{
    //    if (CameraManager::get()->getChangedProjection2DView())
    //    {
    //        inputMove();
    //        jump(elapsed_time);
    //    }
    //}
    

    //updateVerticalHorizoncal(elapsed_time, autoMove);
    

    impluseMoveSpeed(elapsed_time);
}

void Player::AutoGotoPos(const VECTOR3& pos, float elapsedTime)
{

    VECTOR2 dir = { pos.x - position_.x, pos.z - position_.z };
    float dis = MyMath::get()->Length(dir);
    if (dis < 0.1f)
    {
        inputMoveValue.x = 0;
        inputMoveValue.z = 0;
        speed_.x = 0;
        speed_.z = 0;
        return;
    }

    dir = MyMath::get()->Normalize(dir);
    inputMoveValue.x = dir.x;
    inputMoveValue.z = dir.y;
    inputMoveValue *= elapsedTime;
}

void Player::inputMove()
{
   
    //ControlPad* contrPad = ControlPad::get();
    //inputMoveValue.x = contrPad->getPosLeftJoy(0).x * moveSpeed;
    //inputMoveValue.z = contrPad->getPosLeftJoy(0).y * moveSpeed;
    
}

void Player::updateVerticalHorizoncal(float elapsed_timer, bool autoMove)
{
    VECTOR3 cameraForward;// = CameraManager::get()->getGameCameraForwardVector3();
    VECTOR3 cameraRight  ;// = CameraManager::get()->getGameCameraRightVector3();
    cameraForward.y = 0;
    cameraRight.y = 0;
    cameraForward = MyMath::get()->Normalize(cameraForward);
    cameraRight = MyMath::get()->Normalize(cameraRight);
    cameraForward *= inputMoveValue.z * elapsed_timer;
    cameraRight   *= inputMoveValue.x * elapsed_timer;
    DirectX::XMVECTOR Forward = DirectX::XMLoadFloat3(&cameraForward);
    DirectX::XMVECTOR Right = DirectX::XMLoadFloat3(&cameraRight);
    VECTOR3 Vec;
    if (!autoMove)
        DirectX::XMStoreFloat3(&Vec, Forward + Right);
    else
        Vec = inputMoveValue;
    if (MyMath::get()->Length(Vec) <= 0.0f)
    {
        if (!onGround) return;
        else setAnimat(AnimatNum::Idle, 0.6f);
        return;
    }
    RotationTransform(Vec, elapsed_timer);
    speed_.x += Vec.x;
    speed_.z += Vec.z;
    if (fabsf(speed_.x) > MAXSpeed)
        speed_.x = MAXSpeed;
    if (fabsf(speed_.z) > MAXSpeed)
        speed_.z = MAXSpeed;
    if (speed_.x != 0.0f || speed_.z != 0.0f)
    {
        if (!onGround) return;
        else setAnimat(AnimatNum::Run, 1);
    }
}

void Player::jump(float elapsedTimer)
{
    //if (onGround && ControlPad::get()->PressSpace(0))
    //{
    //    AudioManager::get()->play(EFFECT_1, EFFECT_JUMP);
    //    speed_.y += 1.3f;
    //    onGround = false;
    //    setAnimat(AnimatNum::Jump, 1.0f);
    //}
}
