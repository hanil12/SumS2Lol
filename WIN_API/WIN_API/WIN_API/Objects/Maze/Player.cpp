#include "framework.h"
#include "Player.h"

#include "Maze.h"
#include "Block.h"

Player::Player(shared_ptr<Maze> maze)
: _maze(maze)
{
	_maze.lock()->SetBlockType(_pos, Block::Type::PLAYER);

	RightHand();
}

Player::~Player()
{
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
	{
		return;
	}

	_delayTime += 0.3f;
	if (_delayTime > 1.0f)
	{
		_delayTime = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex > 0)
		{
			_maze.lock()->SetBlockType(_path[_pathIndex - 1], Block::Type::FOOTPRINT);
		}
		_maze.lock()->SetBlockType(_pos, Block::Type::PLAYER);

		_pathIndex++;
	}
}

void Player::RightHand()
{
	shared_ptr<Maze> maze = _maze.lock();

	Vector pos = maze->StartPos();
	Vector endPos = maze->EndPos();

	int curDir = Direction::UP;
	while (true)
	{
		if (pos == endPos)
			break;

		int newDir = (curDir - 1 + DIR_COUNT) % DIR_COUNT; // 순환
		Vector oldVector = pos + frontPos[curDir]; // 현재 바라보고 있던 방향으로 한칸 +
		Vector newVector = pos + frontPos[newDir]; // 오른쪽 방향으로 한칸 +

		// 오른쪽으로 갈 수 있다? => 오른쪽으로 방향을 바꾸고 그 방향으로 GO
		if (Cango(newVector))
		{
			curDir = newDir;
			pos = newVector;
			_path.push_back(pos);
		}

		// 오른쪽은 막혀있고 앞 방향은 뚫려있다? => 그대로 진행
		else if (Cango(oldVector))
		{
			pos = oldVector;
			_path.push_back(pos);
		}

		// 오른쪽 막혀있고, 진행방향도 막혀있다 => 왼쪽으로 회전
		else
		{
			curDir = (curDir + 1 + DIR_COUNT) % DIR_COUNT;
		}
	}

	stack<Vector> s;
	// 사이클 처리
	for (int i = 0; i < _path.size() - 1; i++)
	{
		maze->SetBlockType(_path[i], Block::Type::SEARCHED);

		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
			s.push(_path[i]);
	}

	_path.clear();
	while (true)
	{
		if (s.empty() == true)
			break;
		Vector top = s.top();
		_path.push_back(top);
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

bool Player::Cango(Vector pos)
{
	if (_maze.lock()->GetBlockType(pos) == Block::Type::BLOCKED)
		return false;
	return true;
}
