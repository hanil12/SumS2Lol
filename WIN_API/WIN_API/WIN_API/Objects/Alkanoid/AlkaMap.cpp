#include "framework.h"
#include "AlkaMap.h"

#include "Brick.h"
#include "AlkaBall.h"
#include "AlkaItem.h"
#include "Bar.h"

AlkaMap::AlkaMap()
{ 
	_bricks.resize(_countY);

	Vector offset;
	int x = ((_brickSize.x + _brickGap.x) * _countX) / 2.0f;

	Vector temp = CENTER;
	offset.x = temp.x - x;
	offset.y = 200.0f;

	for (int y = 0; y < _countY; y++)
	{
		for (int x = 0; x < _countX; x++)
		{
			shared_ptr<Brick> brick = make_shared<Brick>(_brickSize);

			Vector brickPos;
			brickPos.x = (_brickSize.x + _brickGap.x) * x;
			brickPos.y = (_brickSize.y + _brickGap.y) * y;

			brick->SetPos(brickPos + offset);
			brick->_isActive = true;
			_bricks[y].push_back(brick);
		}
	}
}

AlkaMap::~AlkaMap()
{
}

void AlkaMap::Init(shared_ptr<Bar> bar)
{
	shared_ptr<AlkaItem> item = make_shared<AlkaItem>();
	item->SetSkill(std::bind(&Bar::TwoBall_Skill, bar));
	_items.push_back(item);
	_bricks[0][0]->SetItem(item);
}

void AlkaMap::Update()
{
	for (auto bricks : _bricks)
	{
		for (auto brick : bricks)
		{
			brick->Update();
		}
	}

	for (auto item : _items)
		item->Update();
}

void AlkaMap::Render(HDC hdc)
{
	for (auto bricks : _bricks)
	{
		for (auto brick : bricks)
		{
			brick->Render(hdc);
		}
	}

	for (auto item : _items)
		item->Render(hdc);
}

void AlkaMap::IsCollision_Bricks(shared_ptr<AlkaBall> ball)
{
	for (auto bricks : _bricks)
	{
		for (auto brick : bricks)
		{
			if (brick->_isActive == false)
				continue;

			if (brick->GetCollider()->IsCollision(ball->GetCollider()) == false)
				continue;

			brick->Break_Brick();

			// 좌우 사이에 있었다.
			if (ball->GetPos().x < brick->GetCollider()->Right() && ball->GetPos().x > brick->GetCollider()->Left())
			{
				Vector curDir = ball->GetDir();
				curDir.y *= -1.0f;

				ball->SetDir(curDir);
			}

			// 위 아래 사이에 있었다.
			else
			{
				Vector curDir = ball->GetDir();
				curDir.x *= -1.0f;

				ball->SetDir(curDir);
			}
		}
	}
}

void AlkaMap::GetItems(shared_ptr<Bar> bar)
{
	for (auto item : _items)
	{
		// item과 bar 충돌 했을 때...
		if (item->GetCollider()->IsCollision(bar->GetCollider()))
		{
			// 충돌
			item->ActiveSkill();
		}
	}
}
