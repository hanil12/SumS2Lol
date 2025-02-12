#include "framework.h"
#include "AlkanoidScene.h"

#include "Objects/Alkanoid/Bar.h"
#include "Objects/Alkanoid/AlkaBall.h"
#include "Objects/Alkanoid/Brick.h"
#include "Objects/Alkanoid/AlkaMap.h"

AlkanoidScene::AlkanoidScene()
{
	_bar = make_shared<Bar>();
	_ball = make_shared<AlkaBall>(_bar);
	_map = make_shared<AlkaMap>();
}

AlkanoidScene::~AlkanoidScene()
{
}

void AlkanoidScene::Update()
{
	_bar->Update();
	_ball->Update();
	_map->Update();

	_bar->Input(_ball);
	_map->IsCollision_Bricks(_ball);
}

void AlkanoidScene::Render(HDC hdc)
{
	_bar->Render(hdc);
	_ball->Render(hdc);
	_map->Render(hdc);
}
