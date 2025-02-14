#include <iostream>
#include <vector>

using namespace std;

// 재련하기
// 강화는 하는데, +1, +2, +3
// n강을 하고 싶다.
// => 이 때 나올 수 있는 경우의 수
// 0 < n < 3000
// 

// ex) 3강을 하고 싶다.
// 1 1 1
// 1 2
// 2 1
// 3
// 4

// ex) 4강
// DP[3] + DP[1]
// DP[2] + DP[2]
// DP[1] + DP[3]

vector<int> cache = vector<int>(3001, -1);
int Enchant(int n)
{
	// 하향식
	if (n == 0 || n == 1)
		return 1;
	if (n < 0)
		return 0;

	int& ref = cache[n];
	if (ref != -1)
		return ref;

	return ref = Enchant(n - 1) + Enchant(n - 2) + Enchant(n - 3);
}

int main()
{

	cout << Enchant(3) << endl; // 4

	return 0;
}