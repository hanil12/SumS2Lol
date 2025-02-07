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

	Vector frontPos[8] =
	{

		{0,-1}, // UP
		{-1,0}, // LEFT
		{0,1}, // BOTTOM
		{1,0}, // RIGHT

		{1,1}, // DOWN RIGHT
		{-1,-1}, // UP LEFT
		{1,-1}, // UP RIGHT
		{-1,1}, // DOWN LEFT
	};

	struct Vertex
	{
		Vertex() {}
		Vertex(Vector pos, int cost) : pos(pos), cost(cost) {}

		bool operator<(const Vertex& v) const
		{
			return cost < v.cost;
		}

		bool operator>(const Vertex& v) const
		{
			return cost > v.cost;
		}

		Vector pos;
		int cost;
	};

public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void Update();

	void RightHand();
	void BFS(Vector start); // 최소 간선의 개수
	void Djikstra(Vector start); 

	// TODO...  DFS : 비효율적이지만 한번 해볼 것.
	void DFS(Vector start);
	 
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

	// Djikstra
	vector<vector<int>> _best;
};

