#pragma once
class RectCollider
{
public:
	RectCollider(Vector center, Vector size);
	~RectCollider() {}

	void Update();
	void Render(HDC hdc);

	Vector GetCenter() { return _center; }
	void SetCenter(const Vector& pos) { _center = pos; }

private:
	Vector		_center;
	Vector		_halfSize;
};

