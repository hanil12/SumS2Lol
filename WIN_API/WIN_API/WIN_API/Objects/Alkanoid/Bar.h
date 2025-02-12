#pragma once

class AlkaBall;

class AlkaBall;

class Bar : public enable_shared_from_this<Bar>
{
public:
	Bar();
	~Bar();

	void Init();

	void Update();
	void Render(HDC hdc);

	void Input();

	Vector GetPos() { return _pos; }
	shared_ptr<RectCollider> GetCollider() { return _body; }
	vector<shared_ptr<AlkaBall>> GetBalls() { return _balls; }

	void TwoBall_Skill();

private:
	float _delayTime = 0.0f;

	shared_ptr<RectCollider> _body;

	Vector _pos;

	vector<shared_ptr<AlkaBall>> _balls;
};

