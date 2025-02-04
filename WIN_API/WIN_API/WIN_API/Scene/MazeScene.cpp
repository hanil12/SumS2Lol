#include "framework.h"
#include "MazeScene.h"

#include "Objects/Maze/Block.h"
#include "Objects/Maze/Maze.h"
#include "Objects/Maze/Player.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_mazePlayer = make_shared<Player>(_maze);
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
	_mazePlayer->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);
}
