#pragma once
class CircleCollider
{
public:
	CircleCollider(Vector center, float radius);
	~CircleCollider();

	void Update();
	void Render(HDC hdc);

	Vector GetCenter() { return _center; }
	void SetCenter(const Vector& pos) { _center = pos; }

	bool IsCollision(const Vector& pos);
	bool IsCollision(shared_ptr<CircleCollider> other);

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

private:
	UINT					_curPen = 0;
	vector<HPEN>			_pens;

	Vector					_center;
	float					_radius;
};

