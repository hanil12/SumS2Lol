#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <atomic>

using namespace std;

// CPU 파이프라인 :
// - Fetch : 읽기
// - Decode : 해석
// - Excute : 실행
// - Memory Access : 메모리 접근
// 
// 세마포어 : mutex와 다르게 자물쇠 개념이 아니고, 참조할 때 카운트를 하나씩 올리거나 감소시키는 것.

// 1. 원자성 (atomic)
// - all or nothing

atomic<int> sum = 0; 

void AddSum()
{
	for (int i = 0; i < 10000; i++)
	{
		sum.fetch_add(1);
	}
}

void SubSum()
{
	for (int i = 0; i < 10000; i++)
	{
		sum.fetch_sub(1);
	}
}

int main()
{
	vector<std::thread> threads;
	threads.resize(6);

	for (int i = 0; i < 3; i++)
	{
		threads[i] = std::thread(&AddSum);
	}

	for (int i = 3; i < 6; i++)
	{
		threads[i] = std::thread(&SubSum);
	}

	for(auto& t : threads)
		t.join();

	cout << sum << endl;

	return 0;
}