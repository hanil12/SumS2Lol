#include "framework.h"
#include "Bar.h"

#include "AlkaBall.h"

Bar::Bar()
{
	_pos = CENTER + Vector(0, 200);
	_body = make_shared<RectCollider>(_pos, Vector(140, 20));
}

Bar::~Bar()
{
}

void Bar::Update()
{
	_body->Update();
}

void Bar::Render(HDC hdc)
{
	_body->Render(hdc);
}

void Bar::Input(shared_ptr<AlkaBall> ball)
{
	if (GetKeyState('A') & 0x8000)
	{
		_pos += Vector(-1, 0) * 10;
	}

	if (GetKeyState('D') & 0x8000)
	{
		_pos += Vector(1, 0) * 10;
	}

	_body->SetCenter(_pos);

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		ball->Fire(Vector(0, -1));
	}
}
