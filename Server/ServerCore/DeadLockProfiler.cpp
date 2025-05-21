#include "pch.h"
#include "DeadLockProfiler.h"

void DeadLockProfiler::PushLock(const char* name)
{
	LockGuard lg(_lock);

	int32 lockId = 0;

	auto findIt = _nameToId.find(name);
	if (findIt == _nameToId.end())
	{
		lockId = static_cast<int32>(_nameToId.size());
		_nameToId[name] = lockId;
		_idToName[lockId] = name;
	}
	else
	{
		lockId = findIt->second;
	}

	// ... 미리 Lock이 있었다.
	if (_lockStack.empty() == false)
	{
		const int32 prevID = _lockStack.top();
		if (lockId != prevID)
		{
			set<int32>& history = _lockHistory[prevID];
			if (history.find(lockId) == history.end())
			{
				history.insert(lockId);
				CheckCycle();
			}
		}
	}

	_lockStack.push(lockId);
}

void DeadLockProfiler::PopLock(const char* name)
{
	LockGuard lg(_lock);

	if(_lockStack.empty())
		CRASH("MULTIPLE POP");

	int32 lockID = _nameToId[name];
	if(_lockStack.top() != lockID)
		CRASH("UNVALID POP");

	_lockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	const int32 lockCount = static_cast<int32>(_nameToId.size());

	_discoveredOrder = vector<int32>(lockCount, -1); // 순서기입
	_discoveredCount = 0;
	_finished = vector<bool>(lockCount, false);
	_parent = vector<int32>(lockCount, -1); // 부모 기입

	for (int32 lockID = 0; lockID < lockCount; lockID++)
	{
		DFS(lockID);
	}

	_discoveredOrder.clear();
	_finished.clear();
	_parent.clear();
}

void DeadLockProfiler::DFS(int32 here)
{
	if(_discoveredOrder[here] != -1)
		return;

	_discoveredOrder[here] = _discoveredCount++;

	auto findIt = _lockHistory.find(here);

	// here에서 인접한 정점이 없다.
	// 첫번째 락이자 마지막 락
	if (findIt == _lockHistory.end())
	{
		_finished[here] = true;
		return;
	}

	set<int32>& thereSet = findIt->second;
	for (int32 there : thereSet)
	{
		// 인접해있냐? {}

		// 자기자신이냐? {}

		// 방문 되어있냐?
		if (_discoveredOrder[there] == -1)
		{
			_parent[there] = here;
			DFS(there);
			continue;
		}

		// here 방문체크, there는 이미 방문
		// 순방향 간선
		if(_discoveredOrder[here] < _discoveredOrder[there])
			continue;

		// 순방향간선이 아니고, there가 here보다 더 작다? => there는 here의 선조 => 역방향간선 혹은 Cycle발생
		// there의 DFS가 끝나지 않았었다.
		if (_finished[there] == false)
		{
			// 백트래킹해서 어디에서 어디부터까지 DEADLOCK 경로 출력
			cout << _idToName[here] << " -> " << _idToName[there] << endl;

			int32 now = here;
			while (true)
			{
				cout << _idToName[_parent[now]] << " -> " << _idToName[now] << endl;
				now = _parent[now];
				if(now == there)
					break;
			}

			CRASH("DEADLOCK_DETECTED");
		}
	}

	_finished[here] = true;
}
