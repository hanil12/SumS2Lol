#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <Windows.h>

using namespace std;

// 코드 재배치가 왜 발생하는가
// 1. 컴파일러
// 2. CPU 파이프라인
// => 시간 오래걸리는 작업이 뒤늦게 실행될 수도 있다.
// r1 = x;  Load x  => Load 부분이 뒤늦게 실행될 수도 있다 => cache
// y = 1;  Store y 

// CPU 파이프라인
// - Fetch : 읽기
// - Decode : 해석
// - Excute : 실행
// - Memory Access : 메모리 접근

// 메모리 가시성
// 1. CPU의 캐시들이 독립적으로 저장하기 때문에, 실행 순서를 보장받지 못하는 것
// => C++ 11 이후 atomic => 가시성 해결
// ==> 모든 쓰레드들이 해당 변수의 동일한 수정 순서를 관찰한다. (all or nothing)

int x = 0;
int y = 0;
int r1 = 0;
int r2 = 0;

volatile bool ready;

void Thread_1()
{
	while(!ready)
	;

	r1 = x; // Load x
	y = 1; // Store y
}

void Thread_2()
{
	while(!ready)
	;

	x = 1; // Store x
	r2 = y; // Load y
}

int main()
{
	int count = 0;

	while (true)
	{
		ready = false;
		count++;

		x = y = r1 = r2 = 0;

		std::thread t1(Thread_1);
		std::thread t2(Thread_2);

		ready = true;

		t1.join();
		t2.join();

		if(r1 == 0 && r2 == 0)
			break;
	}

	cout << count << endl;

	return 0;
}