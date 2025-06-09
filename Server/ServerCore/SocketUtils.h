#pragma once
class SocketUtils
{
public:
	static LPFN_CONNECTEX ConnectEx; // 정적멤버변수
	static LPFN_DISCONNECTEX DisConnectEx;
	static LPFN_ACCEPTEX AcceptEx;

public:
	// 정적멤버함수 => 일반 함수랑 똑같다. => 모든 객체에 대하여 동일하게 동작
	static void Init();
	static void Clear();

	static SOCKET CreateSocket();
	static bool BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn);

	// Option
	static bool SetLinger(SOCKET socket, uint16 onOff, uint16 linger);
	static bool SetReuseAddress(SOCKET socket, bool flag);
	static bool SetRecvBufferSize(SOCKET socket, uint32 size);
	static bool SetSendBufferSize(SOCKET socket, uint32 size);
	static bool SetTCPNoDelay(SOCKET socket, bool flag);
	static bool SetUpdateAcceptSocket(SOCKET socket, SOCKET listener);

	template<typename T>
	static bool SetSocketOpt(SOCKET socket, int32 level, int32 optName, T optValue);

	static bool Bind(SOCKET socket, class NetAddress netAddr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);
	static bool Listen(SOCKET socket, int32 backlog = SOMAXCONN);
	static void Close(SOCKET& socket);
};

template<typename T>
inline bool SocketUtils::SetSocketOpt(SOCKET socket, int32 level, int32 optName, T optValue)
{
	return SOCKET_ERROR != ::setsockopt(socket, level, optName, reinterpret_cast<char*>(&optValue), sizeof(T));
}
