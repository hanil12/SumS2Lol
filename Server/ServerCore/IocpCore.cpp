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
    return ::CreateIoCompletionPort(iocpObj->GetHandle(), _iocpHandle, 0, 0);
}

bool IocpCore::DisPatch(uint32 timeOutMs)
{
    DWORD numOfBytes = 0;
    shared_ptr<IocpObject> iocpObject = nullptr; // Session
    IocpEvent* iocpEvent = nullptr;
    ULONG_PTR key = 0;

    if (::GetQueuedCompletionStatus(
        _iocpHandle
        , &numOfBytes
        , &key // ... 0
        , reinterpret_cast<LPOVERLAPPED*>(&iocpEvent)
        , timeOutMs
    ))
    {
        iocpObject = iocpEvent->GetOwner();
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
