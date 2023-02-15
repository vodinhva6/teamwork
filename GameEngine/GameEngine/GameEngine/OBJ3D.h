#pragma once
#ifndef OBJ3D_H
#define OBJ3D_H
#include "Sprite3D.h"
#include "GeometricPrimitive.h"
#include "ShaderManager.h"
#include "SkinnedMesh.h"
#include "DataFormat.h"
#include "ControlPad.h"
#include "MyMath.h"
#include "BoundingInfor.h"

enum class OBJ3DType
{
    NON,
    CHARATER,
    PLAYER,
    ENEMY,
    BLOCK,
    EEND,
    ALLY,
};
enum AnimatNum
{
    Idle,
    Run,
    Jump,
    TakingMove,
    PushFoward,
    TakingIdle,
    ClearSisei,

};

class OBJ3D
{
public:
    OBJ3D();
    OBJ3D(const OBJ3D*);
    void setAnimat(AnimatNum, float);
    virtual ~OBJ3D();
    void CreateBoundingCapsule(const float& height, const float& weight, const VECTOR3& offset);
    void CreateBoundingSphere(const float& radius, const VECTOR3& offset);
    void CreateRay(const VECTOR3& begin, const VECTOR3& end,const VECTOR4& color, RayType Type);
public:

    virtual void init();
    virtual void update(float elapsed_time);
    virtual void draw();
    virtual void release();
    virtual void updateWorldTrans();
    virtual void updateWorldTrans(DirectX::XMFLOAT4X4& transform);
    virtual OBJ3DType getTypeOBJ3D();
    virtual void drawDebug();


public:
    VECTOR3 position_;
    VECTOR3 oldPosition_;
    VECTOR3 rotation_;
    VECTOR3 offSet_;
    VECTOR3 speedRotation_;
    VECTOR3 scale_;
    VECTOR3 hSizeMin_;
    VECTOR3 hSizeMax_;
    VECTOR3 speed_;
    VECTOR4 color_;

    float size_;
    int timer;
    int drawTurn_;
    float gravityValue;
    bool deadFlag;
    bool damageFlag;

    DirectX::XMFLOAT4X4 worldTransform =
    { 1,0,0,0,
     0,1,0,0,
     0,0,1,0,
     0,0,0,1 };
  
public:

    struct Animation
    {
        SkinnedMesh::animation* animat;
        SkinnedMesh::animation* oldanimat;
        SkinnedMesh::animation::keyframe* key_;
        bool trigger;
        size_t animationFrame;
        size_t animatitonTimer;
        float frameStepSpeed;
        float oldFrameStepSpeed;
    };
    Animation animation;
    DrawStates drawStates_;
    Bounding boundingHit_;

    SkinnedMesh* mesh_;
    Sprite3D* sprite3D_;
   
};
#endif // !OBJ3D_H

