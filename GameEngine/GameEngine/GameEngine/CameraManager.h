#pragma once
#include <DirectXMath.h>

#include "DataFormat.h"
enum PROJECTIONNAME
{
    ProjectionOrthographicLH,
    ProjectionPerspectiveFovLH
};


class CameraManager
{
public:
    CameraManager();
    void update();
    void init();
    void initSceneGame();

    void setGameCameraTagert(const VECTOR3& tagert);


    void setGameCameraPosition(const VECTOR3& pos);
    void addGameCameraPosition(const VECTOR3& addPos) { gameCameraInfor.cameraPos += addPos; }
    const VECTOR3 getGameCameraPosition3();
    const VECTOR4& getGameCameraPosition4() { return gameCameraInfor.cameraPos; }


    const VECTOR4& getGameCameraUpVector4() { return gameCameraInfor.cameraUp; }
    const VECTOR3 getGameCameraUpVector3(); 

    const VECTOR4 getGameCameraForwardVector4();
    const VECTOR3 getGameCameraForwardVector3();
     
    const VECTOR4 getGameCameraRightVector4();
    const VECTOR3 getGameCameraRightVector3();

    const VECTOR3 getGameCameraTagertVector3();

    const DirectX::XMMATRIX& getView() { return view; }
    const DirectX::XMMATRIX& getProjection() { return projectionNow; }
    const DirectX::XMMATRIX& getSceneView3D() { return SceneView3D; }

    void setAngleVibrate() { angleVibrate += 720; }

    void DebugCameraUpdate();
    void GameCameraUpdate();
    void Change3DTo2D(float speed);
    void Change2DTo3D(float speed);

    void ResetCameraAtWorldCenter();

    void CameraVibrate();

    void ChangeProjection(int projectionNum, float speed);

    void setPivotPos(int i, VECTOR3 pos) { pivotPos[i] = pos; }

    VECTOR3& getPivotPos(int i) { return pivotPos[i]; }

    const float& getDisFromTagert() { return distanceFromTagert; }

    int getPivotNow() { return pivotNow; }

    bool getProjection2DViewNow() { return Projection2DViewNow; }

    bool getChangedProjection2DView();

    void setActiveControl(bool activeControl) { this->activeControl = activeControl; }

    void ResetProjections();

    ~CameraManager();
private:
    struct CameraInfor
    {
        VECTOR4 cameraPos;
        VECTOR4 cameraTarget;
        VECTOR4 cameraUp;
    };
    void drawCameraObj(DirectX::XMFLOAT4X4 world);
    void updateViewAndProjectionCamera();
    
    void updateChangeProjetion();
    void ChangeProjectionSlerp(DirectX::XMMATRIX& );
    void moveLineCyclic();
    void ChangeSize2DProjection();
    void ChangeGameCameraPositionToPivotPosition();
    void updateSceneView();

    CameraInfor debugCameraInfor;
    CameraInfor gameCameraInfor;
    
    bool activeControl;

    VECTOR3 scale;
    float speedChange;
    float angleVibrate;
    float Project2DSize;
    float ProjectionChangeSpeedUpRate;

    int runUpDowntimer;
    DirectX::XMFLOAT4X4 worldTransform;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projections[2];
    DirectX::XMMATRIX projectionNow;
    DirectX::XMMATRIX* changeToProjection = nullptr;
    DirectX::XMMATRIX SceneView3D;
    //SkinnedMesh* cameraObj;


    bool Projection2DViewNow;
    float distanceFromTagert;
    float maxDistanceFromPivot;
    int pivotNow;
    VECTOR3* toPivotPos;
    VECTOR3 pivotPos[4];
};

