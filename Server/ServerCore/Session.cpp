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
    case EventType::ACCEPT:
    {
        DisConnect(L"Session Cannot Accpet");

        break;
    }
    case EventType::CONNECT:
    {
        ProcessConnect();
    }
        break;
    case EventType::RECV:
    {
        ProcessRecv(numOfBytes);
        break;
    }
        break;
    case EventType::SEND:
        break;
    default:
        break;
    }
}

bool Session::RegisterConnect()
{
    if(IsConnected())
        return false;

    if(GetService()->GetServiceType() != ServiceType::CLIENT)
        return false;

    if(SocketUtils::SetReuseAddress(_socket, true) == false)
        return false;

    if(SocketUtils::BindAnyAddress(_socket,0) == false)
        return false;

   _connectEvent.Init();
   SOCKADDR_IN sockAddr = GetService()->GetNetAddress().GetSockAddr();

   DWORD numOfBytes = 0;

   // connect를 비동기적으로 수행
   if (false == SocketUtils::ConnectEx(_socket, reinterpret_cast<SOCKADDR*>(&sockAddr),
       sizeof(sockAddr), nullptr, 0, &numOfBytes, &_connectEvent))
   {
        int32 errorCode = ::WSAGetLastError();
        if (errorCode != WSA_IO_PENDING)
        {
            HandleError(errorCode);
            _connectEvent.SetOwner(nullptr);
            return false;
        }
   }

   return true;
}

bool Session::RegisterDisConnect()
{
    return false;
}

void Session::RegisterRecv()
{
    // Connect가 성공했을 때
    if(IsConnected() == false)
        return;

    _recvEvent.Init();
    _recvEvent.SetOwner(shared_from_this());

    WSABUF wsaBuf;
    wsaBuf.buf = _recvBuffer;
    wsaBuf.len = sizeof(_recvBuffer);

    DWORD numOfBytes = 0;
    DWORD flags = 0;

    if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, OUT & numOfBytes, &flags, &_recvEvent, nullptr))
    {
        int32 errorCode = ::WSAGetLastError();
        if (errorCode != WSA_IO_PENDING)
        {
            HandleError(errorCode);
            _recvEvent.SetOwner(nullptr);
        }
    }
}

void Session::RegisterSend()
{
    // TODO : Connect가 성공했을 때
}

void Session::ProcessConnect()
{
    _connectEvent.SetOwner(nullptr);
    _connected.store(true);

    GetService()->AddSession(GetSession());

    OnConnect();

    RegisterRecv();
}

void Session::ProcessRecv(int32 numOfBytes)
{
    // 서버는 클라이언트를 절대 신뢰하지않는다.

    // => 패킷 해석할 때도 예외처리

    _recvEvent.SetOwner(nullptr);

    if (numOfBytes == 0)
    {
        DisConnect(L"Recv: 0");
        return;
    }

    OnRecv(reinterpret_cast<BYTE*>(&_recvBuffer), numOfBytes);

    RegisterRecv();
}

void Session::ProcessSend(int32 numOfBytes)
{
    // Send
}

void Session::HandleError(int32 errorCode)
{
    switch (errorCode)
    {
    case WSAECONNRESET:
    case WSAECONNABORTED:
    {
        DisConnect(L"Handle Error");
    }

    default:
        cout << "Handle Error : " << errorCode << endl;
        break;
    }
}

void Session::DisConnect(const WCHAR* cause)
{
    // TODO : Disconnect
    cout << cause << endl;
}
