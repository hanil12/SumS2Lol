#include "framework.h"

// 허상포인터와 메모리 오염
// 가상메모리 vs 물리적메모리
// MMU와 운영체제의 페이징

// 가상메모리
// 1. 가상메모리의 주소와 물리적 메모리의 주소가 서로 다르다.
// 2. 가상메모리에는 RAM만 포함되지 않을 수 있다.(보조기억장치의 메모리 일부를 쓸 수 있다.)
// => 필요한 전체 데이터를 RAM 올리지 않아도 쓸 수 있다.

// MMU(Memory Managerment Unit)
// 가상메모리의 주소를 물리적메모리 주소로 번역.
// 운영체제 데이터에 접근을 막는다. 혹은 다른 프로그램의 주소값을 건드는 행위를 막는다.

// 페이징
// 운영체제가 메모리를 할당하고 관리할 때는 '페이지' 단위로 관리를 하는 것.
// 1. 각 프로세스한테 가상메모리를 주고 유저레벨에서 서로 간섭할 수 없게 만든다.
// 2. 메모리 파편화를 막을 수 있다. (페이지 단위를 늘릴 경우)

// => 물리적 메모리는 운영체제가 담당하겠다.

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
	Player* p = new Player(); // T1

	p->_hp = 10;
	p->_atk = 5;

	delete p;  // T2

	// p는 허상포인터(Dangling Pointer)
	p->_hp = 50; // 메모리 오염    T1

////////////////////////////////////////////////////
// Release에서 메모리오버플로우가 일어나도 정상적으로 실행이된다.
	Knight* k = reinterpret_cast<Knight*>(new Player());

	//k->_stamina = 50;

	delete k;
////////////////////////////////////////////////////

	SYSTEM_INFO s_info;
	::GetSystemInfo(&s_info);

	cout << s_info.dwPageSize << endl; // 페이지 한개당 사이즈 4KB
	cout << s_info.dwAllocationGranularity << endl; // 메모리를 할당할 때 이 숫자의 배수로 할당 : 2B

	int* temp = (int*)::VirtualAlloc(nullptr, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	*temp = 100;

	::VirtualFree(temp, 0, MEM_RELEASE);

	(*temp) = 10; // 허상포인터, 메모리 오염
	// new, delete는 바로 VirtualAlloc, Free를 해주지 않는다.

	return 0;
}