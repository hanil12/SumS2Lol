#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

vector<int> v;
std::mutex m;

// lock
// mutex : mutual exclusion

// RAII : Resource Acquisition is Initilization 
// 리소스 획득은 초기화, 리소스 드랍은 소멸

template<typename T>
class LockGuard
{
public:
	LockGuard(T* mutex) : _mutex(mutex) { _mutex->lock(); } // mutex 획드
	~LockGuard() { _mutex->unlock(); }

private:
	T* _mutex;
};

void Push(int num)
{
	LockGuard<std::mutex> lg(&m);

	v.push_back(num);
}

int main()
{
	std::thread t1([]()-> void
	{
			for (int i = 0; i < 1000; i++)
			{
				Push(i);
			}
	});

	std::thread t2([]()-> void
		{
			for (int i = 0; i < 1000; i++)
			{
				Push(i);
			}
		});

	t1.join();
	t2.join();

	cout << v.size() << endl;

	return 0;
}