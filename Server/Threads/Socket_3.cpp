#include "framework.h"

using namespace std;

// 블로킹 함수 vs 넌블로킹 함수
// 동기 프로그래밍 vs 비동기 프로그래밍

// TCP UDP
// 비유 :

// TCP : 통화
// 1. 서로 연결이 되어있는지 확인.
// 2. 순서가 보장되어있다. 잘 전달되었는지도 보장
// 3. 경계성 X
// 4. 속도 UDP 비해서 느림
// EX) 게임, 서로 연결되어있는지 신뢰필요한 작업

// UDP : 편지
// 1. 서로 연결여부가 필요가 없음.
// 2. 순서가 보장X  잘 전달되었는지도 보장X
// 3. 경계성 O
// 4. TCP 비해서 빠름
// EX) 스트리밍, 연결, 데이터 누락여부보다 빠른 속도 필요한 작업

int Client_UDP()
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

int SERVER_UDP()
{

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
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // 니가 알아서 IP주소 써줘, 로컬 주소
	serverAddr.sin_port = ::htons(7777); // 빅엔디언 표기법으로 바꿈

	if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout << "Binding Error" << endl;
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

			memset(recvBuffer, 0, 1000);

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