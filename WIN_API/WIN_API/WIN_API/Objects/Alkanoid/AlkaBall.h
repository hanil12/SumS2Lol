#pragma once
class Bar;

class AlkaBall
{
public:
	AlkaBall(shared_ptr<Bar> bar);
	~AlkaBall();

	void Update();
	void Render(HDC hdc);

	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }

	void Fixed();
	void Fire(Vector dir);

	void Reflection_Wall();

	void SetDir(Vector dir) { _dir = dir.NormalVector(); }
	Vector GetDir() { return _dir; }

	shared_ptr<CircleCollider> GetCollider() { return _circle; }

private:
	shared_ptr<CircleCollider> _circle;

	Vector _pos = { 0,0 };
	Vector _dir = { 0,0 };
	float _speed = 7.0f;

	weak_ptr<Bar> _bar;

	bool _isFired = false;
};

