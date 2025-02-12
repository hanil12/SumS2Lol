#include "framework.h"
#include "Brick.h"
#include "AlkaItem.h"

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
	if (!_isActive)
		return;

	_body->Update();

	_body->SetCenter(_pos);
}

void Brick::Render(HDC hdc)
{
	if (_isActive)
		_body->Render(hdc);
}

void Brick::SetItem(shared_ptr<AlkaItem> item)
{
	_item = item;
	if (_item.expired())
		return;

	_item.lock()->Pos() = _pos;
}

void Brick::Break_Brick()
{
	_isActive = false;
	if (!_item.expired())
		_item.lock()->CanFalling() = true;
}
