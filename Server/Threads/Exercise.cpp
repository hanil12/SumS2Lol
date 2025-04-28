// 소수 구하기 (1 ~ 100,000)에서 소수가 몇개 있는지
// 1. 단일 쓰레드에서
// 2. 멀티 쓰레드
#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>

using namespace std;

int MAX_C = 1000000;

bool IsPrime(int num)
{
	if(num == 0 || num == 1)
		return false;

	if(num == 2 || num == 3)
		return true;

	int count = sqrt(num);

	for (int i = 2; i <= count; i++)
	{
		if(num % i == 0)
			return false;
	}

	return true;
}


int main()
{
	__int64 start = GetTickCount64();

	int OneCount = 0;
	for (int i = 0; i < MAX_C; i++)
	{
		if (IsPrime(i))
		{
			OneCount++;
		}
	}

	__int64 end = GetTickCount64();
	cout << OneCount << endl;
	cout << end - start << "ms" << endl;

	start = GetTickCount64();
	// 작업
	atomic<int> primeCount = 0;

	vector<std::thread> threads;
	int threadCount = thread::hardware_concurrency();
	int jobCount = (MAX_C / threadCount); // 100000

	for (int i = 0; i < threadCount; i++)
	{
		// thread 9개
		// thread1 : 1 ~ 10000
		// thread2 : 10000 ~ 20000
		// ...
		int start = (i * jobCount);
		int end = min(MAX_C,(i + 1) * jobCount);

		threads.push_back(thread(([start, end, &primeCount]()->void
			{
				for (int i = start; i < end; i++)
				{
					if (IsPrime(i))
						primeCount.fetch_add(1);
				}
			})));
	}

	for(auto& t : threads)
		t.join();

	end = GetTickCount64();

	__int64 temp = end -start;
	cout << primeCount << endl;
	cout << end - start << "ms" << endl;

}