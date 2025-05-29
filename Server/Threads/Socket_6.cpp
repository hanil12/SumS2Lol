
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
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[1000] = {};
	char sendBuffer[1000] = "Hello Im Sever";
	int32 recvBytes = 0;
	int32 sendBytes = 0;

	WSAOVERLAPPED overlapped = {}; // WSASEND, WSARECV 했을 때 이벤트 감지
};

int main()
{
	HelloLib();

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

	// Overlapped IO Event기반 소켓 프로그래밍
	// 하나의 쓰레드가 여러 (네트워크)입출력을 동시에 겹쳐서 처리할 수 있게 해준다.
	// => 멀티쓰레드, 비동기, 논블로킹 소켓프로그래밍
	// WSASend, WSARecv => 입출력함수

	// Overlapped Event 동작방식
	// 입출력함수를 호출 => 준비가 되어있으면 실행
	// 준비가 안되어있으면 => WSA_IO_PENDING

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
			if (clientSocket != INVALID_SOCKET)
				break;

			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
		}

		// 연결되어있는 상황
		Session session = Session{ clientSocket };
		WSAEVENT wsaEvent = ::WSACreateEvent();
		session.overlapped.hEvent = wsaEvent;

		cout << "Client Connected!!! " << endl;

		while (true)
		{
			WSABUF wsaBuf;
			wsaBuf.buf = session.recvBuffer;
			wsaBuf.len = 1000;

			DWORD recvLen = 0;
			DWORD flags = 0;

			// 비동기 함수 WSARecv
			// Overlapped 기반 출력함수
			// 이 함수가 호출되면 Event를 확인

			if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &session.overlapped, nullptr) == SOCKET_ERROR)
			{
				// SOCKET_ERROR
				// 1. 아직 Recv버퍼에 다 복사해오지 않았거나, 대기 상태
				if (::WSAGetLastError() == WSA_IO_PENDING)
				{
					// 백그라운드로 입출력 실행
					// Pending : 보류하고 나중에 확인
					::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
					::WSAGetOverlappedResult(session.socket, &session.overlapped, &recvLen, FALSE, &flags);
				}
				// 2. 진짜 실패하거나 이상함
				else
				{
					// 문제가 있는 상황 : Session가서 다 때려부셔야함
					break;
				}
			}

			if (recvLen != 0)
			{
				cout << session.recvBuffer << endl;
			}

			WSABUF wsaBuf2;
			wsaBuf2.buf = session.sendBuffer;
			wsaBuf2.len = 1000;

			DWORD sendLen = 0;

			if (::WSASend(session.socket, &wsaBuf2, 1, &sendLen, flags, &session.overlapped, nullptr) == SOCKET_ERROR)
			{
				if (WSA_IO_PENDING)
				{
					::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
					::WSAGetOverlappedResult(session.socket, &session.overlapped, &sendLen, FALSE, &flags);
				}
				else
				{
					break;
				}
			}

			if (sendLen != 0)
				cout << "Send Succeed" << endl;
		}

		::closesocket(session.socket);
		::WSACloseEvent(wsaEvent);
	}

	::closesocket(listener);
	::WSACleanup();

	return 0;
}