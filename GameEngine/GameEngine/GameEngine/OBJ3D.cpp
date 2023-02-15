#include "OBJ3D.h"
#include "MousePoint.h"
#include "GraphicEngine.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "Scene.h"
#include "Audio.h"
#include "DataBase.h"

OBJ3D::OBJ3D()
{
    deadFlag = false;
    damageFlag = false;
    scale_ = { 1,1,1 };
    size_ = 1;
    color_ = { 1,1,1,1 };
}

OBJ3D::OBJ3D(const OBJ3D* data)
{
    this->mesh_ = data->mesh_;
    this->oldPosition_ = data->oldPosition_;
    this->position_ = data->position_;
    this->speed_ = data->speed_;
    this->rotation_ = data->rotation_;
    this->speedRotation_ = data->speedRotation_;
    this->color_ = data->color_;
    this->animation = data->animation;
    this->scale_ = data->scale_;
    this->size_ = data->size_;
    this->timer = data->timer;
    this->gravityValue = data->gravityValue;
    this->drawStates_ = data->drawStates_;
    this->worldTransform = data->worldTransform;
    this->offSet_ = data->offSet_;

    this->damageFlag = data->damageFlag;
    this->deadFlag = data->deadFlag;
    this->drawTurn_ = data->drawTurn_;
    this->hSizeMax_ = data->hSizeMax_;
    this->hSizeMin_ = data->hSizeMin_;
    this->boundingHit_ = data->boundingHit_;
    
}

void OBJ3D::setAnimat(AnimatNum ani, float frame)
{
    if (animation.trigger)
        return;
    if (animation.animat == &mesh_->animation_clips.at(ani))
        return;
    animation.oldanimat = animation.animat;
    animation.oldFrameStepSpeed = animation.frameStepSpeed;
    animation.animat = &mesh_->animation_clips.at(ani);
    animation.frameStepSpeed = frame;
    animation.animationFrame = animation.animat->sequence.size();
    animation.animatitonTimer = 0;
}

void OBJ3D::init()
{
    timer = 0;
}

void OBJ3D::update(float elapsed_time)
{
    updateWorldTrans();
    timer++;
}

void OBJ3D::draw()
{
    if(mesh_)
        GraphicEngine::get()->drawSkinnedMesh(mesh_, worldTransform, color_,nullptr, drawTurn_, drawStates_,0);
    if (sprite3D_)
        GraphicEngine::get()->drawSprite3D(sprite3D_, worldTransform, color_, 1);
}

void OBJ3D::release()
{

}

void OBJ3D::updateWorldTrans()
{
    DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(size_ * scale_.x,size_ * scale_.y,size_ * scale_.z) };
    DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(rotation_.x), DirectX::XMConvertToRadians(rotation_.y), DirectX::XMConvertToRadians(rotation_.z)) };
    DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z) };
     
    DirectX::XMStoreFloat4x4(&worldTransform, S * R * T); 
}

void OBJ3D::updateWorldTrans(DirectX::XMFLOAT4X4& transform)
{
    DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(size_ * scale_.x,size_ * scale_.y,size_ * scale_.z) };
    DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(rotation_.x), DirectX::XMConvertToRadians(rotation_.y), DirectX::XMConvertToRadians(rotation_.z)) };
    DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z) };

    DirectX::XMStoreFloat4x4(&worldTransform, S * R * T * DirectX::XMLoadFloat4x4(&transform));
}

OBJ3DType OBJ3D::getTypeOBJ3D()
{
    return OBJ3DType::NON;
}

void OBJ3D::drawDebug()
{
    if (boundingHit_.sphere_)
        GraphicEngine::get()->drawDebugBounding(boundingHit_.sphere_, worldTransform, color_,2);
    if (boundingHit_.capsule_)
        GraphicEngine::get()->drawDebugBounding(boundingHit_.capsule_, worldTransform, color_,3);
    for (auto& ray : boundingHit_.raylist)
    {
        if (ray)
        {
            GraphicEngine::get()->drawDebugBounding(ray, worldTransform, ray->color, 3);
        }
    }
}


OBJ3D::~OBJ3D()
{

}


void OBJ3D::CreateBoundingCapsule(const float& height, const float& weight, const VECTOR3& offset)
{
    boundingHit_.capsule_ = GraphicEngine::get()->createCapsuleDebug(height, weight, offset);
}

void OBJ3D::CreateBoundingSphere(const float& radius, const VECTOR3& offset)
{
    boundingHit_.sphere_ = GraphicEngine::get()->createSphereDebug(radius, offset);
}

void OBJ3D::CreateRay(const VECTOR3& begin, const VECTOR3& end, const VECTOR4& color, RayType Type)
{
    boundingHit_.raylist.push_back(GraphicEngine::get()->createRay(begin, end, color, Type));
}
