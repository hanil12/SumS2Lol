#include "framework.h"

class TestJob
{
	USE_LOCK

public:
	int TestRead()
	{
		READ_LOCK
		if(q.empty() == false)
			return q.front();

		return -1;
	}

	void TestPush()
	{
		WRITE_LOCK

		q.push(rand() % 100);
	}

	void TestPop()
	{
		WRITE_LOCK

		if(q.empty() == false)
			q.pop();
	}

private:
	queue<int> q;
};

TestJob GJob;

void ThreadRead()
{
	while (true)
	{
		int num = GJob.TestRead();
		cout << num << endl;
	}
}

void ThreadWrite()
{
	while (true)
	{
		GJob.TestPush();
		this_thread::sleep_for(3000ms);
		GJob.TestPop();
	}
}

int main()
{
	ThreadManager::Create();

	for (int i = 0; i < 2; i++)
	{
		TM->Launch(ThreadWrite);
	}

	for (int i = 0; i < 5; i++)
	{
		TM->Launch(ThreadRead);
	}

	TM->Join();

	ThreadManager::Delete();

	return 0;
}