#ifdef _DEBUG
#pragma comment(lib,"ServerCore\\Debug\\ServerCore.lib")
#else
#pragma comment(lib,"ServerCore\\Release\\ServerCore.lib")
#endif

#include "../ServerCore/pch.h"

int main()
{
	this_thread::sleep_for(1000ms);

	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 1. Client Socket 만들기
	SOCKET clientSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int errorCode = ::WSAGetLastError();
		cout << "Socket Error : " << errorCode << endl;

		return 0;
	}

	// 2. Server 정보(IP, 포트번호)
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; // IPv4
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // 127.0.0.1 : 자기 PC 주소
	serverAddr.sin_port = ::htons(7777); // 빅엔디언 표기법으로 바꿈

	// 3. 연결
	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int errorCode = ::WSAGetLastError();
		cout << "Socket Error : " << errorCode << endl;

		return 0;
	}

	cout << "Connet To Server!!" << endl;

	while (true)
	{
		char sendBuffer[100] = "Hello World!";

		for (int32 i = 0; i < 10; i++)
		{
			int32 resultCode = ::sendto(clientSocket, sendBuffer, sizeof(sendBuffer), 0,
			(SOCKADDR*)&serverAddr, sizeof(serverAddr));

			if (resultCode == SOCKET_ERROR)
			{
				int32 error = ::WSAGetLastError();
				cout << "Send Error" << endl;
				return 0;
			}
			cout << "Send Data Len : " << sizeof(sendBuffer) << endl;
		}

		this_thread::sleep_for(5000ms);
	}

	// 소켓 닫기
	::closesocket(clientSocket);
	::WSACleanup();

	return 0;
}
