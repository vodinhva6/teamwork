#include "DebuggerMouse.h"
#include "Collision.h"
#include "ObjectManager.h"
#include "GraphicEngine.h"
#include "MousePoint.h"
#include "CameraManager.h"
void DebuggerMouse::init()
{
    ShaderData shaderData = { "./Data/Shaders/skinned_mesh_vs.cso", "./Data/Shaders/skinned_mesh_ps.cso" };
    UpArrow_ = new DebuggerArrow;
    //UpArrow_->mesh_ = GraphicEngine::get()->createSkinnedMesh("./EngineObject/arrow.fbx", true, SkinnedMeshObjectAxis::DEFAULT, shaderData, {0,-1,0});
    UpArrow_->dir = { 0,1,0 };
    UpArrow_->color_ = { 0,1,0,1 };
    UpArrow_->position_ = { 0,0,0 };
    UpArrow_->rotation_ = { 0,0,180 };
    
    RightArrow_ = new DebuggerArrow;
    //RightArrow_->mesh_ = UpArrow_->mesh_;
    RightArrow_->dir = { 1,0,0 };
    RightArrow_->color_ = { 1,0,0,1 };
    RightArrow_->position_ = { 0,0,0 };
    RightArrow_->rotation_ = { 0,0,90 };
    
    ForwardArrow_ = new DebuggerArrow;
    //ForwardArrow_->mesh_ = RightArrow_->mesh_;
    ForwardArrow_->dir = { 0,0,1 };
    ForwardArrow_->color_ = { 0,0,1,1 };
    ForwardArrow_->position_ = { 0,0,0 };
    ForwardArrow_->rotation_ = { -90,0,0 };
    
    UpArrow_->size_ = RightArrow_->size_ = ForwardArrow_->size_ = 1;
    UpArrow_->scale_ = RightArrow_->scale_ = ForwardArrow_->scale_ = { 1,1,1 };

    tagert = nullptr;
    tagertArrow = nullptr;
    sele = 0;
}

void DebuggerMouse::update()
{
    //if (ControlPad::get()->PressT(0))
    //    sele = 0;
    //if (ControlPad::get()->PressS(0))
    //    sele = 1;
    //if(ControlPad::get()->PressR(0))
    //    sele = 2;
    //if(!setTagert())
    //getTagert();
    //if (tagert)
    //{
    //    UpArrow_->position_ = RightArrow_->position_ = ForwardArrow_->position_ = tagert->position_;
    //    UpArrow_->updateWorldTrans();
    //    RightArrow_->updateWorldTrans();
    //    ForwardArrow_->updateWorldTrans();
    //    
    //}

}

void DebuggerMouse::draw()
{
    if (tagert)
    {
        UpArrow_->draw();
        RightArrow_->draw();
        ForwardArrow_->draw();
    }
}

DebuggerMouse::~DebuggerMouse()
{
    SafeDelete(UpArrow_);
    SafeDelete(RightArrow_);
    SafeDelete(ForwardArrow_);

}

void DebuggerMouse::getTagert()
{
    //if (ControlPad::get()->PressA(0))
    //{
    //    VECTOR2 mousePos = MousePoint::get()->getPos();
    //    std::list< OBJ3D*>& list = ObjectManager::get()->getObjectList();
    //    const VECTOR3 cameraPos = CameraManager::get()->getGameCameraPosition3();
    //    float tagertDis = D3D11_FLOAT32_MAX;
    //    bool hit = false;
    //    for (OBJ3D* it : list)
    //    {
    //        VECTOR3 pos = Collision::get()->RayCastMousePointReturnPoint(mousePos, *it, hit);
    //        if (hit)
    //        {
    //            float disTemp = MyMath::get()->Length(cameraPos - pos);
    //            if (disTemp < tagertDis)
    //            {
    //                tagert = it;
    //                tagertDis = disTemp;
    //            
    //            }
    //
    //        }
    //    }
    //    if (tagertDis == D3D11_FLOAT32_MAX)
    //        tagert = nullptr;
    //}
}

bool DebuggerMouse::setTagert()
{
    //if (tagert)
    //{
    //    UpArrow_->size_ = RightArrow_->size_ = ForwardArrow_->size_ = 1.0f;
    //    if (tagertArrow)
    //    {
    //        tagertArrow->size_ = 1.1f;
    //    }
    //    if (ControlPad::get()->HoldeA(0))
    //    {
    //        if (tagertArrow)
    //        {
    //            switch (sele)
    //            {
    //            case 0:
    //                return transforming();
    //                break;
    //    
    //            case 1:
    //                return scaling();
    //                break;
    //            case 2:
    //                return rotationning();
    //                break;
    //    
    //            }
    //    
    //        }
    //    }
    //
    //    if (ControlPad::get()->PressDelete(0))
    //    {
    //        tagert->deadFlag = true;
    //        
    //        if (tagert->getTypeOBJ3D() == OBJ3DType::BLOCK)
    //        return true;
    //    }
    //    bool hit = false;
    //    float tagertDis = D3D11_FLOAT32_MAX;
    //    VECTOR2 mousePos = MousePoint::get()->getPos();
    //    Collision::get()->RayCastMousePointReturnPoint(mousePos, *UpArrow_, hit);
    //    if (hit)
    //        tagertArrow = UpArrow_;
    //    else
    //    {
    //        Collision::get()->RayCastMousePointReturnPoint(mousePos, *RightArrow_, hit);
    //        if (hit)
    //            tagertArrow = RightArrow_;
    //        else
    //        {
    //            Collision::get()->RayCastMousePointReturnPoint(mousePos, *ForwardArrow_, hit);
    //            if (hit)
    //                tagertArrow = ForwardArrow_;
    //            else tagertArrow = nullptr;
    //        }
    //    }
    //
    //
    //
    //}
    return false;

}

bool DebuggerMouse::transforming()
{
    //VECTOR2 mouseIns = MousePoint::get()->getIns() / 10;
    //VECTOR3 cameraForward = CameraManager::get()->getGameCameraForwardVector3();
    //cameraForward.y = 0;
    //VECTOR3 cameraRight = CameraManager::get()->getGameCameraRightVector3();
    //cameraRight.y = 0;
    //if (tagertArrow == UpArrow_)
    //{
    //    tagert->position_ += tagertArrow->dir * -mouseIns.y;
    //    //ImGui::SliderFloat2("moiuse Ins", &mouseIns.x, -1, -2);
    //    return true;
    //}
    //float angle1 = MyMath::get()->AngleBetweenVectorReturnRadian(cameraForward, tagertArrow->dir);
    //float angle2 = MyMath::get()->AngleBetweenVectorReturnRadian(cameraRight, tagertArrow->dir);
    //if (angle2 > DirectX::XM_PIDIV2)
    //{
    //    angle2 = DirectX::XM_PI - angle2;
    //    mouseIns.x *= -1;
    //}
    //if (angle1 > DirectX::XM_PIDIV2)
    //{
    //    angle1 = DirectX::XM_PI - angle1;
    //    mouseIns.y *= -1;
    //}
    //if (angle1 < angle2)
    //    tagert->position_ += tagertArrow->dir * -mouseIns.y;
    //else
    //    tagert->position_ += tagertArrow->dir * mouseIns.x;
    //
    return true;
}

bool DebuggerMouse::scaling()
{

    //VECTOR2 mouseIns = MousePoint::get()->getIns() / 10;
    //VECTOR3 cameraForward = CameraManager::get()->getGameCameraForwardVector3();
    //cameraForward.y = 0;
    //VECTOR3 cameraRight = CameraManager::get()->getGameCameraRightVector3();
    //cameraRight.y = 0;
    //if (tagertArrow == UpArrow_)
    //{
    //    tagert->scale_ += tagertArrow->dir * -mouseIns.y;
    //    return true;
    //}
    //float angle1 = MyMath::get()->AngleBetweenVectorReturnRadian(cameraForward, tagertArrow->dir);
    //float angle2 = MyMath::get()->AngleBetweenVectorReturnRadian(cameraRight, tagertArrow->dir);
    //if (angle2 > DirectX::XM_PIDIV2 || angle1 > DirectX::XM_PIDIV2)
    //{
    //    angle2 = DirectX::XM_PI - angle2;
    //    angle1 = DirectX::XM_PI - angle1;
    //    mouseIns *= -1;
    //}
    //if (angle1 < angle2)
    //    tagert->scale_ += tagertArrow->dir * -mouseIns.y;
    //else
    //    tagert->scale_ += tagertArrow->dir * mouseIns.x;
    //
    return true;
}

bool DebuggerMouse::rotationning()
{
    //VECTOR2 mouseIns = MousePoint::get()->getIns();
    //VECTOR3 cameraForward = CameraManager::get()->getGameCameraForwardVector3();
    //cameraForward.y = 0;
    //VECTOR3 cameraRight = CameraManager::get()->getGameCameraRightVector3();
    //cameraRight.y = 0;
    //if (tagertArrow == UpArrow_)
    //{
    //    tagert->rotation_ += tagertArrow->dir * -mouseIns.y;
    //    return true;
    //}
    //float angle1 = MyMath::get()->AngleBetweenVectorReturnRadian(cameraForward, tagertArrow->dir);
    //float angle2 = MyMath::get()->AngleBetweenVectorReturnRadian(cameraRight, tagertArrow->dir);
    //if (angle2 > DirectX::XM_PIDIV2 || angle1 > DirectX::XM_PIDIV2)
    //{
    //    angle2 = DirectX::XM_PI - angle2;
    //    angle1 = DirectX::XM_PI - angle1;
    //    mouseIns *= -1;
    //}
    //if (angle1 < angle2)
    //    tagert->rotation_ += tagertArrow->dir * -mouseIns.y;
    //else
    //    tagert->rotation_ += tagertArrow->dir * mouseIns.x;
    //
    return true;
}

void DebuggerArrow::draw()
{
    //GraphicEngine::get()->drawSkinnedMesh(mesh_, worldTransform, color_, nullptr, drawTurn_, drawStates_, 3);
}
