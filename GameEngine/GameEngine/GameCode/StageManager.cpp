#include "StageManager.h"
#include "Framework.h"

StageManager::StageManager()
{
    spr_ = new Sprite(Framework::get()->getDevice(), L"./Data/Asset/Stage/stage.png");
    position_ = { Framework::get()->getScreenWidth() * 0.5f, Framework::get()->getScreenHeight() * 0.5f};

}

void StageManager::draw()
{

}
