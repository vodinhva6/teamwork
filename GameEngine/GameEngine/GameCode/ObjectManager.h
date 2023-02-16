#pragma once
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "Player.h"
#include "Background.h"
#include "OBJ2D.h"
#include "Scene.h"
#include <vector>
enum class SceneName;
class ObjectManager :public SingletonPatternTemplate< ObjectManager>
{
    friend class SingletonPatternTemplate< ObjectManager>;
private:
    ObjectManager();
    Player* player;
    Background* back;
    std::list<OBJ3D*> object3DList;
    std::list<OBJ2D*> object2DList;
    std::list<OBJ2D*> pause2DList;
    
public:
    ~ObjectManager();
    Player* getPlayer()
    {
        return player;
    }
    OBJ3D* getStageFloorBlock();
    std::list< OBJ3D*>& getObjectList() { return object3DList; }
    void addListObject3D(OBJ3D* obj);
    void CreateTittle2DButton();
    void CreateStage2DButton();
    void CreatePause2DButton();
    void CreateClear2DButton();
    void CreateOver2DButton();
    void CreateAllObject(SceneName sceneName);
    void createObject3D(int stage);
    void loadObject3D(std::string name);
    void ObjectUpdate(float elapsed_time);
    void ClearAllObject();
    void ObjectDraw();


private:
    void CreateObjectForTitleScene();
    void CreateObjectForGameScene();
    void CreateObjectForClearScene();
    void CreateObjectForStageScene();
};
#endif // !OBJECTMANAGER_H

