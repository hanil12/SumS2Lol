#include <iostream>
#include <vector>

using namespace std;

vector<string> babbling = { "aya", "ye", "woo", "ma" };

vector<string> canBabbling;
// DFS
vector<bool> visited;

void DFS(int here, string str)
{
	visited[here] = true;
	str += babbling[here];
	canBabbling.push_back(str);

	for (int there = 0; there < 4; there++)
	{
		if (here == there)
			continue;
		if (visited[there])
			continue;

		DFS(there, str);

	}
	visited[here] = false;
}

int main()
{
	visited = vector<bool>(4, false);

	for (int i = 0; i < 4; i++)
	{
		DFS(i, "");
	}

	return 0;
}