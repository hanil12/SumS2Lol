#pragma once

class Bar;
class AlkaBall;
class Brick;
class AlkaMap;

class AlkanoidScene : public Scene
{
public:
	AlkanoidScene();
	~AlkanoidScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<AlkaMap> _map;
	shared_ptr<Bar> _bar;

	shared_ptr<class HpBar> _ui_hpBar;
};

