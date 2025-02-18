#include <iostream>
#include <vector>

using namespace std;

// DP
// - 상향식, 하향식
// - 윈도우

vector<int> v;
int N;
int cache[301];

void Input()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;

		v.push_back(temp);
	}

	for (int i = 0; i < 301; i++)
	{
		cache[i] = -1;
	}
}

int DP(int n)
{
	// 기저
	if (n < 0)
		return 0;

	// 메모이제이션
	int& ref = cache[n];
	if (ref != -1)
		return ref;

	// 구하기
	// 한칸
	if(n > 0)
		ref = v[n] + v[n - 1] + DP(n - 3);

	// 두칸 뛰기
	ref = max(ref, v[n] + DP(n - 2));

	return ref;
}

int main()
{
	Input();

	cout << DP(v.size() - 1) << endl;

	return 0;
}