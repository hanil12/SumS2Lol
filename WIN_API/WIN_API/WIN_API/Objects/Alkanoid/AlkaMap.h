#pragma once

class Brick;
class AlkaBall;
class Bar;

class AlkaMap
{
public:
	AlkaMap();
	~AlkaMap();

	void Init(shared_ptr<Bar> bar);

	void Update();
	void Render(HDC hdc);

	vector<vector<shared_ptr<Brick>>> GetBricks() { return _bricks; }

	void IsCollision_Bricks(shared_ptr<AlkaBall> ball);
	void GetItems(shared_ptr<Bar> bar);

private:
	vector<vector<shared_ptr<Brick>>> _bricks;
	vector<shared_ptr<class AlkaItem>> _items;

	Vector _brickSize = Vector(80, 20);

	int _countX = 9;
	int _countY = 3;

	Vector _brickGap = Vector(2, 2);
};

