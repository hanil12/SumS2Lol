#pragma once

class Maze;

class MazeScene : public Scene
{
public:
	MazeScene();
	~MazeScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<Maze> _maze;
};

