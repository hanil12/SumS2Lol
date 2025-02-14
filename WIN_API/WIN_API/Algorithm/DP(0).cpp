#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

// DP : Dynamic Programming 동적계획법
// 수학자

// => 최적화

// 1. 점화식 찾기 : 최적 부분 구조
//  : 이전에 구한 답이 다음 답을 구할 때 쓰인다.
// => 이전 구한 답을 미리 적어놓자.(메모이제이션)
// 
// 2. 기저사항 찾기
// 3. 캐쉬설계


// 피보나치 수열
// f(0) = 1
// f(1) = 1
// f(n) = f(n-1) + f(n-2) ...점화식

// f(2) ... 2
// f(3) ... 3
// f(4) ... 5
// f(5) ... 8
// f(10) ...
int countA = 0;
int Fibonacci(int n)
{
	if (n == 0 || n == 1)
		return 1;

	if (n == 2)
		countA++;

	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

// n... 1000이하
vector<int> cache = vector<int>(1001, -1);
int FibonacciDP(int n)
{
	// 기저사항
	if (n == 0 || n == 1)
		return 1;
	if (n == 2)
	{
		countA++;
	}

	// 메모이제이션
	int& ref = cache[n];
	if (ref != -1)
	{
		return ref;
	}

	// 구하기
	return ref = FibonacciDP(n - 1) + FibonacciDP(n - 2);
}

int main()
{
	__int64 start = GetTickCount64();

	cout << FibonacciDP(70) << endl;

	cout << "f(2)가 호출된 횟수" << countA << endl;
	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;

	return 0;
}