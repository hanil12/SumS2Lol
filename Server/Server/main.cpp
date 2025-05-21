
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
	SOCKET listener = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listener == INVALID_SOCKET)
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

	// 3. Listener 세팅
	if (::bind(listener, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		// Error
		return 0;
	}

	// 4. 연결(listener) 준비
	if (::listen(listener, 10) == SOCKET_ERROR)
	{
		// Error
		return 0;
	}

	// 5. Accept
	while (true)
	{
		SOCKADDR_IN clientAddr; // IPv4
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int addrLen = sizeof(clientAddr);

		// listener한테 현재 대기 중인 클라이언트를 받아서 정보 추출
		SOCKET clientSocket = ::accept(listener, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			// Error
			return 0;
		}

		// 클라이언트 입장
		char ipAddress[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
		cout << "Client Conneted!!! Client IP : " << ipAddress << endl;
	}

	::closesocket(listener);
	::WSACleanup();

	return 0;
}