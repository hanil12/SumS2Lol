#include "framework.h"

using namespace std;

// TCP/IP
// 블록킹 함수
// recv
// send
// accept
// connect

// UDP
// 블록킹 함수
// recvfrom
// sendto

// => 유저레벨에서 커널레벨Buffer로 복사 후, send or recv

// send...만약 커널영역 Send buffer가 꽉 찼을 경우... 대기
// 만약 5000명의 플레이어가 send할려는데 꽉찼다면 어떻게 할 것인가...? => 넌블록킹

int SocketOpt()
{
	SOCKET listener = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listener == INVALID_SOCKET)
	{
		// Error
		return 0;
	}

	// 2. Server(나) 정보 세팅(IP 주소, 포트번호)
	SOCKADDR_IN serverAddr; // 현재 나의 세팅
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; // IPv4
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // 니가 알아서 IP주소 써줘, 로컬 주소
	serverAddr.sin_port = ::htons(7777); // 빅엔디언 표기법으로 바꿈(1~1000)

	// 3. Listener Setting
	if (::bind(listener, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cout << "Binding Error" << endl;
		return 0;
	}

	// SO_KEEPALIVE => 주기적으로 연결이 끊겼는지 확인하는 옵션
	bool enable = true;
	::setsockopt(listener, SOL_SOCKET, SO_KEEPALIVE, (char*)&enable, sizeof(enable));

	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 5;
	// 소켓이 하는 일을 마무리 하고 닫히게 만든다...(닫히는 것을 지연시킴)
	::setsockopt(listener, SOL_SOCKET, SO_LINGER, (char*)(&linger), sizeof(linger));

	int32 recvBufferSize = 0;
	int32 optionLen = sizeof(recvBufferSize);
	::getsockopt(listener, SOL_SOCKET, SO_RCVBUF, (char*)(&recvBufferSize), &optionLen);
	cout << "Kenel Recv Buffer Size : " << recvBufferSize << endl;

	int32 sendBufferSize = 0;
	optionLen = sizeof(sendBufferSize);
	::getsockopt(listener, SOL_SOCKET, SO_SNDBUF, (char*)(&sendBufferSize), &optionLen);
	cout << "Kenel Send Buffer Size : " << sendBufferSize << endl;

	// SO_REUSEADDR
	// IP 주소 및 포트번호를 재사용할 것인가?
	::setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)(&enable), sizeof(enable));

	// TCP_NODELAY ... 게임은 true
	// 데이터 모았다가 한번에 전송 : 네이글 알고리즘
	// => 단점: 반응시간 손해
	// => 장점: 작은 패킷들을 여러번 보냈을 때 발생하는 오버헤드 감소

	enable = true;
	::setsockopt(listener, IPPROTO_TCP, TCP_NODELAY, (char*)(&enable), sizeof(enable));

	return 0;
}