#include "framework.h"
#include "Brick.h"

Brick::Brick(Vector size)
{
	_pos = CENTER;
	_body = make_shared<RectCollider>(CENTER, size);
}

Brick::~Brick()
{
}

void Brick::Update()
{
	_body->Update();

	_body->SetCenter(_pos);
}

void Brick::Render(HDC hdc)
{
	_body->Render(hdc);
}
