#include "pch.h"
#include "SocketUtils.h"

void SocketUtils::Init()
{
}

void SocketUtils::Clear()
{
}

SOCKET SocketUtils::CreateSocket()
{
	return SOCKET();
}

bool SocketUtils::BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn)
{
	return false;
}

bool SocketUtils::SetLinger(SOCKET socket, uint16 onOff, uint16 linger)
{
	return false;
}

bool SocketUtils::SetReuseAddress(SOCKET socket, bool flag)
{
	return false;
}

bool SocketUtils::SetRecvBufferSize(SOCKET socket, uint32 size)
{
	return false;
}

bool SocketUtils::SetSendBufferSize(SOCKET socket, uint32 size)
{
	return false;
}

bool SocketUtils::SetTCPNoDelay(SOCKET socket, bool flag)
{
	return false;
}

bool SocketUtils::SetUpdateAcceptSocket(SOCKET socket, SOCKET listener)
{
	return false;
}

bool SocketUtils::Bind(SOCKET socket, NetAddress netAddr)
{
	return false;
}

bool SocketUtils::BindAnyAddress(SOCKET socket, uint16 port)
{
	return false;
}

bool SocketUtils::Listen(SOCKET socket, int32 backlog)
{
	return false;
}

void SocketUtils::Close(SOCKET& socket)
{
}
