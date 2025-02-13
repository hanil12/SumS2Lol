#pragma once
class RectCollider : public Collider
{
public:
	RectCollider(Vector center, Vector size);
	virtual ~RectCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

	int Left() { return _center.x - _halfSize.x; }
	int Right() { return _center.x + _halfSize.x; }
	int Top() { return _center.y - _halfSize.y; }
	int Bottom() { return _center.y + _halfSize.y; }

	Vector GetHalfSize() { return _halfSize; }
	void SetSize(Vector size) { _halfSize = size * 0.5f; }
	Vector GetSize() { return _halfSize * 2.0f; }

private:
	Vector					_halfSize;
};

