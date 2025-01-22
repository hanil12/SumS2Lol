#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circle = make_shared<CircleCollider>(Vector(450, 500), 100);
	_movingCircle = make_shared<CircleCollider>(Vector(0, 0), 60);

	// rect, moving ����
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_movingCircle->SetCenter(mousePos);
	// movingRect �����̱�

	// rect�� movingrect �浹�����ؼ� ���ٲٱ�


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
