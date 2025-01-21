#pragma once
class Creature
{
public:
	Creature(int hp, int atk);
	virtual ~Creature();

	virtual void Attack(shared_ptr<Creature> other) abstract;
	virtual void TakeDamage(int amount, shared_ptr<Creature> attacker = nullptr);

	bool IsDead();

	// C# getset
	string GetName() { return _name; }
	void SetName(string name) { _name = name; }

protected:
	int _hp;
	int _atk;
	string _name;
};

