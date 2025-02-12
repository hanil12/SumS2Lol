#pragma once
class Brick
{
public:
	Brick(Vector size);
	~Brick();

	void Update();
	void Render(HDC hdc);

	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }

	shared_ptr<RectCollider> GetCollider() { return _body; }

private:
	shared_ptr<RectCollider> _body;
	Vector _pos;
};

