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

private:
	EventType _eventType;
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

	void SetSession(Session* session) { _session = session; }
	Session* GetSession() { return _session; }

private:
	Session* _session = nullptr;
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
