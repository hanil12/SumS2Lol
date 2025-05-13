#pragma once
class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle();
	void DFS(int32 here);

private:
	Mutex _lock;

	unordered_map<const char*, int32> _nameToId;
	unordered_map<int32, const char*> _idToName;

	stack<int32>					 _lockStack;
	map<int32,set<int32>>			 _lockHistory; // adjacent 역할

	//DFS
	vector<int32>		_discoveredOrder; // 노드가 발견된 순서를 기입
	int32				_discoveredCount = 0;
	vector<bool>		_finished; // 현재 index의 DFS가 다 통과되었는지 여부
	vector<int32>		_parent;
};

