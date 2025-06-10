#pragma once

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

	// 일감

	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};

private:
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};


};

