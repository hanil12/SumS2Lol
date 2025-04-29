#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>

using namespace std;

// Event Lock
// Producer - Consumer Pattern

queue<int> q;
std::mutex m;
HANDLE handle;

void Produce()
{
	while (true)
	{
		{
			unique_lock<std::mutex> lg(m);
			q.push(100);
		}

		::SetEvent(handle);
		this_thread::sleep_for(1000ms);
	}
}

void Consume()
{
	while (true)
	{
		::WaitForSingleObject(handle, INFINITE); // 대기

		unique_lock<std::mutex> lg(m);

		if (q.empty() == false)
		{
			auto data = q.front();
			q.pop();
			cout << data << endl;
		}
	}
}

int main()
{
	handle = CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Produce);
	std::thread t2(Consume);

	t1.join();
	t2.join();

	::CloseHandle(handle);

	return 0;
}