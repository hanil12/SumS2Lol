#pragma once
class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();

private:
	shared_ptr<CircleCollider>	_body;
	shared_ptr<Line>			_barrel;

	float _speed;

	Vector	_barrelDir;
	float	_barrelLength;
	float	_angle;
};

