#include "pch.h"
#include "IocpCore.h"

IocpCore::IocpCore()
{
    // Completion Port
    _iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0,0,0);
    ASSERT_CRASH(_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
    ::CloseHandle(_iocpHandle);
}

bool IocpCore::Register(IocpObject* iocpObj)
{
    return ::CreateIoCompletionPort(iocpObj->GetHandle(), _iocpHandle, reinterpret_cast<ULONG_PTR>(iocpObj), 0);
}

bool IocpCore::DisPatch(uint32 timeOutMs)
{
    DWORD numOfBytes = 0;
    IocpObject* iocpObject = nullptr; // Session
    IocpEvent* iocpEvent = nullptr;

    if (::GetQueuedCompletionStatus(
        _iocpHandle
        , &numOfBytes
        , reinterpret_cast<PULONG_PTR>(&iocpObject)
        , reinterpret_cast<LPOVERLAPPED*>(&iocpEvent)
        , timeOutMs
    ))
    {
        iocpObject->DisPatch(iocpEvent, numOfBytes);
    }
    else
    {
        int32 errorCode = ::WSAGetLastError();
        switch (errorCode)
        {
        case WAIT_TIMEOUT:
            return false;

        default:
            iocpObject->DisPatch(iocpEvent, numOfBytes);
            break;
        }
    }

    return true;
}
