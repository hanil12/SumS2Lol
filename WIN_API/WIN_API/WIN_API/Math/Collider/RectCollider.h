#pragma once
class RectCollider
{
public:
	RectCollider(Vector center, Vector size);
	~RectCollider();

	void Update();
	void Render(HDC hdc);

	Vector GetCenter() { return _center; }
	void SetCenter(const Vector& pos) { _center = pos; }

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

	bool IsCollision(const Vector& pos);
	bool IsCollision(shared_ptr<RectCollider> other);

private:
	UINT					_curPen = 0;
	vector<HPEN>			_pens;

	Vector					_center;
	Vector					_halfSize;
};

