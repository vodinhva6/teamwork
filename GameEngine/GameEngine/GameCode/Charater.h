#pragma once
#include "OBJ3D.h"
class Charater : public OBJ3D
{
public:
    Charater();
    virtual OBJ3DType getTypeOBJ3D() override { return OBJ3DType::CHARATER; }
    virtual void update(float elapsed_time) override;
    virtual void draw() override;
    virtual void animationUpdate();
    virtual  ~Charater() override;
    void RotationTransform(const VECTOR3& direction, float elapsedTime);
protected:
    virtual void updateMove(float elapsed_time);
    bool onGround;
    virtual void impluseMoveSpeed(float elapsed_time);
    void GravityImpuse(float elapsed_time);
    bool takingBool;
private:
    void VerticalUpdate(float elapsed_time);
    void HorizoncalUpdate(float elapsed_time);
    float rotationSpeed;
};