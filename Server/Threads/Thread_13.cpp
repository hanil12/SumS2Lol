#include "framework.h"

LockBasedStack<int> s;
queue<int> q;

void Push()
{
	while (true)
	{
		int value = rand() % 100;
		s.push(value);

		this_thread::sleep_for(1000ms);
	}
}

void Pop()
{
	while (true)
	{
		int out = -1;
	/*	if (s.tryPop(out))
		{
			cout << out << endl;
		}*/

		s.waitPop(out);
		cout << out << endl;
	}
}

void Push_Q()
{
	while (true)
	{
		q.push(rand() % 100);

		this_thread::sleep_for(1000ms);
	}
}

void Pop_Q()
{
	while (true)
	{
		if (q.empty() == false)
		{
			int out = q.front();
			q.pop();

			cout << out << endl;
		}
	}
}

int main()
{
	std::thread t1(Push_Q);
	std::thread t2(Pop_Q);
	std::thread t3(Pop_Q);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}