#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circle = make_shared<CircleCollider>(Vector(450, 500), 100);
	_movingCircle = make_shared<CircleCollider>(Vector(0, 0), 60);

	// rect, moving 생성
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_movingCircle->SetCenter(mousePos);
	// movingRect 움직이기

	// rect와 movingrect 충돌판정해서 색바꾸기


	if (_circle->IsCollision(_movingCircle))
	{
		_circle->SetRed();
	}
	else
	{
		_circle->SetGreen();
	}

	_circle->Update();
	_movingCircle->Update();
}

void CollisionScene::Render(HDC hdc)
{
	_circle->Render(hdc);
	_movingCircle->Render(hdc);
}
