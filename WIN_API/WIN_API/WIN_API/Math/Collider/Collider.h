#pragma once
class CircleCollider;
class RectCollider;

class Collider
{
public:
	enum class ColType
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider(Vector center);
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	bool IsCollision(shared_ptr<Collider> other);
	virtual bool IsCollision(const Vector& pos) abstract;
	virtual bool IsCollision(shared_ptr<class RectCollider> rect)abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other)abstract;

	Vector GetCenter() { return _center; }
	void SetCenter(const Vector& pos) { _center = pos; }

	void SetRed() { _curPen = 2; }
	void SetGreen() { _curPen = 1; }

protected:
	UINT					_curPen = 0;
	vector<HPEN>			_pens;

	Vector					_center;

	ColType					_type = ColType::NONE;
};

