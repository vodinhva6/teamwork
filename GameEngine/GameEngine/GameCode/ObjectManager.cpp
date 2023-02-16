#include "ObjectManager.h"
#include "DataBase.h"
#include "GraphicEngine.h"
#include "Scene.h"
ObjectManager::ObjectManager()
{
    player = nullptr;
}

ObjectManager::~ObjectManager()
{
    
}

OBJ3D* ObjectManager::getStageFloorBlock()
{
    for (auto it : object3DList)
        if (it->getTypeOBJ3D() == OBJ3DType::BLOCK)
            return it;
    return nullptr;
}

void ObjectManager::addListObject3D(OBJ3D* obj)
{
    if(obj)
    object3DList.push_back(obj);
}

void ObjectManager::CreateTittle2DButton()
{
    DataBase* dataBas = DataBase::get();

    Button* button = dataBas->CreateStartButton();
    if (button) object2DList.push_back(button);
    
    button = dataBas->CreateEndButton();
    if (button) object2DList.push_back(button);
}

void ObjectManager::CreateStage2DButton()
{
    DataBase* dataBas = DataBase::get();

    Button* button = dataBas->CreateStage1Button();
    if (button) object2DList.push_back(button);

    button = dataBas->CreateStage2Button();
    if (button) object2DList.push_back(button);

    button = dataBas->CreateStage3Button();
    if (button) object2DList.push_back(button);
}

void ObjectManager::CreatePause2DButton()
{
    DataBase* dataBas = DataBase::get();

    Button* button = dataBas->CreateContinueButton();
    if (button) pause2DList.push_back(button);

    button = dataBas->CreateRetryButton();
    if (button) pause2DList.push_back(button);

    button = dataBas->CreateBackToTitleButton();
    if (button) pause2DList.push_back(button);
}

void ObjectManager::CreateClear2DButton()
{
    DataBase* dataBas = DataBase::get();

    Button* button = dataBas->CreateNextButton();
    if (button) object2DList.push_back(button);

    button = dataBas->CreateClearRetryButton();
    if (button) object2DList.push_back(button);

    button = dataBas->CreateClearBackToStageButton();
    if (button) object2DList.push_back(button);

    button = dataBas->CreateClearBackToTitleButton();
    if (button) object2DList.push_back(button);
}

void ObjectManager::CreateOver2DButton()
{
    DataBase* dataBas = DataBase::get();

    Button* button = dataBas->CreateOverRetryButton();
    if (button) object2DList.push_back(button);

    button = dataBas->CreateOverBackToStageButton();
    if (button) object2DList.push_back(button);

    button = dataBas->CreateOverBackToTitleButton();
    if (button) object2DList.push_back(button);
}

void ObjectManager::CreateAllObject(SceneName sceneName)
{
    switch (sceneName)
    {
    case SceneName::Title:
        CreateObjectForTitleScene();
        break;
    case SceneName::Game:
        CreateObjectForGameScene();
        break;
    case SceneName::Over:
        break;
    case SceneName::Clear:
        CreateObjectForClearScene();
        break;
    case SceneName::Menu:
        break;
    case SceneName::Stage:
        CreateObjectForStageScene();
    default:
        break;
    }
}

void ObjectManager::createObject3D(int stage)
{
    //DataBase* dataBas = DataBase::get();
    //player = dataBas->CreatePlayer(stage);
    //Background* skybos = dataBas->CreateBackground();
    //
    //if (player)
    //    object3DList.push_back(player);
    //if (skybos)
    //    object3DList.push_back(skybos);
    //

}

void ObjectManager::loadObject3D(std::string name)
{
    std::ifstream file;
    file.open(name);
    if (!file)
        return;
    OBJ3D* obj = new OBJ3D();
    //std::wstring fileName = std::wstring(name.begin(),name.end());
    const char* objName = name.c_str();
    ShaderData shaderData = { "./Data/Shaders/skinned_mesh_vs.cso", "./Data/Shaders/skinned_mesh_ps.cso" };
    //obj->mesh_ = GraphicEngine::get()->createSkinnedMesh(objName,true,SkinnedMeshObjectAxis::DEFAULT, shaderData);
    obj->size_ = 0.05f;
    if (obj)
        object3DList.push_back(obj);
}

void ObjectManager::ObjectUpdate(float elapsed_time)
{
    for (std::list<OBJ3D*>::iterator it = object3DList.begin(); it != object3DList.end();)
    {
        (*it)->update(elapsed_time);
        if ((*it)->deadFlag)
        {
            SafeDelete(*it);
            it = object3DList.erase(it);
        }
        else
        {
            it++;
        }
    }


    for (std::list<OBJ2D*>::iterator it = object2DList.begin(); it != object2DList.end();)
    {
        if((*it)) (*it)->update();
        it++;
    }


}


void ObjectManager::ClearAllObject()
{
    for (std::list<OBJ3D*>::iterator it = object3DList.begin(); it != object3DList.end();)
    {
        if (*it)
        {
            SafeDelete(*it);
            it = object3DList.erase(it);
        }
        else it++;
    }
    object3DList.clear();


    for (std::list<OBJ2D*>::iterator it = object2DList.begin(); it != object2DList.end();)
    {
        if (*it)
        {
            SafeDelete(*it);
            it = object2DList.erase(it);
        }
        else it++;
    }
    object2DList.clear();


  
}

void ObjectManager::ObjectDraw()
{
    for (auto it : object3DList)
    {
        it->draw();

#ifdef _DEBUG
        it->drawDebug();
#endif // _DEBUG
    }
    for (auto it : object2DList)
    {
        if (it) it->draw();
    }
}

void ObjectManager::CreateObjectForTitleScene()
{
    Button* exitButton = DataBase::get()->CreateEndButton();
    object2DList.push_back(exitButton);
}

void ObjectManager::CreateObjectForGameScene()
{

}

void ObjectManager::CreateObjectForClearScene()
{

}

void ObjectManager::CreateObjectForStageScene()
{

}

