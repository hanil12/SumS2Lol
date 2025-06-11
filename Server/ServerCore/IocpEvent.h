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

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::ACCEPT) {}

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
