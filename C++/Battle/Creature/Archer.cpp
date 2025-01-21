#include "pch.h"
#include "Archer.h"

Archer::Archer(int hp, int atk, string name)
: Player(hp, atk, name)
{
}

Archer::~Archer()
{
}

void Archer::Attack(shared_ptr<Creature> other)
{
	if (IsDead()) return;

	cout << _name << " Archer Attack!!!" << endl;
	other->TakeDamage(_atk, shared_from_this());
}
