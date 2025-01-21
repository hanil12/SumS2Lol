#pragma once
#include "Player.h"

class Archer : public Player, public enable_shared_from_this<Archer>
{
public:
	Archer(int hp, int atk, string name);
	~Archer();

	// 함수 오버라이딩
	virtual void Attack(shared_ptr<Creature> other) override;

private:
};

