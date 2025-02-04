#include <iostream>
#include <stack>
#include <queue>

// stack, queue
// statck : 선입후출 -> First Input Last Out : FILO => 팬케이크 => Last Input First Out
// queue : 선입선출 -> First Input First Oout : FIFO => 줄 서는 것
using namespace std;

template<typename T, typename Container = vector<T>>
class Stack
{
public:
	void push(T value)
	{
		v.push_back(value);
	}

	void pop()
	{
		v.pop_back();
	}

	T top()
	{
		return v.back();
	}

	bool empty() { return v.empty(); }

private:
	Container v;
};

int main()
{
	stack<int>;
	Stack<int> s;

	s.push(10);
	s.push(1);
	s.push(15);
	s.push(6);
	s.push(100);

	while (true)
	{
		if (s.empty() == true)
			break;

		cout << s.top() << endl;
		s.pop();
	}

	return 0;
}