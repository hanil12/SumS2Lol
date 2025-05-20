#include "framework.h"


class Player
{
public:
	Player() { cout << "Player의 생성자 호출" << endl; }
	~Player() { cout << "Player의 소멸자 호출" << endl; }

public:
	int _hp = 0;
	int _atk = 0;
};

class Knight : public Player
{
public:
	Knight() { cout << "Knight의 생성자 호출" << endl; }
	~Knight() { cout << "Knight의 소멸자 호출" << endl; }

public:
	int _stamina = 0;
};

int main()
{
	ThreadManager::Create();

	TM->Launch([]() 
	{
		Vector<Knight> k;
		k.resize(10);
	});

	Knight* k = xnew<Knight>();
	Player* p = xnew<Player>();

	reinterpret_cast<Knight*>(p)->_stamina = 10;

	xdelete(p);
	xdelete(k);

	TM->Join();

	ThreadManager::Delete();

	return 0;
}