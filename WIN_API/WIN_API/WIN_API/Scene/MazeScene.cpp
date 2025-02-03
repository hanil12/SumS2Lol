#include "framework.h"
#include "MazeScene.h"

#include "Objects/Maze/Block.h"
#include "Objects/Maze/Maze.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);
}
