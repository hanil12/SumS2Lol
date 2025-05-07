#pragma once

#include <stack>
#include <mutex>
#include <condition_variable>

template<typename T>
class LockBasedStack
{
public:
	void push(const T& value)
	{
		std::unique_lock<std::mutex> lg(m);

		s.push(value);

		cv.notify_one();
	}

	bool tryPop(T& out)
	{
		std::unique_lock<std::mutex> lg(m);

		if(s.empty())
			return false;

		out = s.top();
		s.pop();

		return true;
	}

	void waitPop(T& out)
	{
		// 값이 들어올 때까지 대기하다가 들어오면 pop시켜주는 용도
		std::unique_lock<std::mutex> ul(m);
		cv.wait(ul, [this]()->bool 
		{ 
			if(this->s.empty() == false)
				return true;
			return false;
		});

		out = s.top();
		s.pop();
	}

private:
	std::stack<T> s;
	std::mutex m;
	std::condition_variable cv;
};