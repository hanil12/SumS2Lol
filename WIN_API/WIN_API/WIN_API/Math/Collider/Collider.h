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

	// enum class는 이름이 겹쳐도 상관없다.
	enum class TempType
	{
		NONE,
		TEMP1,
		TEMP2
	};

	Collider(Vector center);
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	bool IsCollision(shared_ptr<Collider> other);
	virtual bool IsCollision(const Vector& pos) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other)abstract;
	virtual bool IsCollision(shared_ptr<class RectCollider> rect)abstract;

	Vector GetCenter() { return _center; }
	void SetCenter(const Vector& pos) { _center = pos; }

	void SetGreen() { _curPen = 0; }
	void SetRed() { _curPen = 1; }

protected:
	UINT					_curPen = 0;
	vector<HPEN>			_pens;

	Vector					_center;

	ColType					_type = ColType::NONE;
};

