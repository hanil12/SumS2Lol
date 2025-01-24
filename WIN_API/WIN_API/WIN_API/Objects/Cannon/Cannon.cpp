#include "framework.h"
#include "Cannon.h"

Cannon::Cannon()
{
	_angle = 0;
	_barrelDir = Vector(1, 0);
	_barrelLength = 120.0f;
	_speed = 10.0f;

	_body = make_shared<CircleCollider>(CENTER, 50);
	_barrel = make_shared<Line>(_body->GetCenter(), _body->GetCenter() + _barrelDir * _barrelLength);
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	_body->Update();
	_barrel->Update();

	_barrel->start = _body->GetCenter();
	_barrel->end = _body->GetCenter() + _barrelDir * _barrelLength;

	Move();
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
}

void Cannon::Move()
{
	if (GetKeyState('A') & 0x8000)
	{
		_body->SetCenter(_body->GetCenter() + Vector(-1, 0) * _speed);
	}
	if (GetKeyState('D') & 0x8000)
	{
		_body->SetCenter(_body->GetCenter() + Vector(1, 0) * _speed);
	}
}
