#include "framework.h"
#include "RWLock.h"

void RWLock::WriteLock()
{
	uint32 lockThreadID = (_lockFlag & WRITE_THREAD_MASK) >> 16;

	// 같은 Thread가 WriteLock 잡았었다.=> 통과
	if (LThreadID == lockThreadID)
	{
		_writeCount++;
		return;
	}

	int64 beginTick = ::GetTickCount64();
	
	// [wwwwwwww] [wwwwwwww] [rrrrrrrr] [rrrrrrrr]
	// 1. writeFlag 다른 누군가
	// 2. writeFlag = 0 , readFlag (...)
	// 3. writeFlag = 0 , readFlag = 0 (expected)

	uint32 desired = LThreadID << 16;
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32 expected = EMPTY_FLAG;
			if (_lockFlag.compare_exchange_strong(expected, desired))
			{
				_writeCount++;
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
		{
			CRASH("TIME OUT");
		}

		this_thread::yield();
	}
}

// [wwwwwwww] [wwwwwwww] [rrrrrrrr] [rrrrrrrr]
// & WRITE_THREAD_MASK
// [wwwwwwww] [wwwwwwww] [00000000] [00000000]

// [wwwwwwww] [wwwwwwww] [rrrrrrrr] [rrrrrrrr]
// & READ_THREAD_MASK
// [00000000] [00000000] [rrrrrrrr] [rrrrrrrr] => expected(아무도 WriteLock을 걸지 않은 것)
void RWLock::ReadLock()
{
	// ThreadID 추출
	uint32 lockThreadID = (_lockFlag & WRITE_THREAD_MASK) >> 16;

	// 같은 Thread가 WriteLock 잡았었다. => 통과
	if (LThreadID == lockThreadID)
	{
		_lockFlag.fetch_add(1);
		return;
	}

	// WriteLock 건 얘가 다른 얘 ... 불통과 =>  WriteFlag가 0이 아니였다 => SpinLock
	// WriteLock이 안걸려있었다... 통과  => WriteFlag가 0 => ReadCount++
	int64 beginTick = ::GetTickCount64();
	while (true)
	{
		for (uint64 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			// lockThreadID가 원자적으로 한번에 바꿔치기 해줘야한다.
			uint32 expected = (_lockFlag.load() & READ_COUNT_MASK); // => WriteFlag가 0 일 것이로 예상
			uint32 desired = expected + 1; // WriteFlag가 0이면 ReadCount를 1 올려주는 것을 희망
			if (_lockFlag.compare_exchange_strong(expected, desired))
			{
				return; // 통과
			}
		}

		// 스핀하면서 시간을 잿을 때 ACQUIRE_TIMEOUT_TICK보다 커지면, CRASH
		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
		{
			CRASH("TIME OUT");
		}

		this_thread::yield();
	}
}

void RWLock::WriteUnlock()
{
	// 자기 자신이 ReadLock을 건 다음, WriteLock이 걸리면 안되는데 걸렸을 때 예외처리
	if ((_lockFlag.load() & READ_COUNT_MASK) != 0)
	{
		CRASH("INVALID UNLOCK OREDER");
	}

	int32 lockCount = --_writeCount;
	if (lockCount == 0)
	{
		_lockFlag.store(EMPTY_FLAG);
	}
}

void RWLock::ReadUnlock()
{
	if ((_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
	{
		CRASH("MUTIPLE UNLOCK");
	}
}
