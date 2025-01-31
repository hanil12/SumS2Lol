#pragma once

#include "Scene/CannonScene.h"

class Barrel;
class Ball;

class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	// 시그니쳐 반환자료형(void), 매개변수(void)인 Callable 객체를 받을 수 있는 매개변수 형식
	// Callable 객체? => 변수이름()
	void Fire(function<void(void)> fn);

	shared_ptr<CircleCollider> GetCollider() { return _body; }
	vector<shared_ptr<Ball>> GetBalls() { return _balls; }
	bool IsCollision(shared_ptr<Ball> ball);

private:
	shared_ptr<CircleCollider>	_body;
	
	float _delay = 0.0f;
	const float _attackSpeed = 3.0f;

	shared_ptr<Barrel>			_barrel;

	UINT						_poolCount;
	vector<shared_ptr<Ball>>	_balls;

	float _speed;
	bool _isActive = true;
};

