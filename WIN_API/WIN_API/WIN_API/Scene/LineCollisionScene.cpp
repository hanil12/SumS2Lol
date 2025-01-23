#include "framework.h"
#include "LineCollisionScene.h"

LineCollisionScene::LineCollisionScene()
{
	_line1 = make_shared<Line>(Vector(100, 100), Vector(100, 100));
	_line2 = make_shared<Line>(Vector(100, 500), Vector(700, 200));
}

LineCollisionScene::~LineCollisionScene()
{
}

void LineCollisionScene::Update()
{
	_line1->Update();
	_line2->Update();

	if (_line1->IsCollision(_line2))
	{
		_line2->SetRed();
	}
	else
	{
		_line2->SetGreen();
	}

	_line1->end = mousePos;
}

void LineCollisionScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
}
