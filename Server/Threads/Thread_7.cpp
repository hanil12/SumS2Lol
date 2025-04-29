#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>

using namespace std;

// Event Lock
// Producer - Consumer Pattern

// CV : Condition Variable

queue<int> q;
std::mutex m;
condition_variable cv;

void Produce()
{
	while (true)
	{
		{
			unique_lock<std::mutex> lg(m);
			q.push(100);
		}

		cv.notify_all();
		this_thread::sleep_for(1000ms);
	}
}

void Consume()
{
	while (true)
	{
		unique_lock<std::mutex> lg(m);
		cv.wait(lg, []()-> bool 
		{
			return q.empty() == false;
		});

		auto data = q.front();
		q.pop();
		cout << "Q Data : " << data << endl;
		cout << "Q Size : " << q.size() << endl;
	}
}

int main()
{
	std::thread t1(Produce);
	std::thread t2(Consume);

	t1.join();
	t2.join();

	return 0;
}