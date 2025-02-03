#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector dir);
	void SetPos(Vector pos) { _circle->SetCenter(pos); }
	void AddVector(Vector v);
	shared_ptr<CircleCollider> GetCollider() { return _circle; }

	bool isActive = false;

private:
	shared_ptr<CircleCollider>  _circle;

	float _ballHasGone = 0.0f;
	float _ballSpeed = 3;
	Vector _dir;
};

