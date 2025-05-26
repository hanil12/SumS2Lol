
#ifdef _DEBUG
#pragma comment(lib,"ServerCore\\Debug\\ServerCore.lib")
#else
#pragma comment(lib,"ServerCore\\Release\\ServerCore.lib")
#endif

#include "../ServerCore/pch.h"

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

	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		char recvBuffer[1000];

		memset(recvBuffer, 0, 1000);

		SOCKET clientSocket = ::accept(listener, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			// 넌블로킹 함수의 예외처리
			// WSAEWOULDBLOCK : 아직 준비가 되지 않았다.
			if(::WSAGetLastError() == WSAEWOULDBLOCK)
			{
				// 다른 작업 실행가능
			
				continue;
			}

			break;
		}

		cout << "Client Connected" << endl;

		while (true)
		{
			int recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
			if (recvLen <= 0)
			{
				if (::WSAGetLastError() == WSAEWOULDBLOCK)
				{
					continue;
				}

				cout << "Recv Error" << endl;
				break;
			}

			cout << "Recv Data : " << recvBuffer << endl;
			cout << "Recv Len : " << recvLen << endl;
		}
	}

	::closesocket(listener);
	::WSACleanup();

	return 0;
}