#include "framework.h"
#include "Barrel.h"

#include "Cannon.h"

Barrel::Barrel(shared_ptr<CircleCollider> cannonBody)
{
	_angle = 0;
	_barrelDir = Vector(1, 0);
	_barrelLength = 120.0f;

	_barrel = make_shared<Line>(
		cannonBody->GetCenter(),
		cannonBody->GetCenter() + _barrelDir * _barrelLength);

	_cannonBody = cannonBody;
}

Barrel::~Barrel()
{
}

void Barrel::Update()
{
	if (_cannonBody.expired())
		return;

	shared_ptr<CircleCollider> cannonBody = _cannonBody.lock();

	_barrel->Update();

	_barrel->start = cannonBody->GetCenter();
	_barrel->end = cannonBody->GetCenter() + _barrelDir * _barrelLength;

	// _barrelDir
	_barrelDir.x = cosf(_angle);
	_barrelDir.y = sinf(_angle);
}

void Barrel::Render(HDC hdc)
{
	_barrel->Render(hdc);
}
