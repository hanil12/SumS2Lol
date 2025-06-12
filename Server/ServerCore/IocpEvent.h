#pragma once

enum class EventType : uint8
{
	CONNECT,
	ACCEPT,
	RECV,
	SEND
};

class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void Init();
	EventType GetType() { return _eventType; }
	void SetOwner(shared_ptr<IocpObject> object) { _owner = object; }
	shared_ptr<IocpObject> GetOwner() { return _owner; }

private:
	EventType _eventType;
	shared_ptr<IocpObject> _owner = nullptr;
};

class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::CONNECT) {}
};

// AcceptEvent Owner : Listener
// AcceptEvent Seesion
class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::ACCEPT) {}

	void SetSession(shared_ptr<Session> session) { _session = session; }
	shared_ptr<Session> GetSession() { return _session; }

	shared_ptr<Session> _session;
};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::RECV) {}
};

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::SEND) {}
};
