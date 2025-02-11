#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left]; // 50
	int lowIndex = left + 1;
	int highIndex = right;

	while (true)
	{
		if (lowIndex > highIndex)
			break;

		if (lowIndex <= right && pivot > v[lowIndex])
		{
			lowIndex++;
		}

		if (highIndex >= left && pivot < v[highIndex])
		{
			highIndex--;
		}

		if (lowIndex < highIndex)
		{
			std::swap(v[lowIndex], v[highIndex]);
		}
	}

	std::swap(v[highIndex], v[left]);

	return highIndex;
}

void QuickSort(vector<int>& v, int left, int right)
{
	// 기저사항
	if (left > right)
		return;

	int pivotIndex = Partition(v, left, right);
	cout << left << " ~ " << pivotIndex - 1 << endl;

	QuickSort(v, left, pivotIndex - 1);
	QuickSort(v, pivotIndex + 1, right);
}

int main()
{
	vector<int> v = { 55, 30, 15, 100, 1, 5, 70, 120 };

	// 시간복잡도 : N x logN
	QuickSort(v, 0, v.size() - 1);
	//std::sort(v.begin(), v.end())

	return 0;
}