#include "framework.h"
#include "ThreadManager.h"

ThreadManager* ThreadManager::_instance = nullptr;
Atomic<int> ThreadManager::SThreadID = 0;

ThreadManager::ThreadManager()
{
	// mainThread만 호출가능
	InitTLS();
	// mainThread의 아이디 1
}

ThreadManager::~ThreadManager()
{
	// mainThread만 호출가능
	DestroyTLS();
}

void ThreadManager::Launch(function<void(void)> callback)
{
	LockGuard lg(_lock);

	_threads.push_back(thread([=]()-> void 
	{
		InitTLS();
		callback();
		DestroyTLS();
	}));
}

void ThreadManager::Join()
{
	LockGuard lg(_lock);

	bool clearCheck = true;

	for (auto& thread : _threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
		else
		{
			clearCheck = false;
		}
	}

	if (clearCheck)
	{
		_threads.clear();
	}
}

void ThreadManager::InitTLS()
{
	LThreadID = SThreadID.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{
}
