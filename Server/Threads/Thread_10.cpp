#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <Windows.h>

using namespace std;

// TLS : Thread Local Storage
// 각 쓰레드의 고유한 메모리 저장공간

thread_local int L_threadID;

void MySetThreadId(int id)
{
	L_threadID = id;

	while (true)
	{
		cout << "Hi Im Thread : " << L_threadID << endl;
		this_thread::sleep_for(3000ms);
	}
}

int main()
{
	vector<std::thread> threads;

	int count = std::thread::hardware_concurrency();
	for (int i = 0; i < count; i++)
	{
		threads.push_back(std::thread(MySetThreadId, i));
	}

	for(auto& t : threads)
		t.join();

	return 0;
}