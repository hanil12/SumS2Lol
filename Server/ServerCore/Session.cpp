#include "pch.h"
#include "Session.h"

Session::Session()
{
    _socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
    SocketUtils::Close(_socket);
}

HANDLE Session::GetHandle()
{
    return reinterpret_cast<HANDLE>(_socket);
}

void Session::DisPatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
    EventType type = iocpEvent->GetType();

    // TODO
    switch (type)
    {
    case EventType::CONNECT:
        break;
    case EventType::ACCEPT:
        break;
    case EventType::RECV:
    {
        cout << "Recv!!!" << endl;

    }
        break;
    case EventType::SEND:
        break;
    default:
        break;
    }
}
