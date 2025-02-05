#pragma once

class Maze;
class Block;

class Player
{
	// Path
	enum Direction
	{
		UP,
		LEFT,
		BOTTOM,
		RIGHT,

		DIR_COUNT = 4
	};

	Vector frontPos[4] =
	{
		{0,-1}, // UP
		{-1,0}, // LEFT
		{0,1}, // BOTTOM
		{1,0}, // RIGHT
	};

public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	void BFS(Vector start);

	bool Cango(Vector pos);

private:
	weak_ptr<Maze> _maze;

	Vector				_pos = { 1,1 };
	vector<Vector>		_path;
	int					_pathIndex = 0;
	float				_delayTime = 0.0f;

	// RightHand
	Vector _dir = Vector(0,-1);

	// BFS
	vector<vector<bool>> _discovered;
	vector<vector<Vector>> _parent; // _parent[1][1] = {1,1};
};

