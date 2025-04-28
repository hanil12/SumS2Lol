#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>

using namespace std;

// 쓰는 이유:
// 1. 비동기 프로그램, 넌블락킹 (하나의 함수가 끝날 때까지 다른 함수를 실행시키지 못하는 것)
// 2. 효율적으로 쓰기위해서

void HelloThread()
{
	cout << "Hello Thread!" << endl;
}

int main()
{
	std::thread t(&HelloThread);

	t.join();
	// join : t가 끝날 때까지 대기
	// joinable : join 가능한지
	// get_id : 쓰레드 아이디
	// detach : 쓰레드 분리
	// hardware_concurrency : 현재 운용가능한 쓰레드의 개수

	return 0;
}
