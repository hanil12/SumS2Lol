#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <Windows.h>

using namespace std;

// undefined behavior

// 메모리 정책
// - memory_order::relaxed
// => 느슨한, 코드재배치 O, 메모리 가시성 해결X
// 
// - memory_order::seq_cst
// => 가장 엄격한, 코드재배치X, 가시성 문제 해결O
//
// - memory_order::acquire, release

atomic<bool> ready;
int value;

void Produce()
{
	value = 10;
	ready.store(true, memory_order_seq_cst);
	// 절취선
}

void Consume()
{
	while(ready.load(memory_order_seq_cst) == false)
	;

	cout << value << endl;
}

int main()
{
	std::thread t1(Produce);
	std::thread t2(Consume);

	t1.join();
	t2.join();

	return 0;
}