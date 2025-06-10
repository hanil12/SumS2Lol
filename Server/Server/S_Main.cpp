
#ifdef _DEBUG
#pragma comment(lib,"ServerCore\\Debug\\ServerCore.lib")
#else
#pragma comment(lib,"ServerCore\\Release\\ServerCore.lib")
#endif

#include "../ServerCore/pch.h"

// Non Blocking => 무한대기
// 커널 recvBuffer, sendBuffer가 비어있는데도 불구하고 무한대기
// 
// Event 기반 Select
// => Event Select
// 운영체제한테, Event를 받아서 처리하고싶다.

struct Session_
{
	Session_(SOCKET s) : socket(s) {}

	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[1000] = {};
	char sendBuffer[1000] = "Hello Im Sever";
	int32 recvBytes = 0;
	int32 sendBytes = 0;
};

enum IO_TYPE
{
	READ,
	WRITE,
	ACCEPT,
	CONNECT
};

struct OverlappedEx
{
	WSAOVERLAPPED overlapped = {};
	int32 type = 0;
};

// 쓰레드가 CP 감지
void WorkThreadMain(HANDLE iocpHandle)
{
	while (true)
	{
		// 초기화
		DWORD bytesTransferred = 0; // 전송된 크기
		Session_* session = nullptr;
		OverlappedEx* overlappedEx = nullptr;

		BOOL ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTransferred, /*Key*/(ULONG_PTR*)(&session),
		(LPOVERLAPPED*)&overlappedEx, INFINITE);

		if (ret == FALSE || bytesTransferred == 0)
		{
			// 연결 끊어줘야함.

			continue;
		}

		// session, overlapped가 세팅완료

		switch (overlappedEx->type)
		{
		case IO_TYPE::READ:
		{
			cout << session->recvBuffer << endl;

			WSABUF wsaBuf;
			wsaBuf.buf = session->recvBuffer;
			wsaBuf.len = 1000;

			DWORD recvLen = 0;
			DWORD flags = 0;

			// CP에 Recv를 재등록
			::WSARecv(session->socket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, nullptr);
		}

		default:
			break;
		}
	}
}

int main()
{
	TM->Create();

	SocketUtils::Init();

	// Non Blocking
	SOCKET listener = SocketUtils::CreateSocket();

	SocketUtils::BindAnyAddress(listener, 7777);
	SocketUtils::Listen(listener);

	vector<Session_*> sessionManager;
	HANDLE iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// CP에서 완료된 정보를 감지하는 5개의 쓰레드 준비
	for (int32 i = 0; i < 5; i++)
	{
		TM->Instance()->Launch([=]() { WorkThreadMain(iocpHandle); });
	}

	while (true)
	{
		SOCKADDR_IN clientAddr;
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket;

		// accept 시도
		while (true)
		{
			// listener가 넌블로킹 소켓
			// ::accept => 넌블로킹 동작
			clientSocket = ::accept(listener, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket == INVALID_SOCKET)
				continue;

			Session_* session = xnew<Session_>(clientSocket);
			sessionManager.push_back(session);

			cout << "Client Accept!!" << endl;

			// CP에 현재 연결된 소켓을 등록 => 신호감지 해달라고 등록
			// Key를 session의 주소로 연동
			::CreateIoCompletionPort((HANDLE)clientSocket, iocpHandle, (ULONG_PTR)session, 0); // Completion Queue

			// Recv 예약
			WSABUF wsabuf;
			wsabuf.buf = session->recvBuffer;
			wsabuf.len = 1000;

			OverlappedEx* overlappedEx = xnew<OverlappedEx>();
			overlappedEx->type = IO_TYPE::READ;

			DWORD recvLen = 0;
			DWORD flags = 0;
			::WSARecv(clientSocket, &wsabuf, 1, &recvLen, &flags, &overlappedEx->overlapped, nullptr);
		}
	}

	for (auto session : sessionManager)
	{
		xdelete(session);
	}

	TM->Join();

	SocketUtils::Close(listener);
	SocketUtils::Clear();

	TM->Delete();

	return 0;

	return 0;
}