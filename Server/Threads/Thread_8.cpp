#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>

using namespace std;

__int64 Caculate()
{
	__int64 sum = 0;

	for (int i = 0; i < 100'0000; i++)
	{
		sum += i;
	}

	return sum;
}

void PromiseWorker(std::promise<string>& promise)
{
	promise.set_value("Set Massage");
}

void TaskWorker(std::packaged_task<__int64()>& task)
{
	task();
}

int main()
{
	// future
	{
		// std::launch::deferred : 지연시키셔서 나중에 실행
		// std::launch::async : 쓰레드를 하나 파서 실행

		// 비동기 방식으로 future에서 할 일을 만들고 나중에 반환받는 법.
		std::future<__int64> f = std::async(std::launch::async, Caculate);

		// TODO ... => f가 끝나던지 끝나지 않던지 간에 이 내용들이 실행
		int temp = 0;

		__int64 sum = f.get();

		cout << sum << endl;
	}

	// promise : 동기시점을 제공한다.
	{
		// 미래에 값을 설정 받을 변수
		std::promise<string> promise;
		std::future<string> future = promise.get_future(); // future에 반환하겠다 라는 약속

		std::thread t(PromiseWorker, std::ref(promise));

		std::future_status status = future.wait_for(10ms); // 0.01초 동안 대기하면서 future의 상태 확인
		if (status == future_status::ready)
		{
			// future가 세팅이 잘 되어있다 => 즉시 실행 가능
			string value = future.get();
			cout << value << endl;
		}

		t.join();
	}

	// packaged_task : 일감(function)을 만들어서 넘겨주는 방법
	{
		// task를 미래에 실행시켜서 그 반환값을 f_result에 돌려주겠다.
		std::packaged_task<__int64()> task(Caculate);
		std::future<__int64> f_result = task.get_future();

		std::thread t(TaskWorker, std::ref(task));

		__int64 sum = f_result.get();

		cout << sum << endl;

		t.join();
	}

	// Cacluate하는데 Event기반 Lock, Spin Lock, Sleep Lock 를 걸고 멀티쓰레드에서 작업하는 환경을 최소화
	// 작은 작업들을 하는데 비동기방식이 필요할 경우 => future
	// 예시) C# await 

	return 0;
}