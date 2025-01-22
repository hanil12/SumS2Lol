#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector center, Vector size)
: _center(center), _halfSize(size * 0.5f)
{
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));
}

RectCollider::~RectCollider()
{
	for (auto pen : _pens)
	{
		DeleteObject(pen);
	}
}

void RectCollider::Update()
{
}

void RectCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPen]);

	float left = _center.x - _halfSize.x;
	float right = _center.x + _halfSize.x;
	float top = _center.y - _halfSize.y;
	float bottom = _center.y + _halfSize.y;

	Rectangle(hdc, left, top, right, bottom);
}


// Rect 회전하지않는다는 조건
bool RectCollider::IsCollision(const Vector& pos)
{
	return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return false;
}
