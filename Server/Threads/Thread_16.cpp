#include "framework.h"

class Player : public RefCountable
{
public:
	Player() { cout << "Player 생성자 호출!" << endl;}
	~Player() {cout << "Player 소멸자 호출!" << endl; }

	void SetTarget(TSharedPtr<Player> target)
	{
		_target = target;
	}

	void Attack()
	{
		if (_target != nullptr)
		{
			_target->_hp -= _atk;
		}
	}

	bool IsDead()
	{
		return _hp <= 0;
	}

private:
	TSharedPtr<Player> _target = nullptr;

	int _hp = 10;
	int _atk = 1;
};

int main()
{
	ThreadManager::Create();

	TSharedPtr<Player> p1 = new Player();
	TSharedPtr<Player> p2 = new Player();

	p1->SetTarget(p2);

	ThreadManager::Delete();

	return 0;
}