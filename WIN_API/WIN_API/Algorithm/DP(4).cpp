#include <iostream>
#include <vector>

using namespace std;

// LIS (부분 증가 수열)의 최대합
// { 10 , 5 , 6, 7, 9 } 증가수열X
// 부분 증가 수열
// {7,9}, {6,9} ... {5 ,7 ,9}
// 
// {1, 10, 11, 15, 30} 증가수열

// { 10 , 5 , 6, 7, 9 }
// 5 + 6 + 7 + 9

// {1, 10, 11, 15, 30}
// 1 + 10 + 11 + 15 + 30

// {10,7,5,3}
// 10

// {15, 30, 10, 17, 50}


int LIS(int n) // Longest Increasing Sequence의 최대합 구하기
{
	return 0;
}

int main()
{
	vector<int> v = { 1,10,11,15,30 };

	int anwser = 0;

	cout << anwser << endl;

	return 0;
}