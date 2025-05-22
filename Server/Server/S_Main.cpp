
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

	// 1. ListenSocket 만들기
	// ListenSocket : 클라이언트를 받아주는 문지기 역할
	SOCKET serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		// Error
		return 0;
	}

	// 2. Server(나) 정보 세팅
	SOCKADDR_IN serverAddr; // 현재 나의 세팅
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; // IPv4
	serverAddr.sin_addr.s_addr= ::htonl(INADDR_ANY); // 니가 알아서 IP주소 써줘, 로컬 주소
	serverAddr.sin_port = ::htons(7777); // 빅엔디언 표기법으로 바꿈

	if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout <<"Binding Error" << endl;
		return 0;
	}

	// 5. Accept
	while (true)
	{
		while (true)
		{
			SOCKADDR_IN clientAddr;
			::memset(&clientAddr, 0, sizeof(clientAddr));
			int32 addrLen = sizeof(clientAddr);

			char recvBuffer[1000];

			memset(recvBuffer,0,1000);

			int recvLen = ::recvfrom(serverSocket, recvBuffer, sizeof(recvBuffer), 0, 
			(SOCKADDR*)(&clientAddr), &addrLen);
			if (recvLen <= 0)
			{
				int32 errorCode = ::WSAGetLastError();
				cout << "Recv Error" << endl;

				return 0;
			}

			cout << "Recv Data : " << recvBuffer << endl;
			cout << "Recv Len : " << recvLen << endl;
		}
	}

	::closesocket(serverSocket);
	::WSACleanup();

	return 0;
}