
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

struct Session
{
	Session(SOCKET s) : socket(s) {}

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
		Session* session = nullptr;
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


	cout << "Hello Server!" << endl;

	SocketUtils::Init();

	// Non Blocking
	SOCKET listener = SocketUtils::CreateSocket();
	ASSERT_CRASH(listener != INVALID_SOCKET);

	SocketUtils::BindAnyAddress(listener, 7777);
	SocketUtils::Listen(listener);

	SOCKET clientSocket = ::accept(listener, nullptr , nullptr); // 블록킹함수

	cout << "Client Accept " << endl;

	while (true)
	{

	}

	TM->Join();

	SocketUtils::Clear();

	TM->Delete();

	return 0;
}