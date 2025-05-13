#pragma once

// 1. 공유변수를 읽거나 수정
//  Player;
// a,b,c threads
// a쓰레드 R / b쓰레드 R / c쓰레드 R

// => Spin Lock 같은 경우 c쓰레드는 a,b가 다 읽기 전까지 읽을 수 없다.

// 읽는 것만 할거면 다들 동시에 봐도 상관없지 않을까?

// [wwwwwwww] [wwwwwwww] [rrrrrrrr] [rrrrrrrr] => 32개의 비트
// 1. 여러 쓰레드가 'Read'만 할 경우 : readlock 몇 번 걸었는지 기입
// 2. 한 쓰레드가 'Write'할 경우 : ID 기입,  기입된 ID가 나랑 같다면 통과, 그게 아니면 Read, Write 불가
// 3. 누가 'Read'하고 있는데 'Write'를 할 경우 : 통과 X
// 4. 누가 'Write'하고 있는데 'Read'를 할 경우 : 통과 X

// RWLock 정책
// 1. Read는 상호베타적일 필요없이 공유 count만 올리겠다.
// 2. Write는 무조건 상호베타적이여야한다.
// => Write중에는 다른 쓰레드에서 Write를 시도할 수 없다.
// => Read중에는 다른 쓰레드에서 Write를 시도할 수 없다.
// * 내 Thread에서 Write하고 Read,Write하는 것은 가능하다.
// * 내 Thread에서 Read하고 Write하는 것 불가능

class RWLock
{
	enum : uint32
	{
		EMPTY_FLAG = 0x0000'0000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		ACQUIRE_TIMEOUT_TICK = 10000
	};

public:
	void WriteLock(const char* name);
	void ReadLock(const char* name);
	void WriteUnlock(const char* name);
	void ReadUnlock(const char* name);

private:
	Atomic<uint32> _lockFlag = 0;
	uint16 _writeCount = 0;
};

class ReadLockGuard
{
public:
	ReadLockGuard(RWLock& lock, const char* name) : _lock(lock), _name(name)
	{
		_lock.ReadLock(_name);
	}

	~ReadLockGuard()
	{
		_lock.ReadUnlock(_name);
	}

private:
	const char* _name;
	RWLock& _lock;
};

class WriteLockGuard
{
public:
	WriteLockGuard(RWLock& lock, const char* name) : _lock(lock), _name(name)
	{
		_lock.WriteLock(_name);
	}

	~WriteLockGuard()
	{
		_lock.WriteUnlock(_name);
	}

private:
	const char* _name;
	RWLock& _lock;
};
