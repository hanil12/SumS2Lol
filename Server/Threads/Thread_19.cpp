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
	// 메모리 누수 발생-> 7일마다 점검해서 해제
	// 메모리 오염 발생-> 추적

	// StompAllocator를 이용하여 메모리 오염 방지 -> Debug
	Player* p = xnew<Player>();

	p->_hp = 10;

	//Knight* k = reinterpret_cast<Knight*>(p);
	//k->_stamina = 5;

	xdelete(p);

	//p->_hp = 5;

	// STLAllocator를 이용하여 STL의 Container를 쓸 때 메모리 오염 및 허상포인터 방지
	// Vector<Player> players = {Player(), Player(), Player()};

	MemoryPool pool1(100);

	MemoryHeader* header = pool1.Pop();
	Player* p1 = reinterpret_cast<Player*>(MemoryHeader::AttachHeader(header, sizeof(Player)));

	p1->_hp = 100;
	p1->_atk = 10;

	ThreadManager::Delete();

	return 0;
}