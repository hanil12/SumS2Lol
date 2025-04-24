#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

//  - DeadLock : 교착상태
//    mutex가 2개 있는 상황

// - SpinLock
//    : CAS
// - SleepLock
// - EventLock
//    : CV

class AccountManager;

class User {};
class Account {};

class UserManager
{
private:
	UserManager() {}
	~UserManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new UserManager();
	}
	static void Delete()
	{
		if (_instance)
			delete _instance;
	}
	static UserManager* GetInstance() { return _instance; }

	User* GetUser(int id)
	{
		lock_guard<std::mutex> lg(_mutex);

		// 아이디 추출

		return nullptr;
	}

	void Save();

public:
	std::mutex _mutex;
	static UserManager* _instance;
};
UserManager* UserManager::_instance = nullptr;

class AccountManager
{
private:
	AccountManager() {}
	~AccountManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new AccountManager();
	}
	static void Delete()
	{
		if (_instance)
			delete _instance;
	}
	static AccountManager* GetInstance() { return _instance; }
	Account* GetAccount(int id)
	{
		lock_guard<std::mutex> lg(_mutex);

		// 계좌 정보를 갖고온다...

		return nullptr;
	}

	void Login();

public:
	std::mutex _mutex;
	static AccountManager* _instance;
};
AccountManager* AccountManager::_instance = nullptr;

int main()
{
	AccountManager::Create();
	UserManager::Create();

	std::thread t1([]()->void 
	{
			for (int i = 0; i < 10000; i++)
			{
				AccountManager::GetInstance()->Login();
			}
	});

	std::thread t2([]()->void
	{
			for (int i = 0; i < 10000; i++)
			{
				UserManager::GetInstance()->Save();
			}
	});

	t1.join();
	t2.join();

	return 0;
}

void UserManager::Save()
{
	lock_guard<std::mutex> lg(_mutex);

	// 계좌를 확인하고 저장
	Account* account = AccountManager::GetInstance()->GetAccount(10);

	// 계정 저장
	// DB에 Update

	return;
}

void AccountManager::Login()
{
	lock_guard<std::mutex> lg(_mutex);

	User* user = UserManager::GetInstance()->GetUser(10);

	// User 정보를 확인하고 맞을 시에 통과
	// DB에서 확인

	return;
}
