#pragma once

// 일감
class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	IocpObject() = default;
	virtual ~IocpObject() {}

	virtual HANDLE GetHandle() abstract;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

// Completion Port에 이벤트 등록, 감지하는 일을 한다.
class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE GetHandle() { return _iocpHandle; }

	bool Register(shared_ptr<class IocpObject> iocpObj);

	bool DisPatch(uint32 timeOutMs = INFINITE);

private:
	HANDLE _iocpHandle;
};

