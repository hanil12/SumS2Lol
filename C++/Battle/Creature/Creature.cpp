#include "pch.h"
#include "Creature.h"

Creature::Creature(int hp, int atk)
: _hp(hp)
, _atk(atk)
{
}

Creature::~Creature()
{
}

void Creature::TakeDamage(int amount, shared_ptr<Creature> attacker)
{
	_hp -= amount;

	if (_hp < 0)
		_hp = 0;
}

bool Creature::IsDead()
{
	return _hp <= 0;
}
