#pragma once

class AcceptEvent;
// 역할
// Accpet
class Listener : public IocpObject
{
public:
	Listener() = default;
	~Listener();

	bool StartAccept(shared_ptr<class Service> service);
	void CloseSocket();

	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);

	// IocpObject을(를) 통해 상속됨
	HANDLE GetHandle() override;
	void DisPatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

private:
	SOCKET _socket = INVALID_SOCKET; // listener자체 소켓
	vector<AcceptEvent*> _acceptEvents;
};

