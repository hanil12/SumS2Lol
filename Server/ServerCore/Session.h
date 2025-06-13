#pragma once

class Service;

#include "IocpEvent.h"

// 식탁
class Session : public IocpObject
{
public:
	Session();
	~Session();

	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	void SetSocket(SOCKET socket) { _socket = socket; }
	SOCKET GetSocket() { return _socket; }

	// IocpObject을(를) 통해 상속됨
	virtual HANDLE GetHandle() override;
	virtual void DisPatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

	shared_ptr<Service> GetService() { return _service.lock(); }
	void SetService(shared_ptr<Service> service) { _service = service; }
	// 일감
	bool IsConnected() { return _connected.load(); }
	shared_ptr<Session> GetSession() { return static_pointer_cast<Session>(shared_from_this()); }

	bool RegisterConnect(); // 연결 예약
	bool RegisterDisConnect(); // 끊어내기 예약
	void RegisterRecv();
	void RegisterSend();

	void ProcessConnect(); // 연결 완료, RegisterRecv 예약
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(int32 numOfBytes);

	void HandleError(int32 errorCode);
	void DisConnect(const WCHAR* cause);

	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};

protected:
	virtual void OnConnect() { cout << "test" << endl; }
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len) {}
	virtual void OnDisConnect() {}

private:
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};

	weak_ptr<Service> _service;
	Atomic<bool> _connected = false;

	RecvEvent _recvEvent;
	ConnectEvent _connectEvent;
};

