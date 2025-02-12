#pragma once

class AlkaBall;

class Bar
{
public:
	Bar();
	~Bar();

	void Update();
	void Render(HDC hdc);

	void Input(shared_ptr<AlkaBall> ball);

	Vector GetPos() { return _pos; }
	shared_ptr<RectCollider> GetCollider() { return _body; }

private:
	shared_ptr<RectCollider> _body;

	Vector _pos;
};

