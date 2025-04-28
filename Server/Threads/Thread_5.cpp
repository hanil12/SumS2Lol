#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>

using namespace std;

// Spin Lock => mutex
// Lock이 풀릴 때까지 쓰레드 무한 반복 대기
// 
// Sleep Lock
// Lock이 잠겨있으면 Sleep 시키고, 다시 되돌아와서 확인 후 Sleep or Excute 결정
// Sleep : 운영체제에서 thead를 재운다.

// SleepLock의 단점
// - 자고 일어나서 왔을 때 이미 다른 쓰레드가 점유해서 최악의 경우 오랜 시간동안 일을 못할 수도 있다.

// SpinLock의 단점
// - thread가 쉬지 않고 계속 무한 루프

// Context Switching : 

int sum = 0;
std::mutex myMutex;

class SpinLock
{
public:
	void lock()
	{
		// 비교하고 값을 대입하는 과정이 한번에
		// CAS : Compare And Swap
		
		bool expected = false;
		bool desired = true;

		// compare_exchange_strong
		// if(_locked == expected)
		// {
		//		expected = _locked;
		//      _locked = desired
		//      return true;
		// }
		// else
		// {
		//		expected = _locked;
		//      return false;
		// }

		// t2 : _locked(true)
		while (_locked.compare_exchange_strong(expected, desired) == false)
		// 1. 만약 _locked가 false 였다.
		// _lock은 desired(true)로 바뀌고 true 리턴
		{
		// t1이 끝날 때까지 t2 대기
			expected = false;

			this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
      // t1
	}

	void unlock()
	{
		_locked.store(false);
	}

private:
	atomic<bool> _locked = false;
};

SpinLock _myLock;

void Add()
{
	for (int i = 0; i < 10000; i++)
	{
		lock_guard<SpinLock> lg(_myLock);
		sum++;
	}
}

void Sub()
{
	for (int i = 0; i < 10000; i++)
	{
		lock_guard<SpinLock> lg(_myLock);
		sum--;
	}
}


// 코드 최적화란?
int main()
{
	volatile int aInt = 1;
	aInt = 2;
	aInt = 3;
	aInt = 4;

	cout << aInt << endl;

	std::thread t1(Add);
	std::thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;


	return 0;
}