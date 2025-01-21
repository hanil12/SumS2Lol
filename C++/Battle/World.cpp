#include "pch.h"

#include "Creature/Boss.h"
#include "Creature/Player.h"
#include "Creature/Knight.h"
#include "Creature/Archer.h"

#include "World.h"

World::World()
{
    _boss = make_shared<Boss>();

	for (int i = 0; i < 10; i++)
	{
		int randNum = rand() % 2;

		if (randNum == 0)
		{
			_players.push_back(make_shared<Knight>(100, 10, "Knight"));
		}
		else
		{
			_players.push_back(make_shared<Archer>(100, 10, "Archer"));
		}
	}
}

World::~World()
{
}

void World::Update()
{
	for (auto player : _players)
	{
		player->Attack(_boss);
	}

	shared_ptr<Boss> boss = dynamic_pointer_cast<Boss>(_boss);
	if (boss != nullptr)
	{
		boss->AttackAggro();
	}

}

bool World::End()
{
	if (_boss->IsDead())
		return true;

	for (auto player : _players)
	{
		if (!player->IsDead())
		{
			return false;
		}
	}

	return true;
}
