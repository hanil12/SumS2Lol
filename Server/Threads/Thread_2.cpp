#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <atomic>

using namespace std;

// CPU 파이프라인 :
// 세마포어 : 

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