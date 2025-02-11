#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// 안전한 정렬
// 임시배열을 만든다.

// 정복, 결합
void MergeResult(vector<int>& v, int left, int mid, int right)
{
	// 처음에 들어왔을 때는 제일 잘게 쪼개진 상태에서 시작
	// [30] , [55]
	// left = 1
	// right = 2
	// mid = 1

	int leftIndex = left;
	int rightIndex = mid + 1;
	vector<int> temp;

	// [30]         [55]
	// leftIndex,  rightIndex
	while (true)
	{
		if (leftIndex > mid || rightIndex > right)
			break;

		if (v[leftIndex] <= v[rightIndex])
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}

		// [30]         [55]
		//            rightIndex
		//             leftIndex
		else
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	// ... 왼쪽 혹은 오른쪽에 있던 배열들을 temp 배열에 복사한 상황

	// right쪽이 남아있었다...
	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}
	// left쪽이 남아있었다.
	else
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	// temp에 정렬된 배열이 복사
	// => temp를 v의 원본에 복사
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	// 기저사항 : 제일 잘게 쪼갰을 때
	if (left >= right)
		return;

	int mid = (left + right) / 2;

	// Divide
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	// Conquer And Combine
	MergeResult(v, left, mid, right);
}

int main()
{
	vector<int> v = { 55, 30, 15, 100, 1, 5, 30 };
	MergeSort(v, 0, v.size() - 1);

	std::sort(v.begin(), v.end()); // N x logN
	// 빠른 정렬

	std::partial_sort(v.begin(), v.begin() + 3, v.end()); // N x logM => 앞에 3개만 최대값으로 정렬
	
	std::stable_sort(v.begin(), v.end()); // N x logN
	// 안전한 정렬(같은 값일 경우 앞에있던 수가 무조건 앞에 있다.)
	// ... 임시배열 만든다.

	return 0;
}