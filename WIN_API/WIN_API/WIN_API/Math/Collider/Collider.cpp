#include "framework.h"
#include "Collider.h"

#include "RectCollider.h"
#include "CircleCollider.h"

Collider::Collider(Vector center)
: _center(center)
{
	_pens.push_back(CreatePen(1, 3, BLACK));
	_pens.push_back(CreatePen(1, 3, GREEN));
	_pens.push_back(CreatePen(1, 3, RED));
}

Collider::~Collider()
{
	for (auto pen : _pens)
	{
		DeleteObject(pen);
	}
}

bool Collider::IsCollision(shared_ptr<Collider> other)
{
	// other이 circle인지 rect인지?
	ColType otherType = other->_type;

	switch (otherType)
	{
	case Collider::ColType::NONE:
		break;
	case Collider::ColType::CIRCLE:
	{
		return IsCollision(static_pointer_cast<CircleCollider>(other));
	}
		break;
	case Collider::ColType::RECT:
	{
		return IsCollision(static_pointer_cast<RectCollider>(other));
	}
		break;
	default:
		break;
	}

	return false;
}
