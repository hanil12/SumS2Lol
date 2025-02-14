#include <string>
#include <vector>

using namespace std;

// 프로그래머스 정수 삼각형

vector<vector<int>> cache;
vector<vector<int>> arr;
int N = 0;

int DP_UP(int y, int x)
{
    if (y == 0 && x == 0)
        return arr[y][x];

    if (x < 0)
        return -1;

    // y...1, x...1
    int left = DP_UP(y - 1, x - 1);
    int right = DP_UP(y - 1, x);

    if (left > right)
        return arr[y][x] + left;
    else
        return arr[y][x] + right;
}

int DP_DOWN(int y, int x)
{
    if (y == N - 1)
        return arr[y][x];

    int& ref = cache[y][x];

    if (ref != -1)
        return ref;


    int left = arr[y][x] + DP_DOWN(y + 1, x);
    int right = arr[y][x] + DP_DOWN(y + 1, x + 1);

    return ref = std::max(left, right);
}