#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// 그래프
// Vertex와 edge로 이루어진 자료구조

// => 그래프의 순회 방법
// DFS(Deep First Search), BFS(Breadth First Seartch)
//  깊이 우선 탐색,           넓이 우선 탐색

// adjacent : 인접해있다.

// 인접리스트
vector<vector<int>> adjacent_list;
void CreateGraph_list()
{
	adjacent_list.resize(7);
	adjacent_list[0] = { 0,1,2,3 };
	adjacent_list[1] = { 0,1,4 };
	adjacent_list[2] = { 0, 2, 5,6 };
	adjacent_list[3] = { 0,3 };
	adjacent_list[4] = { 1,4 };
	adjacent_list[5] = { 2,5 };
	adjacent_list[6] = { 2,6 };
}

vector<vector<bool>> adjacent; // 인접행렬
// - 데이터를 많이 먹더라도, 탐색하는데 상수의 시간이 걸린다.
void CreateGraph()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false)); // 7x7
	//adjacent.resize(7, vector<bool>(7,false))

	// 양방향은 그래프 A는 A와 전치행렬(A)와 서로 같다.

	//   0  1  2  3  4  5  6
	// 0 1  1  1  1  0  0  0
	// 1 1  1  0  0  1  0  0
	// 2 1  0  1  0  0  1  1
	// 3 1  0  0  1  0  0  0
	// 4 0  1  0  0  1  0  0
	// 5 0  0  1  0  0  1  0
	// 6 0  0  1  0  0  0  1

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][3] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;
	adjacent[1][4] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][5] = true;
	adjacent[2][6] = true;

	adjacent[3][0] = true;
	adjacent[3][3] = true;

	adjacent[4][1] = true;
	adjacent[4][4] = true;
	
	adjacent[5][2] = true;
	adjacent[5][5] = true;

	adjacent[6][2] = true;
	adjacent[6][6] = true;
}

int main()
{
	CreateGraph_list();
	// 0과 2가 현재 연결이 되어있냐?
	auto iter = std::find(adjacent_list[0].begin(), adjacent_list[0].end(), 2);

	if (iter != adjacent_list[0].end())
		cout << *iter << endl;

	CreateGraph();
	// 0과 2가 현재 연결되어있냐?
	if (adjacent[0][2]) // 상수의 시간
	{
		cout << "0과 2가 연결되어있습니다." << endl;
	}

	return 0;
}