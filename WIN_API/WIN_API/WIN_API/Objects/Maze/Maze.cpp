#include "framework.h"
#include "Maze.h"

#include "Block.h"

Maze::Maze()
{
	// offset : 기준점(원점)에서 떨어뜨려놓는 Vector
	Vector offset = Vector(500, 200);

	_blocks.resize(MAX_Y);
	for (int y = 0; y < MAX_Y; y++)
	{
		_blocks[y].reserve(MAX_X);
		for (int x = 0; x < MAX_X; x++)
		{
			shared_ptr<Block> block = make_shared<Block>();
			Vector pos;
			pos.x = x * 19;
			pos.y = y * 19;
			block->SetCenter(pos + offset);
			block->SetType(Block::Type::BLOCKED);

			_blocks[y].push_back(block);
		}
	}
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			block->Update();
		}
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blockV : _blocks)
	{
		for (auto block : blockV)
		{
			block->Render(hdc);
		}
	}
}
