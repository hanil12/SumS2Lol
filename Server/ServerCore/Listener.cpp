#include "pch.h"
#include "Listener.h"

Listener::~Listener()
{
	SocketUtils::Close(_socket);

	for (auto event : _acceptEvents)
	{
		xdelete(event);
	}
}

bool Listener::StartAccept(shared_ptr<Service> service)
{
	_socket = SocketUtils::CreateSocket();
	if(_socket == INVALID_SOCKET) return false;

	if (service->GetIocp()->Register(shared_from_this()) == false) // => IOCP에게 Lister의 이벤트를을 감지하게끔 등록
		return false;

	if (SocketUtils::SetReuseAddress(_socket, true) == false)
		return false;

	if (SocketUtils::SetLinger(_socket, 0, 0) == false)
		return false;

	if(SocketUtils::Bind(_socket, service->GetNetAddress()) == false)
		return false;

	if(SocketUtils::Listen(_socket) == false)
		return false;

	const int32 acceptCount = 1;

	for (int32 i = 0; i < acceptCount; i++)
	{
		AcceptEvent* accpetEvent = xnew<AcceptEvent>(); // 
		accpetEvent->SetOwner(shared_from_this());
		_acceptEvents.push_back(accpetEvent);
		RegisterAccept(accpetEvent); 
	}

	return true;
}

void Listener::CloseSocket()
{
	SocketUtils::Close(_socket);
}

void Listener::RegisterAccept(AcceptEvent* acceptEvent)
{
	shared_ptr<Session> session = make_shared<Session>();

	acceptEvent->Init();
	acceptEvent->SetSession(session);

	DWORD bytesRecived = 0;

	if (false == SocketUtils::AcceptEx(_socket, session->GetSocket(), session->_recvBuffer, 0,
		sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytesRecived, static_cast<LPOVERLAPPED>(acceptEvent)))
	{
		int32 errorCode = ::WSAGetLastError();

		if (errorCode != WSA_IO_PENDING)
		{
			// 뭔가 이상이 있음.

			RegisterAccept(acceptEvent);
		}
	}
}

void Listener::ProcessAccept(AcceptEvent* acceptEvent)
{
	shared_ptr<Session> session = static_pointer_cast<Session>(acceptEvent->GetSession());

	if (false == SocketUtils::SetUpdateAcceptSocket(session->GetSocket(), _socket))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	SOCKADDR_IN socketAddress;
	int32 sizeofSockAddr = sizeof(socketAddress);

	if (SOCKET_ERROR == ::getpeername(session->GetSocket(), reinterpret_cast<SOCKADDR*>(&socketAddress), &sizeofSockAddr))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	session->SetNetAddress(socketAddress);

	cout << "Client Connect!!!" << endl;

	RegisterAccept(acceptEvent);
}

HANDLE Listener::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Listener::DisPatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	ASSERT_CRASH(iocpEvent->GetType() == EventType::ACCEPT);
	AcceptEvent* acceptEvent = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(acceptEvent);
}
