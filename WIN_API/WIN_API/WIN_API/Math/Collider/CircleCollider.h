#pragma once
class CircleCollider : public enable_shared_from_this<CircleCollider>, public Collider
{
public:
	CircleCollider(Vector center, float radius);
	~CircleCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	float GetRadius() { return _radius; }
	void SetRadius(float radius) { _radius = radius; }

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> rect) override;

private:
	float					_radius;
};

