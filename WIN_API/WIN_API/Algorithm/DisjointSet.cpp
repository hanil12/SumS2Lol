#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

struct User
{
	int guildId = 0;

	// hp...
};

class NaiveDisJointSet;

void GuildSystem()
{
	vector<User> users;

	for (int i = 0; i < 1000; i++)
	{
		users.push_back({ i });
	}

	// 555번 째 유저가 , 1번 째 유저 길드에 병합
	users[555].guildId = users[1].guildId;

	// usrs[1]이 길드 3으로 들어갔다.
	// users[1].guildId = 3

	// guild ID가 2인 유저들이 1길드에 통합 => N만큼의 시간복잡도
	for (auto& user : users)
	{
		if (user.guildId == 2)
		{
			user.guildId = 1;
		}
	}

	NaiveDisJointSet set(1000);

	// 555번 째 유저가 , 1번 째 유저 길드에 병합
	set.Merge(555, 1);

	set.Merge(2, 1);
}

class NaiveDisJointSet
{
public:
	NaiveDisJointSet(int n)
	{
		_parent = vector<int>(n, 0);
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}


	// [0] [1] [2] [3] [4] [5]

	// => 5가 0의 산하로 들어갔다.
	// => 3이 5산하로 들어갔다.
	//   [0] [1] [2] [4]
	// [5][3] 
	// 

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}

	// [0] [1]  [4]
	// [5] [2]
	// [3]

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		// 같은 길드 소속이냐?
		if (uLeader == vLeader)
			return;

		_parent[uLeader] = vLeader;
	}

private:
	vector<int> _parent;
};

class DisJointSet
{
public:
	DisJointSet(int n)
	{
		_parent = vector<int>(n, 0);
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}

		_rank = vector<int>(n, 1);
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}


	//			        3
	//			       [3]  
	//			       [2]  [0]
	//               [4]  [5] [1]
	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		if (_rank[uLeader] > _rank[vLeader])
			std::swap(uLeader, vLeader);

		// vLeader의 랭크가 항상 크거나 같다.
		_parent[uLeader] = vLeader;

		// 같은 랭크를 가졌으면 vLeader의 크기 1증가.
		if (_rank[uLeader] == _rank[vLeader])
			_rank[vLeader]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

int main()
{
	GuildSystem();

	return 0;
}