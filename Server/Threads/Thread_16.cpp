#include "framework.h"

class Player : public RefCountable
{
public:
	Player() { cout << "Player 생성자 호출!" << endl;}
	~Player() 
	{
		cout << "Player 소멸자 호출!" << endl; 
	}

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

void Fight(TSharedPtr<Player> p1, TSharedPtr<Player> p2)
{
	while (true)
	{
		p1->Attack();
		p2->Attack();

		if (p1->IsDead() || p2->IsDead())
			break;
	}
}

int main()
{
	ThreadManager::Create();

	TSharedPtr<Player> p1 = new Player();//1
	TSharedPtr<Player> p2 = new Player();//1

	p1->SetTarget(p2); // 2
	p2->SetTarget(p1); // 2

	TM->Launch([p1,p2]()->void
	{
		while (true)
		{
			this_thread::sleep_for(1000ms);
			break;
		}
	});

	TM->Join(); // 3, 3

	p1->ReleaseRef();
	p2->ReleaseRef();

	ThreadManager::Delete();

	return 0;
}