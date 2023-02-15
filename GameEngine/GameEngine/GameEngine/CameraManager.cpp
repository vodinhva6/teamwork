#include "CameraManager.h"
#include "GraphicEngine.h"
#include "InputManager.h"
#include "MyMath.h"
void CameraManager::update()
{
#ifdef _DEBUG
    ImGui::Begin("Camera");
    ImGui::SliderFloat3("Camera Pos", &gameCameraInfor.cameraPos.x, -20, 20);
    ImGui::SliderFloat3("Camera Tagert", &gameCameraInfor.cameraTarget.x, -100, 100);
    ImGui::SliderFloat3("Camera debug Pos", &debugCameraInfor.cameraPos.x, -20, 20);
    ImGui::SliderFloat3("Camera debug Tagert", &debugCameraInfor.cameraTarget.x, -100, 100);
    ImGui::End();
#endif // _DEBUG
    //CameraVibrate();
    //moveLineCyclic();
    //if (activeControl)
    //ChangeGameCameraPositionToPivotPosition();
    //updateViewAndProjectionCamera();
    //updateChangeProjetion();
    //ChangeSize2DProjection();
    DebugCameraUpdate();
    updateSceneView();

}

void CameraManager::init()
{
    angleVibrate = 0;
    gameCameraInfor.cameraUp = { 0,1,0,0 };
    gameCameraInfor.cameraPos = { 0,0,50,0 };
    gameCameraInfor.cameraTarget = { 0,0,-10,0 };
    debugCameraInfor = gameCameraInfor;
    activeControl = false;
    pivotPos[0] = pivotPos[1] = pivotPos[2] = pivotPos[3] = { gameCameraInfor.cameraPos.x,gameCameraInfor.cameraPos.y,gameCameraInfor.cameraPos.z };
    runUpDowntimer = 0;
    Project2DSize = 100;
    maxDistanceFromPivot = 100;
    scale = { 0.1f,0.1f,0.1f };
    float aspect_ratio = GraphicEngine::get()->getAspectRatio();
    projections[PROJECTIONNAME::ProjectionPerspectiveFovLH] = { DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45), aspect_ratio, 0.1f, 1000.0f) };
    projections[PROJECTIONNAME::ProjectionOrthographicLH] = DirectX::XMMatrixOrthographicLH(Project2DSize * aspect_ratio, Project2DSize, 0.1f, 1000.0f);
    toPivotPos = nullptr;
    distanceFromTagert = 200;
    Projection2DViewNow = false;
    projectionNow = projections[PROJECTIONNAME::ProjectionPerspectiveFovLH];
    changeToProjection = nullptr;
    speedChange = 0;
    pivotNow = 1;
#if _DEBUG
    ShaderData shaderData = { "./Data/Shaders/skinned_mesh_vs.cso", "./Data/Shaders/skinned_mesh_ps.cso" };
    //cameraObj = GraphicEngine::get()->createSkinnedMesh("./EngineObject/camera.fbx", false, SkinnedMeshObjectAxis::DEFAULT, shaderData);
#endif // _DEBUG
}
void CameraManager::initSceneGame()
{
    if (Projection2DViewNow)
    {
        // 2D -> 3D
        ChangeProjection(PROJECTIONNAME::ProjectionPerspectiveFovLH, 0.0001f);
        ProjectionChangeSpeedUpRate = 1.15f;
        Projection2DViewNow = false;

    }
    else
    {
        // 3D -> 2D
        ChangeProjection(PROJECTIONNAME::ProjectionOrthographicLH, 0.1f);
        ProjectionChangeSpeedUpRate = 1;
        Projection2DViewNow = true;
        Project2DSize = 100;

        toPivotPos = &pivotPos[pivotNow];
    }
}
void CameraManager::setGameCameraPosition(const VECTOR3& pos)
{
    gameCameraInfor.cameraPos = pos;
}
const VECTOR3 CameraManager::getGameCameraTagertVector3()
{
    CameraInfor* CameraInfor = nullptr;
    CameraInfor = &gameCameraInfor;
    VECTOR3 tagert =
    {
        CameraInfor->cameraTarget.x,
        CameraInfor->cameraTarget.y,
        CameraInfor->cameraTarget.z
    };
    // tagert = MyMath::get()->Normalize(tagert);
    return tagert;
}
void CameraManager::Change3DTo2D(float speed)
{
    // 3D -> 2D
    ChangeProjection(PROJECTIONNAME::ProjectionOrthographicLH, speed);
    ProjectionChangeSpeedUpRate = 1;
    Projection2DViewNow = true;
    Project2DSize = 100;
}

void CameraManager::Change2DTo3D(float speed)
{
    // 2D -> 3D
    ChangeProjection(PROJECTIONNAME::ProjectionPerspectiveFovLH, speed);
    ProjectionChangeSpeedUpRate = 1.15f;
    Projection2DViewNow = false;
}
void CameraManager::setGameCameraTagert(const VECTOR3& tagert)
{

    gameCameraInfor.cameraTarget = tagert;
}

const VECTOR3 CameraManager::getGameCameraPosition3()
{
    VECTOR3 pos = { gameCameraInfor.cameraPos.x, gameCameraInfor.cameraPos.y, gameCameraInfor.cameraPos.z };
    return pos;
}

const VECTOR3 CameraManager::getGameCameraUpVector3()
{
    VECTOR3 up = { gameCameraInfor.cameraUp.x, gameCameraInfor.cameraUp.y, gameCameraInfor.cameraUp.z };
    up = MyMath::get()->Normalize(up);
    return up;
}

const VECTOR4 CameraManager::getGameCameraForwardVector4()
{
    VECTOR4 forward = { gameCameraInfor.cameraTarget - gameCameraInfor.cameraPos };
    forward = MyMath::get()->Normalize(forward);
    return forward;
}

const VECTOR3 CameraManager::getGameCameraForwardVector3()
{
    CameraInfor* CameraInfor = nullptr;
    CameraInfor = &gameCameraInfor;
    VECTOR3 forward =
    {
        CameraInfor->cameraTarget.x - CameraInfor->cameraPos.x,
        CameraInfor->cameraTarget.y - CameraInfor->cameraPos.y,
        CameraInfor->cameraTarget.z - CameraInfor->cameraPos.z
    };
    forward = MyMath::get()->Normalize(forward);
    return forward;
}

const VECTOR4 CameraManager::getGameCameraRightVector4()
{
    
    VECTOR3 t = MyMath::get()->Cross(getGameCameraUpVector3(), getGameCameraForwardVector3());
    VECTOR4 right = { t.x,t.y,t.z,0 };
    return right;
}

const VECTOR3 CameraManager::getGameCameraRightVector3()
{
    VECTOR3 right = MyMath::get()->Cross(getGameCameraUpVector3(), getGameCameraForwardVector3());
    return right;
}

void CameraManager::ResetCameraAtWorldCenter()
{
    gameCameraInfor.cameraPos = { 0,0,0 };
    gameCameraInfor.cameraTarget = { 0,0,10 };
    Project2DSize = 100;
    maxDistanceFromPivot = 100;
    toPivotPos = nullptr;
    distanceFromTagert = 200;
    Projection2DViewNow = false;
    projectionNow = projections[PROJECTIONNAME::ProjectionPerspectiveFovLH];
    changeToProjection = nullptr;
    pivotNow = 1;
    ProjectionChangeSpeedUpRate = 0;
}

void CameraManager::CameraVibrate()
{
    static float angle = 0;
    float a = cosf(MyMath::get()->convertToRadian(angle + 90));
    //gameCameraInfor.cameraPos.y += a ;
    gameCameraInfor.cameraPos.x += a ;
    gameCameraInfor.cameraPos.z += sinf(MyMath::get()->convertToRadian(angle)) ;
    angle += 30;
    
}

void CameraManager::ChangeProjection(int projectionNum, float speed)
{
    changeToProjection = &projections[projectionNum];
    speedChange = speed;
}

void CameraManager::ChangeProjectionSlerp(DirectX::XMMATRIX& changeToPjection)
{
   
    DirectX::XMFLOAT4X4 projec;
    DirectX::XMStoreFloat4x4(&projec, projectionNow);
    float aspect_ratio = GraphicEngine::get()->getAspectRatio();
    DirectX::XMFLOAT4X4 Toprojec;
    DirectX::XMStoreFloat4x4(&Toprojec, changeToPjection);


    VECTOR4 row1 = { projec._11,projec._12,projec._13,projec._14 };
    VECTOR4 row2 = { projec._21,projec._22,projec._23,projec._24 };
    VECTOR4 row3 = { projec._31,projec._32,projec._33,projec._34 };
    VECTOR4 row4 = { projec._41,projec._42,projec._43,projec._44 };

    VECTOR4 toRow1 = { Toprojec._11,Toprojec._12,Toprojec._13,Toprojec._14 };
    VECTOR4 toRow2 = { Toprojec._21,Toprojec._22,Toprojec._23,Toprojec._24 };
    VECTOR4 toRow3 = { Toprojec._31,Toprojec._32,Toprojec._33,Toprojec._34 };
    VECTOR4 toRow4 = { Toprojec._41,Toprojec._42,Toprojec._43,Toprojec._44 };

    bool equal1 = MyMath::get()->Vector4AndVector4Equal(row1, toRow1,5);
    bool equal2 = MyMath::get()->Vector4AndVector4Equal(row2, toRow2,5);
    bool equal3 = MyMath::get()->Vector4AndVector4Equal(row3, toRow3,5);
    bool equal4 = MyMath::get()->Vector4AndVector4Equal(row4, toRow4,5);

    DirectX::XMVECTOR Row1 = DirectX::XMLoadFloat4(&row1);
    DirectX::XMVECTOR Row2 = DirectX::XMLoadFloat4(&row2);
    DirectX::XMVECTOR Row3 = DirectX::XMLoadFloat4(&row3);
    DirectX::XMVECTOR Row4 = DirectX::XMLoadFloat4(&row4);

    DirectX::XMVECTOR ToRow1 = DirectX::XMLoadFloat4(&toRow1);
    DirectX::XMVECTOR ToRow2 = DirectX::XMLoadFloat4(&toRow2);
    DirectX::XMVECTOR ToRow3 = DirectX::XMLoadFloat4(&toRow3);
    DirectX::XMVECTOR ToRow4 = DirectX::XMLoadFloat4(&toRow4);

    if (equal1)
        Row1 = ToRow1;
    else Row1 = DirectX::XMVectorLerp(Row1, ToRow1, speedChange);

    if (equal2)
        Row2 = ToRow2;
    else Row2 = DirectX::XMVectorLerp(Row2, ToRow2, speedChange);

    if (equal3)
        Row3 = ToRow3;
    else Row3 = DirectX::XMVectorLerp(Row3, ToRow3, speedChange);

    if (equal4)
        Row4 = ToRow4;
    else Row4 = DirectX::XMVectorLerp(Row4, ToRow4, speedChange);

    if (equal1 && equal2 && equal3 && equal4)
    {
        changeToProjection = nullptr;
        return;
    }
    else
    {
        speedChange *= ProjectionChangeSpeedUpRate;
    }

    projectionNow = { Row1 ,Row2,Row3,Row4 };
}

void CameraManager::DebugCameraUpdate()
{
    DirectX::XMVECTOR Eye;
    DirectX::XMVECTOR Focus;
    DirectX::XMVECTOR Up;


    Up = { DirectX::XMVector3Normalize(
        DirectX::XMVectorSet(
            debugCameraInfor.cameraUp.x, debugCameraInfor.cameraUp.y, 
            debugCameraInfor.cameraUp.z, debugCameraInfor.cameraUp.w)) };

    Eye = { DirectX::XMVectorSet(
        debugCameraInfor.cameraPos.x, debugCameraInfor.cameraPos.y, 
        debugCameraInfor.cameraPos.z, debugCameraInfor.cameraPos.w) };

    Focus = { DirectX::XMVectorSet(
        debugCameraInfor.cameraTarget.x, debugCameraInfor.cameraTarget.y,
        debugCameraInfor.cameraTarget.z, debugCameraInfor.cameraTarget.w) };

    DirectX::XMVECTOR Forward = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(Focus, Eye));
    DirectX::XMVECTOR Right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(Up, Forward));
    
    MousePoint* mousP = InputManager::get()->getMousePoint();
    VECTOR2 pos = mousP->getIns();
    DirectX::XMVECTOR v = DirectX::XMQuaternionRotationAxis(Up, DirectX::XMConvertToRadians(pos.x / 30.0f));
    Forward = DirectX::XMQuaternionMultiply(Forward, v);
    Right = DirectX::XMVectorSetY(DirectX::XMVector3Cross(Up, Forward), 0);
    v = DirectX::XMQuaternionRotationAxis(Right, DirectX::XMConvertToRadians(pos.y / 30.0f));
    Forward = DirectX::XMQuaternionMultiply(Forward, v);
    Up = DirectX::XMVector3Cross(Forward, Right);
    
    
    DirectX::XMStoreFloat4(&debugCameraInfor.cameraUp, Up);
    
    ControlPad* contrPad = InputManager::get()->getControlPad();
    VECTOR2 leftJoy = contrPad->getPosLeftJoy(0);
    Eye = DirectX::XMVectorAdd(Eye, DirectX::XMVectorScale(DirectX::XMVector3Normalize(Forward), leftJoy.y * 0.5f));
    Eye = DirectX::XMVectorAdd(Eye, DirectX::XMVectorScale(DirectX::XMVector3Normalize(Right), leftJoy.x * 0.5f));
    if (contrPad->HoldeZ(0))
    {
        DirectX::XMVECTOR Down = { 0,-1,0,0 };
        Eye = DirectX::XMVectorAdd(Eye, Down);
    }
    if (contrPad->HoldeX(0))
    {
        DirectX::XMVECTOR Down = { 0,1,0,0 };
        Eye = DirectX::XMVectorAdd(Eye, Down);
    }
    DirectX::XMStoreFloat4(&debugCameraInfor.cameraPos, Eye);
    Focus = DirectX::XMVectorAdd(Eye,DirectX::XMVectorScale(Forward,DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(Focus,Eye)))));
    DirectX::XMStoreFloat4(&debugCameraInfor.cameraTarget, Focus);
    view = { DirectX::XMMatrixLookAtLH(Eye, Focus, Up) };
    
    
    {
        DirectX::XMVECTOR dummy = { 0,0,0,1 };
        VECTOR4 eye = gameCameraInfor.cameraPos;
        DirectX::XMVECTOR Eye;
        DirectX::XMVECTOR Focus;
        DirectX::XMVECTOR Up;
        Up = { DirectX::XMVector3Normalize(
        DirectX::XMVectorSet(
            gameCameraInfor.cameraUp.x, gameCameraInfor.cameraUp.y,
            gameCameraInfor.cameraUp.z, gameCameraInfor.cameraUp.w)) };
    
        Eye = { DirectX::XMVectorSet(
            gameCameraInfor.cameraPos.x, gameCameraInfor.cameraPos.y,
            gameCameraInfor.cameraPos.z, gameCameraInfor.cameraPos.w) };
    
        Focus = { DirectX::XMVectorSet(
            gameCameraInfor.cameraTarget.x, gameCameraInfor.cameraTarget.y,
            gameCameraInfor.cameraTarget.z, gameCameraInfor.cameraTarget.w) };
    
        DirectX::XMVECTOR Forward = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(Focus, Eye));
        
        DirectX::XMVECTOR Right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(Up, Forward));
    
        DirectX::XMMATRIX Orien =
        {
            Right,Up,Forward,dummy
            
        };
        DirectX::XMVECTOR orien;
        orien = DirectX::XMQuaternionRotationMatrix(Orien);
        
        DirectX::XMMATRIX Transta
        {
            scale.x,0,0,0,
            0,scale.y,0,0,
            0,0,scale.z,0,
            eye.x,eye.y,eye.z,1
        };
    
    
        DirectX::XMMATRIX TransformMatrix;
        TransformMatrix = DirectX::XMMatrixRotationQuaternion(orien) * Transta;
        DirectX::XMStoreFloat4x4(&worldTransform, TransformMatrix);
        drawCameraObj(worldTransform);
    }
}

void CameraManager::GameCameraUpdate()
{
    debugCameraInfor = gameCameraInfor;
    DirectX::XMVECTOR Eye;
    DirectX::XMVECTOR Focus;
    DirectX::XMVECTOR Up;

    Up = { DirectX::XMVector3Normalize(
        DirectX::XMVectorSet(
            gameCameraInfor.cameraUp.x, gameCameraInfor.cameraUp.y,
            gameCameraInfor.cameraUp.z, gameCameraInfor.cameraUp.w)) };

    Eye = { DirectX::XMVectorSet(
        gameCameraInfor.cameraPos.x, gameCameraInfor.cameraPos.y,
        gameCameraInfor.cameraPos.z, gameCameraInfor.cameraPos.w) };

    Focus = { DirectX::XMVectorSet(
        gameCameraInfor.cameraTarget.x, gameCameraInfor.cameraTarget.y,
        gameCameraInfor.cameraTarget.z, gameCameraInfor.cameraTarget.w) };

    view = { DirectX::XMMatrixLookAtLH(Eye, Focus, Up) };


}

bool CameraManager::getChangedProjection2DView()
{
    return(Projection2DViewNow && changeToProjection == nullptr);
}

void CameraManager::ResetProjections()
{
    float aspect_ratio = GraphicEngine::get()->getAspectRatio();
    projections[PROJECTIONNAME::ProjectionPerspectiveFovLH] = { DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45), aspect_ratio, 0.1f, 1000.0f) };
    projections[PROJECTIONNAME::ProjectionOrthographicLH] = DirectX::XMMatrixOrthographicLH(Project2DSize * aspect_ratio, Project2DSize, 0.1f, 1000.0f);
}

CameraManager::~CameraManager()
{
}

void CameraManager::drawCameraObj(DirectX::XMFLOAT4X4 world)
{
    //if(GraphicEngine::get()->getGameMode() == GameModes::DebugMode)
    DrawStates drawStates;
    drawStates.blendState = BlendStates::Alpha;
    drawStates.depthState = DepthStencilStates::DepthTestOn_DepthWriteOn;
    drawStates.drawType = DrawType::SkinnedMeshObject;
    drawStates.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn;
    drawStates.samplerState = SamplerStates::Anisotropic;
    //GraphicEngine::get()->drawSkinnedMesh(cameraObj, world, { 1,1,1,1 }, nullptr, 1, drawStates,1);
}

void CameraManager::updateViewAndProjectionCamera()
{
//    int cameraMode = GraphicEngine::get()->getGameMode();
//    (cameraMode) ? DebugCameraUpdate() : GameCameraUpdate();
//
//#ifdef _DEBUG
//    bool firstPerson = MousePoint::get()->getFirstPersonMouseNotShow();
//    if (ControlPad::get()->PressF1(0))
//    {
//        MousePoint::get()->setFirstPersonMouseNotShow(!firstPerson);
//        if (firstPerson)
//            ShowCursor(true);
//        else 
//            ShowCursor(false);
//    }
//    if (firstPerson)
//        MousePoint::get()->resetPosition();
//#endif // _DEBUG
//    if (ControlPad::get()->PressF3(0))
//    {
//        gameCameraInfor = debugCameraInfor;
//    }
        
}

CameraManager::CameraManager()
{

}

void CameraManager::updateChangeProjetion()
{
    if (changeToProjection)
    {
        ChangeProjectionSlerp(*changeToProjection);
    }
}

void CameraManager::moveLineCyclic()
{
    //static float angle = 0;
    //float a = cosf(MyMath::get()->convertToRadian(angle += 1));
    //gameCameraInfor.cameraPos.x = pivotPos.x + a * a ;
}

void CameraManager::ChangeSize2DProjection()
{
    if (Projection2DViewNow && !changeToProjection)
    {       
        //float aspect_ratio = GraphicEngine::get()->getAspectRatio();
        //Project2DSize -= MousePoint::get()->getWheelValue() / 10;
        //Project2DSize = clamp(Project2DSize, 50, 200);
        //projectionNow = DirectX::XMMatrixOrthographicLH((Project2DSize)*aspect_ratio, Project2DSize, 0.1f, 1000.0f);
    }
;}

void CameraManager::ChangeGameCameraPositionToPivotPosition()
{
    if (toPivotPos)
    {
        gameCameraInfor.cameraPos = MyMath::get()->Lerp(getGameCameraPosition3(), *toPivotPos, 0.08f);
        if (MyMath::get()->Vector3AndVector3Equal(getGameCameraPosition3(), *toPivotPos, 0))
        {
            gameCameraInfor.cameraPos = *toPivotPos;
            toPivotPos = nullptr;
        }
            
    }
}

void CameraManager::updateSceneView()
{
    SceneView3D = view * projectionNow;
}
