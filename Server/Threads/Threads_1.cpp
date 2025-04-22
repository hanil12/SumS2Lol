#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>

using namespace std;

// 1. 프로세스 vs 쓰레드?
// 2. CPU 코어 vs 쓰레드 상관관계

// 식당
// 1. 손님 응대 < 1
// 2. 음식 조리
// 3. 서빙
// 4. 설거지 < 2
// 5. 계산기

// thread : 알바, PAWN

void HelloThread()
{
	cout << "Hello Thread!" << endl;
}

int sum = 0;

void AddSum()
{
	for(int i=0; i < 10000; i++)
		sum++;
}

void SubSum()
{
	for (int i = 0; i < 10000; i++)
		sum--;
}

int main()
{
	vector<std::thread> threads;

	for(int i=0; i < 5;i++)
		threads.push_back(std::thread(AddSum));
	
	for (int i = 0; i < 5; i++)
		threads.push_back(std::thread(SubSum));

	for(auto& t : threads)
		t.join();

	cout << sum << endl;

	return 0;
}
