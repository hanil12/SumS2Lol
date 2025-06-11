
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

	Session* session = xnew<Session>();

	while (true)
	{
		// Accpet
		SOCKET clientSocket;
		SOCKADDR clientAddr;
		int32 addrLen = sizeof(clientAddr);

		clientSocket = ::accept(listener, (SOCKADDR*)&clientAddr, &addrLen);
		if(clientSocket == INVALID_SOCKET)
			continue;

		// Connect
		session->SetSocket(clientSocket);
		NetAddress clientNetAddr(*reinterpret_cast<SOCKADDR_IN*>(&clientAddr));
		session->SetNetAddress(clientNetAddr);
		cout << "Connected" << endl;
		TM->GetIocpCore()->Register(session); // IOCP에서 session을 감지하겠다.

		// 일감 등록
		// RECV 예약
		WSABUF wsaBuf;
		wsaBuf.buf = session->_recvBuffer;
		wsaBuf.len = 1000;
		DWORD recvLen = 0;
		DWORD flag = 0;

		RecvEvent* iocpEvent = xnew<RecvEvent>();
		::WSARecv(session->GetSocket(), &wsaBuf, 1, &recvLen, &flag, iocpEvent, nullptr);
	}

	TM->Join();

	SocketUtils::Close(listener);
	SocketUtils::Clear();

	TM->Delete();

	return 0;

	return 0;
}