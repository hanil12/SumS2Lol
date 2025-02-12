#include "framework.h"
#include "AlkaItem.h"

AlkaItem::AlkaItem()
{
	_body = make_shared<CircleCollider>(_pos, 5.0f);
}

AlkaItem::~AlkaItem()
{
}

void AlkaItem::Update()
{
	_body->Update();

	_body->SetCenter(_pos);

	if (_canFalling)
		_pos += _dir * _speed;
}

void AlkaItem::Render(HDC hdc)
{
	_body->Render(hdc);
}
