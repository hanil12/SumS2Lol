#pragma once

#include "Block.h"

#define MAX_X 25
#define MAX_Y 25

class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();
	Block::Type GetBlockType(Vector pos);
	void SetBlockType(Vector pos, Block::Type type);

	Vector StartPos() { return { 1,1 }; }
	Vector EndPos() { return { MAX_X - 2, MAX_Y - 2 }; }

private:
	vector<vector<shared_ptr<Block>>> _blocks;
};

