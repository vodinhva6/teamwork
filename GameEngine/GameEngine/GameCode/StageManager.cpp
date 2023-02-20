#include "StageManager.h"
#include "DataBase.h"

StageManager::StageManager()
{

}

void StageManager::CreateAllStage2D(int stageNo)
{
	switch (stageNo)
	{
	case StageNo::Stage1:
		Create2DStage1();
		break;

	case StageNo::Stage2:

		break;

	case StageNo::Stage3:

		break;
	}
}

void StageManager::StageDraw()
{
	for (auto it : stage2DList)
	{
		it->draw();
	}
}

void StageManager::Create2DStage1()
{
	DataBase* database = DataBase::get();

	Stage2D* stage2d = DataBase::get()->CreateStage2D1();
	stage2DList.push_back(stage2d);
}