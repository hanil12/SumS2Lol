#include "framework.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

// Socket : 네트워크 프로그래밍에서, 서로 연결될 단자
// - ip 주소 : 아파트 주소
// - 포트넘버 : 아파트 동호수
// - 프로토콜(Protocol) : 통신 규약

// IP 주소 : IPV4, IPV6
// UDP , TCP/IP

// 현재 나는 클라이언트.
int main()
{
	this_thread::sleep_for(1000ms);

	// 윈도우 소켓,(윈속) 초기화
	// 관련 정보 wsaData에 채워넣는다.
	WSAData wsaData;
	if(::WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		return 0;

	// 1. Client Socket 만들기
	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int errorCode = ::WSAGetLastError();
		cout << "Socket Error : " << errorCode << endl;

		return 0;
	}

	// 2. Server 정보(IP, 포트번호)
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; // IPv4
	inet_pton(AF_INET,"127.0.0.1", &serverAddr.sin_addr); // 127.0.0.1 : 자기 PC 주소
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

	}

	// 소켓 닫기
	::closesocket(clientSocket);
	::WSACleanup();

	return 0;
}
