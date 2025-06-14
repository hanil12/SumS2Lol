#include "pch.h"
#include "NetAddress.h"

NetAddress::NetAddress(SOCKADDR_IN sockAddr)
{
}

NetAddress::NetAddress(wstring ip, uint16 port)
{
	::memset(&_sockAddr,0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr = NetAddress::IP2Address(ip.c_str());
	_sockAddr.sin_port = ::htons(port);
}

wstring NetAddress::GetIPAddress()
{
	WCHAR buffer[100];
	::InetNtopW(AF_INET,&_sockAddr.sin_addr, buffer, sizeof(buffer));

	return buffer;
}

IN_ADDR NetAddress::IP2Address(const WCHAR* ip) // "127.0.0.1"
{
	IN_ADDR address;
	::InetPtonW(AF_INET,ip, &address);

	return address;
}
