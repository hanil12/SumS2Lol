#include "pch.h"
#include "Creature.h"
#include "Player.h"
#include "Goblin.h"
#include "Knight.h"

Knight::Knight(int hp, int atk, string name)
: Player(hp,atk,name)
{
}

Knight::~Knight()
{
}

void Knight::Attack(shared_ptr<Creature> other)
{
	if (IsDead()) return;

	cout << _name << " Knight Attack!!!" << endl;
	other->TakeDamage(_atk, shared_from_this());
}
