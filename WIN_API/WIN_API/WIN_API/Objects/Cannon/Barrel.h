#pragma once

class Cannon;

class Barrel
{
public:
	Barrel(shared_ptr<CircleCollider> cannonBody);
	~Barrel();

	void Update();
	void Render(HDC hdc);

	void SetDirection(Vector dir) { _barrelDir = dir.NormalVector(); }
	void SetAngle(float angle) { _angle = angle; }

	Vector GetDir() { return _barrelDir; }
	float GetAngle() { return _angle; }

	Vector GetMuzzle() { return _barrel->end; }

private:
	weak_ptr<CircleCollider> _cannonBody;
	shared_ptr<Line>	_barrel;

	Vector	_barrelDir;
	float	_barrelLength;
	float	_angle;
};

