#include "Charater.h"
#include "ObjectManager.h"
#include "GraphicEngine.h"
#include "Collision.h"
Charater::Charater()
{
    rotationSpeed = 30.0f;
    onGround = false;
    takingBool = false;
}

void Charater::update(float elapsed_time)
{    

    //if (CameraManager::get()->getChangedProjection2DView())
    //{
    //  
    //}
}

void Charater::animationUpdate()
{
    //if (animation.animat == nullptr)
    //{
    //    return;
    //}
    //else animation.animatitonTimer++;
    //int tmp = static_cast<int>(animation.animatitonTimer * animation.frameStepSpeed) % animation.animationFrame;
    //animation.key_ = &animation.animat->sequence.at(tmp);
    //int upLimitTime = static_cast<int>(animation.animationFrame / animation.frameStepSpeed);
    //if (animation.animatitonTimer >= upLimitTime)
    //{
    //    animation.animat = animation.oldanimat;
    //    animation.frameStepSpeed = animation.oldFrameStepSpeed;
    //    animation.animationFrame = animation.animat->sequence.size();
    //    animation.animatitonTimer = 0;
    //    animation.trigger = false;
    //}
}

Charater::~Charater()
{
}

void Charater::RotationTransform(const VECTOR3& direction, float elapsedTime)
{
    VECTOR3 Forward = {
        worldTransform._31,
        worldTransform._32,
        worldTransform._33,
    };
    float angle = MyMath::get()->AngleBetweenVectorReturnDegrees(Forward, direction);
    if (fabsf(angle) <= 5)
        return;
    rotation_.y += angle * rotationSpeed * elapsedTime;

}


void Charater::draw()
{

}

void Charater::updateMove(float elapsed_time)
{

}

void Charater::GravityImpuse(float elapsed_time)
{
    static float gravityRate = 0.06f;
#ifdef USE_IMGUI
    ImGui::SliderFloat("gravityRate", &gravityRate, 0, 0.2f);
#endif
    speed_.y += gravityValue;
    if (speed_.y < 0)
        speed_.y += speed_.y * gravityRate;
}

void Charater::VerticalUpdate(float elapsed_time)
{

}

void Charater::HorizoncalUpdate(float elapsed_time)
{

}


void Charater::impluseMoveSpeed(float elapsed_time)
{
    position_ += speed_;
    rotation_ += speedRotation_;
    speed_.x *= 0.75f;
    speed_.z *= 0.75f;

}
