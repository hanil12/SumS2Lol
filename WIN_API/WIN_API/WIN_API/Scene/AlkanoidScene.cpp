#include "framework.h"
#include "AlkanoidScene.h"

#include "Objects/Alkanoid/Bar.h"
#include "Objects/Alkanoid/AlkaBall.h"
#include "Objects/Alkanoid/Brick.h"
#include "Objects/Alkanoid/AlkaMap.h"
#include "Objects/Alkanoid/HpBar.h"

AlkanoidScene::AlkanoidScene()
{
	_bar = make_shared<Bar>();
	_map = make_shared<AlkaMap>();
	
	_bar->Init();
	_map->Init(_bar);

	_ui_hpBar = make_shared<HpBar>(CENTER + Vector(0, 300), Vector(600, 30));

	_ui_hpBar->SetValue(0.5);
}

AlkanoidScene::~AlkanoidScene()
{
}

void AlkanoidScene::Update()
{
	_bar->Update();
	_map->Update();
	_ui_hpBar->Update();

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


	// UI는 항상 최후위
	_ui_hpBar->Render(hdc);
}
