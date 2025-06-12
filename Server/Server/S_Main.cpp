
#ifdef _DEBUG
#pragma comment(lib,"ServerCore\\Debug\\ServerCore.lib")
#else
#pragma comment(lib,"ServerCore\\Release\\ServerCore.lib")
#endif

#include "../ServerCore/pch.h"


int main()
{
	TM->Create();

	SocketUtils::Init();

	// Non Blocking
	shared_ptr<Listener> listener = make_shared<Listener>();
	NetAddress netAddress(L"127.0.0.1", 7777);
	listener->StartAccept(netAddress);

	// CP에서 완료된 정보를 감지하는 5개의 쓰레드 준비
	for (int32 i = 0; i < 5; i++)
	{
		TM->Instance()->Launch([=]()
		{ 
			while (true)
			{
				TM->GetIocpCore()->DisPatch();
			}
		});
	}

	while (true)
	{

	}

	TM->Join();

	SocketUtils::Clear();

	TM->Delete();

	return 0;

	return 0;
}