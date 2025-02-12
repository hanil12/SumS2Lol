#include "framework.h"
#include "AlkanoidScene.h"

#include "Objects/Alkanoid/Bar.h"
#include "Objects/Alkanoid/AlkaBall.h"
#include "Objects/Alkanoid/Brick.h"
#include "Objects/Alkanoid/AlkaMap.h"

AlkanoidScene::AlkanoidScene()
{
	_bar = make_shared<Bar>();
	_map = make_shared<AlkaMap>();
	
	_bar->Init();
	_map->Init(_bar);
}

AlkanoidScene::~AlkanoidScene()
{
}

void AlkanoidScene::Update()
{
	_bar->Update();
	_map->Update();

	_bar->Input();

	for (auto ball : _bar->GetBalls())
	{
		if (ball->IsFired() == false)
			continue;

		_map->IsCollision_Bricks(ball);
	}

	_map->GetItems(_bar);
}

void AlkanoidScene::Render(HDC hdc)
{
	_bar->Render(hdc);
	_map->Render(hdc);
}
