#include "framework.h"

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
		READ_LOCK;

		// 아이디 추출

		return nullptr;
	}

	void Save();

public:
	USE_LOCK;
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
		READ_LOCK;

		// 계좌 정보를 갖고온다...

		return nullptr;
	}

	void Login();

public:
	USE_LOCK;
	static AccountManager* _instance;
};
AccountManager* AccountManager::_instance = nullptr;

void UserManager::Save()
{
	WRITE_LOCK;
	// 계좌를 확인하고 저장
	Account* account = AccountManager::GetInstance()->GetAccount(10);

	// 계정 저장
	// DB에 Update

	return;
}

void AccountManager::Login()
{
	WRITE_LOCK;

	User* user = UserManager::GetInstance()->GetUser(10);

	// User 정보를 확인하고 맞을 시에 통과
	// DB에서 확인

	return;
}

void Login()
{
	for(int i=0; i < 10000; i++)
		AccountManager::GetInstance()->Login();
}

void Save()
{
	for (int i = 0; i < 10000; i++)
		UserManager::GetInstance()->Save();
}

int main()
{
	TM->Create();

	AccountManager::Create();
	UserManager::Create();

	TM->Launch(Login);
	TM->Launch(Save);

	TM->Join();

	AccountManager::Delete();
	UserManager::Delete();

	TM->Delete();

	return 0;
}
