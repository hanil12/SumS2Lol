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

	_delayTime += 0.1f;
	if (_delayTime > 1.0f)
	{
		_delayTime = 0.0f;
		_pos = _path[_pathIndex];

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

		int newDir = (curDir - 1 + DIR_COUNT) % DIR_COUNT; // ��ȯ
		Vector oldVector = pos + frontPos[curDir]; // ���� �ٶ󺸰� �ִ� �������� ��ĭ +
		Vector newVector = pos + frontPos[newDir]; // ������ �������� ��ĭ +

		// ���������� �� �� �ִ�? => ���������� ������ �ٲٰ� �� �������� GO
		if (Cango(newVector))
		{
			curDir = newDir;
			pos = newVector;
			_path.push_back(pos);
		}

		// �������� �����ְ� �� ������ �շ��ִ�? => �״�� ����
		else if (Cango(oldVector))
		{
			pos = oldVector;
			_path.push_back(pos);
		}

		// ������ �����ְ�, ������⵵ �����ִ� => �������� ȸ��
		else
		{
			curDir = (curDir + 1 + DIR_COUNT) % DIR_COUNT;
		}
	}
}

bool Player::Cango(Vector pos)
{
	if (_maze.lock()->GetBlockType(pos) == Block::Type::BLOCKED)
		return false;
	return true;
}
