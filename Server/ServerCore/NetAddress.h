#pragma once
class NetAddress
{
public:
	NetAddress() = default;
	NetAddress(SOCKADDR_IN sockAddr);
	NetAddress(wstring ip, uint16 port);

	SOCKADDR_IN& GetSockAddr() { return _sockAddr; }
	wstring GetIPAddress();
	uint16 GetPortNum() { return ::ntohs(_sockAddr.sin_port); }

	static IN_ADDR IP2Address(const WCHAR* ip);
	
private:
	SOCKADDR_IN	_sockAddr = {};
};

