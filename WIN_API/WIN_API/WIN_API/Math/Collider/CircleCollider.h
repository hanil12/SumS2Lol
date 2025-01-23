#pragma once
class CircleCollider : public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(Vector center, float radius);
	~CircleCollider();

	void Update();
	void Render(HDC hdc);

	Vector GetCenter() { return _center; }
	void SetCenter(const Vector& pos) { _center = pos; }
	float GetRadius() { return _radius; }
	void SetRadius(float radius) { _radius = radius; }

	bool IsCollision(const Vector& pos);
	bool IsCollision(shared_ptr<CircleCollider> other);
	bool IsCollision(shared_ptr<class RectCollider> rect);

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

private:
	UINT					_curPen = 0;
	vector<HPEN>			_pens;

	Vector					_center;
	float					_radius;
};

