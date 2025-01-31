#include "framework.h"
#include "CannonScene.h"

#include "Objects/Cannon/Cannon.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>();
	_cannon2 = make_shared<Cannon>();
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon->Update();
	_cannon2->Update();

	_timeElipse += 0.1f;

	if (_timeElipse < _delay)
		return;

	switch (_curTurn)
	{
	case CannonScene::ONE:
	{
		_cannon->Move();
 		_cannon->Fire(bind(&CannonScene::NextTurn, this));
	}
		break;
	case CannonScene::TWO:
	{
		_cannon2->Move();
		_cannon2->Fire(bind(&CannonScene::NextTurn, this));
	}
		break;
	default:
		break;
	}

	// cannon1의 공들과 cannon2의 몸체와 충돌?
	for (auto ball : _cannon->GetBalls())
	{
		_cannon2->IsCollision(ball);
	}

	for (auto ball : _cannon2->GetBalls())
	{
		_cannon->IsCollision(ball);
	}
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	_cannon2->Render(hdc);
}
