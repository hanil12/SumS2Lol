#pragma once
#include "Monster.h"

class Player;

struct PlayerInfo
{
	weak_ptr<Player> player;
	int totalDamage;

	bool operator<(const PlayerInfo& other) const
	{
		if (totalDamage < other.totalDamage)
			return true;
		return false;
	}

	bool operator>(const PlayerInfo& other) const
	{
		if (totalDamage > other.totalDamage)
			return true;
		return false;
	}
};

class Boss : public Monster
{
public:
	Boss();
	~Boss();

	// Monster을(를) 통해 상속됨
	void Attack(shared_ptr<Creature> other) override;
	void AttackAggro();

	virtual void TakeDamage(int damage, shared_ptr<Creature> attacker) override;

private:
	vector<PlayerInfo> _aggroTable;
};

