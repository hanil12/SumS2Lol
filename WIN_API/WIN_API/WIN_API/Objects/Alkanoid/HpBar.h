#pragma once
class HpBar
{
public:
	HpBar(Vector center, Vector size);
	~HpBar();

	void Update();
	void Render(HDC hdc);
	void SetValue(float value);

private:
	shared_ptr<RectCollider> _bg;
	shared_ptr<RectCollider> _value;

	HBRUSH _redBrush;
	HBRUSH _oldBrush;
};

