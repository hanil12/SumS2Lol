#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>

using namespace std;

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
