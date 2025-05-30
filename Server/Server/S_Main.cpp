
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

	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// Error
		return 0;
	}

	// Non Blocking
	SOCKET listener = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listener == INVALID_SOCKET)
	{
		// Error
		return 0;
	}

	u_long on = 1;
	if (::ioctlsocket(listener, FIONBIO, &on) == SOCKET_ERROR) // listener 소켓을 논블로킹 소켓으로 만드는 함수
	{
		return 0;
	}

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(listener, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout << "Binding Error" << endl;
		return 0;
	}

	if (::listen(listener, 10) == SOCKET_ERROR)
	{
		cout << "Listen Error" << endl;
		return 0;
	}

	// Overlapped Callback
	// 1. 논블럭킹 + 비동기
	//
	// 단점
	// 1. APC큐가 쓰레드마다 있다.
	// => 쓰레드를 Alertable Wait 상태로 만들어줘야 APC큐에 있는 함수가 실행
	// ==> 이것마저 부담

	// => IOCP 기반 서버
	// 1. APC => Completion Port (쓰레드 마다 있는게 아니라 중앙관리)
	// 2. 쓰레드를 Alertable Wait 상태로 만들기 => CP 결과 처리를 GetQueuedCompletionStatus
	// => 멀티쓰레드에 최적화 되어있다.

	// CreateIOCompletionPort => CP 생성 / CP에 소켓 연동
	// GetQueuedCompletionStatus => 결과 처리

	vector<Session*> sessionManager;
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
			if(clientSocket == INVALID_SOCKET)
				continue;

			Session* session = xnew<Session>(clientSocket);
			sessionManager.push_back(session);

			cout << "Client Accept!!" <<  endl;

			// CP에 현재 연결된 소켓을 등록 => 신호감지 해달라고 등록
			// Key를 session의 주소로 연동
			::CreateIoCompletionPort((HANDLE)clientSocket, iocpHandle, (ULONG_PTR)session, 0);

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

	::closesocket(listener);
	::WSACleanup();

	TM->Delete();

	return 0;
}