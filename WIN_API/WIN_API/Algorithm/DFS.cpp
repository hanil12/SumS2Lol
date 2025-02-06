#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

// DFS
// 스택구조를 이용해서 순회하는 방법
// => 스택프레임을 활용해서
// ==> 재귀함수

// BFS vs DFS
// 1. BFS : 길찾기(최단거리 찾기)
// 2. DFS : 길찾기를 제외한 모든 탐색 => 닫힌 계 찾기

vector<vector<bool>> adjacent;
vector<bool> visited;

void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));
	visited = vector<bool>(7, false);

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][3] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;
	//adjacent[1][4] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	//adjacent[2][5] = true;
	adjacent[2][6] = true;

	adjacent[3][0] = true;
	adjacent[3][3] = true;

	//adjacent[4][1] = true;
	adjacent[4][4] = true;

	//adjacent[5][2] = true;
	adjacent[5][5] = true;

	adjacent[6][2] = true;
	adjacent[6][6] = true;
}

void DFS(int here)
{
	visited[here] = true;
	cout << here << endl;

	for (int there = 0; there < adjacent.size(); there++)
	{
		if (here == there)
			continue;

		if (visited[there] == true)
			continue;

		if (adjacent[here][there] == false)
			continue;

		DFS(there);
	}
}

int main()
{
	CreateGraph();
	
	int count = 0;
	for (int i = 0; i < adjacent.size(); i++)
	{
		if (visited[i] == false)
		{
			count++;
			DFS(i);
		}
	}

	cout << "count : " << count << endl;

	return 0;
}