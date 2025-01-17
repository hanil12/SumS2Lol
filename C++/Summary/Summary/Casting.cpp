#include <iostream>
#include <vector>

using namespace std;

// 캐스팅 : 형변환
// 암묵적 캐스팅
// int -> float (안전)
// float -> int (불안전)
// char -> int (안전)
// int -> char (불안전) => 크기가 큰 자료형에서 작은 자료형으로 캐스팅할 때 비트가 날아가므로 불안전


// class 설계도
// 객체(건물)를 찍어내는 설계도
// 객체
// - 속성(멤버변수)과 기능(멤버함수)을 갖고, 메모리에 할당되어있는 얘
//   attribute        method

// 업캐스팅
// - 자식 객체를 부모 포인터가 가리키게 할 수 있다. => 안전
// 다운캐스팅
// - 부모의 객체를 자식포인터가 가리킬 수 있다. => 불안전

// 캐스팅 4총사
// - static_cast
//  : 논리적으로 OK면 통과
//  => 컴파일을 통과시킬 것인가?
// 
// - dynamic_cast
//  : 상속구조에서, RTTI가 있으면 통과
//  - RTTI : Runtime Type Information
// => 실행 중에 통과시킬 것이냐?
// ==> 캐스팅에 실패하면 nullptr을 반환
// 
// - const_cast
// - reinterpret_cast
// => C스타일의 강제형변환, 

class Player
{
public:

	// 가상함수를 선언하면
	// 가상함수테이블(vftable) 생긴다
	// 객체의 맨 앞주소에는 가상함수테이블을 가리키는 포인터가 생긴다. => 실행 중에 타입이 무엇인지 확인할 수 있다.
	// -> RTTI
	virtual void Hello() { cout << "Im Player" << endl; }

	int type = 0;
	int _hp = 1;
	int _atk = 2;
};

class Knight : public Player
{
public:
	virtual void Hello() { cout << "Im Knight" << endl; }
	void Attack() {}

	int type = 1;
	int _stamina = 3;
};

int main()
{
	int aInt = static_cast<int>(1.5f); // C++ 기준에서 재해석
	float aFloat = 1.0f;
	int* ptr = reinterpret_cast<int*>(&aFloat);
	aInt = 455555;
	char aChar = aInt;

	cout << aInt << endl;
	cout << *ptr << endl;

	Player* p = new Player();
	Knight* k2 = static_cast<Knight*>(new Player()); // 다운캐스팅
	Player* k = new Knight(); // 업캐스팅

	Knight* dynamicK = dynamic_cast<Knight*>(k); 
	if (k->type == 1)
	{
		static_cast<Knight*>(k);
	}

	if (dynamicK != nullptr)
	{
		// 실제 Knight
		dynamicK->Hello();
		dynamicK->Attack();
	}
	else
	{
		// Knight가 아니였다.
	}

	const char* str = "Hello"; // rodata
	char* str2 = const_cast<char*>(str);
	// str2[0] = 'K'; // rodata에가서 H를 K로 바꿔줘,

	return 0;
}