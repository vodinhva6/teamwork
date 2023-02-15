#include "ControlPad.h"
#include "InputManager.h"
#include "MyMath.h"
#include "MousePoint.h"
using namespace DirectX;
using namespace input;
VECTOR2 ControlPad::getPosLeftJoy(int playerNum)
{
    return playerNum_[playerNum].PositionLeftJoy;
}

VECTOR2 ControlPad::getPosRightJoy(int playerNum)
{
    return playerNum_[playerNum].PositionRightJoy;
}

VECTOR2 ControlPad::getOldPosLeftJoy(int playerNum)
{
    return playerNum_[playerNum].OldPositionLeftJoy;
}

VECTOR2 ControlPad::getOldPosRightJoy(int playerNum)
{
    return playerNum_[playerNum].OldPositionRightJoy;
}

float ControlPad::getTriggerRight(int playerNum)
{
    if (!enableUsing)
        return false;
    return playerNum_[playerNum].TriggerRight;
    
}

bool ControlPad::PressT(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & KEY_T);
}

bool ControlPad::PressS(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & KEY_S);
}

bool ControlPad::PressE(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & KEY_E);
}

bool ControlPad::PressQ(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & KEY_Q);
}

bool ControlPad::PressR(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & KEY_R);
}

bool ControlPad::PressDelete(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & KEY_DELETE);
}

int ControlPad::TRG(int playerNum)
{
    if (!enableUsing)
        return false;
    return true;// InputManager::get()->getPadAddress()[playerNum].trigger;
}

int ControlPad::STATE(int playerNum)
{
    if (!enableUsing)
        return false;
    return true;//InputManager::get()->getPadAddress()[playerNum].state;
}

bool ControlPad::PressA(int PlayerNum)
{
    if (!enableUsing)
        return false;
     return (playerNum_[PlayerNum].PressTRG & PAD_TRG1);
}

bool ControlPad::PressRightMouse(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_TRG4);
}

bool ControlPad::HoldeA(int playerNum)
{
    if (!enableUsing)
        return false;
    return playerNum_[playerNum].StatePress & PAD_TRG1;
}

bool ControlPad::PressF1(int playerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[playerNum].PressTRG & KEY_F1);
}

bool ControlPad::PressF2(int playerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[playerNum].PressTRG & KEY_F2);
}

bool ControlPad::PressF3(int playerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[playerNum].PressTRG & KEY_F3);
}

bool ControlPad::HoldeZ(int playerNum)
{
    if (!enableUsing)
        return false;
    return playerNum_[playerNum].StatePress & KEY_Z;
}

bool ControlPad::HoldeX(int playerNum)
{
    if (!enableUsing)
        return false;
    return playerNum_[playerNum].StatePress & KEY_X;
}

bool ControlPad::PressSpace(int playerNum)
{
    if (!enableUsing)
        return false;
    return playerNum_[playerNum].PressTRG & KEY_SPACE;
}

bool ControlPad::PressLeft(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_LEFT);
}

bool ControlPad::PressRight(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_RIGHT);
}

bool ControlPad::PressUp(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_UP);
}

bool ControlPad::PressDown(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_DOWN);
}

bool ControlPad::PressStart(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_START);
}

bool ControlPad::PressBack(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_TRG3);
}

bool ControlPad::PressY(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].PressTRG & PAD_TRG4);
}

bool ControlPad::ReleaseA(int PlayerNum)
{
    if (!enableUsing)
        return false;
    return (playerNum_[PlayerNum].Release & PAD_TRG1);
}

void ControlPad::setVibration(int PlayerNum, float motorLeft, float motorRight)
{
    //InputManager::get()->setVibration(PlayerNum, motorLeft, motorRight);
}



void ControlPad::update()
{
    InputManager* inputMana = InputManager::get();
    
    
    int stateInput = inputMana->getPadAddress()[0].state;
    
    if (controler_ == Controler::GAMEPAD)
    {
        for (int i = 0; i < MAX_PLAYER; i++)
        {
            playerNum_[i].OldPositionLeftJoy = playerNum_[i].PositionLeftJoy;
            playerNum_[i].PositionLeftJoy.x = inputMana->getPadAddress()[i].leftX;
            playerNum_[i].PositionLeftJoy.y = inputMana->getPadAddress()[i].leftY;
    
            playerNum_[i].OldPositionRightJoy = playerNum_[i].PositionRightJoy;
            playerNum_[i].PositionRightJoy.x = inputMana->getPadAddress()[i].rightX;
            playerNum_[i].PositionRightJoy.y = inputMana->getPadAddress()[i].rightY;
    
            playerNum_[i].TriggerRight = inputMana->getPadAddress()[i].right;
            playerNum_[i].PressTRG = inputMana->getPadAddress()[i].trigger;
            playerNum_[i].Release = inputMana->getPadAddress()[i].triggerUp;
        }
    }
    
    else
    {
        playerNum_[0].OldPositionLeftJoy = playerNum_[0].PositionLeftJoy;
        playerNum_[0].PositionLeftJoy.x = 0;
        playerNum_[0].PositionLeftJoy.y = 0;
        playerNum_[0].OldPositionRightJoy = playerNum_[0].PositionRightJoy;
        
        VECTOR2 Vec = MyMath::get()->Normalize(InputManager::get()->getMousePoint()->getIns());
        playerNum_[0].PositionRightJoy.x = Vec.x;
        playerNum_[0].PositionRightJoy.y = Vec.y;
    
        playerNum_[0].TriggerRight = 0;
        playerNum_[0].PressTRG = 0;
        int stateInput = inputMana->getPadAddress()[0].state;
        playerNum_[0].StatePress = stateInput;
        switch (stateInput & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT))
        {
        case (PAD_UP | PAD_LEFT):
            playerNum_[0].PositionLeftJoy.y = 0.7f;
            playerNum_[0].PositionLeftJoy.x = -0.7f;
            break;
        case (PAD_UP | PAD_RIGHT):
            playerNum_[0].PositionLeftJoy.y = 0.7f;
            playerNum_[0].PositionLeftJoy.x = 0.7f;
            break;
        case (PAD_DOWN | PAD_LEFT):
            playerNum_[0].PositionLeftJoy.y = -0.7f;
            playerNum_[0].PositionLeftJoy.x = -0.7f;
            break;
        case (PAD_DOWN | PAD_RIGHT):
            playerNum_[0].PositionLeftJoy.y = -0.7f;
            playerNum_[0].PositionLeftJoy.x = 0.7f;
            break;
        case PAD_UP:
            playerNum_[0].PositionLeftJoy.y = 1;
            break;
        case PAD_DOWN:
            playerNum_[0].PositionLeftJoy.y = -1;
            break;
        case PAD_LEFT:
            playerNum_[0].PositionLeftJoy.x = -1;
            break;
        case PAD_RIGHT:
            playerNum_[0].PositionLeftJoy.x = 1;
            break;
            
        }
        if (stateInput & PAD_TRG1)
            playerNum_[0].TriggerRight = 1;
        playerNum_[0].Release = inputMana->getPadAddress()[0].triggerUp;
        playerNum_[0].PressTRG = inputMana->getPadAddress()[0].trigger;
    }
    
}

ControlPad::ControlPad()
{
   
    enableUsing = true;
}

void ControlPad::updateUsingControlPad()
{
    //InputManager* inputMana = InputManager::get();
    //if (inputMana->PadGameConnected(0))
    //    controler_ = Controler::GAMEPAD;
    //else controler_ = Controler::KEYBOARD;

}
