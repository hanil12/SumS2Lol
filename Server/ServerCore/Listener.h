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

	void RegisterAccept(AcceptEvent* acceptEvent); // 입장 받을 준비
	void ProcessAccept(AcceptEvent* acceptEvent); // 입장 처리 , OnAccept함수 호출
	void OnAccept(shared_ptr<Session> session, IocpEvent* iocpEvent); // session의 ProcessConnect호출

	// IocpObject을(를) 통해 상속됨
	HANDLE GetHandle() override;
	void DisPatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

private:
	weak_ptr<Service> _service;

	SOCKET _socket = INVALID_SOCKET; // listener자체 소켓
	vector<AcceptEvent*> _acceptEvents;
};

