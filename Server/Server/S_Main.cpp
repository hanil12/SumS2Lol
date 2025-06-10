
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
	SOCKET listener = SocketUtils::CreateSocket();

	SocketUtils::BindAnyAddress(listener, 7777);
	SocketUtils::Listen(listener);

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
		// Accpet

		// Connect

		// 일감 등록
	}

	TM->Join();

	SocketUtils::Close(listener);
	SocketUtils::Clear();

	TM->Delete();

	return 0;

	return 0;
}