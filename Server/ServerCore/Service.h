#pragma once

// Service
// - Session 관리
// - IOCP 관리
// - Lister 관리

// Client Service
// - Session 단하나

// Server Service
// - Session 여러개

enum class ServiceType : uint8
{
	SERVER,
	CLIENT
};

// 디자인 패턴 : Factory 패턴
using SessionFactory = function<shared_ptr<Session>(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool Start() abstract;
	bool CanStart() { return _sessionFactory != nullptr; }
	virtual void CloseService();
	void SetSessionFactory(SessionFactory func) { _sessionFactory = func;}

	// Session 관리
	shared_ptr<Session>	CreateSession();
	void AddSession(shared_ptr<Session> session);
	void ReleaseSession(shared_ptr<Session> session);

	int32 GetCurSessionCount() { return _sessionCount; }
	int32 GetMaxSessionCount() { return _maxSessionCount; }

	ServiceType GetServiceType() { return _type; }
	NetAddress GetNetAddress() { return _netAddress; }
	shared_ptr<IocpCore>& GetIocp() { return _iocpCore; }

protected:
	USE_LOCK;

	ServiceType _type;
	NetAddress _netAddress = {};
	shared_ptr<IocpCore> _iocpCore;

	Set<shared_ptr<Session>> _sessions;
	int32 _sessionCount = 0;
	int32 _maxSessionCount = 0;

	SessionFactory _sessionFactory;
};

class ClientService : public Service
{
public:
	ClientService(NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount = 1);
	~ClientService();

	virtual bool Start() override;
};

class ServerService : public Service
{
public:
	ServerService(NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount = 1);
	~ServerService();

	virtual bool Start() override;
	virtual void CloseService() override;

private:
	shared_ptr<Listener> _listener;
};
