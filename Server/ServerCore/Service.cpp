#include "pch.h"
#include "Service.h"

Service::Service(ServiceType type, NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount)
: _type(type)
, _netAddress(address)
, _iocpCore(core)
, _sessionFactory(factory)
, _maxSessionCount(maxSessionCount)
{
}

Service::~Service()
{
}

bool Service::Start()
{
	return false;
}

void Service::CloseService()
{
}

shared_ptr<Session> Service::CreateSession()
{
	shared_ptr<Session> session = _sessionFactory();
	session->SetService(shared_from_this());

	if(_iocpCore->Register(session) == false)
		return nullptr;

	return session;
}

void Service::AddSession(shared_ptr<Session> session)
{
	WRITE_LOCK;
	_sessionCount++;
	_sessions.insert(session);
}

void Service::ReleaseSession(shared_ptr<Session> session)
{
	WRITE_LOCK;
	_sessions.erase(session);
	_sessionCount--;
}

ClientService::ClientService(NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount)
: Service(ServiceType::CLIENT,address,core,factory,maxSessionCount)
{
}

ClientService::~ClientService()
{
}

bool ClientService::Start()
{
	if(CanStart() == false)
		return false;

	// TODO : 서버가 연결을 거부했다던지... 등등

	return true;
}

ServerService::ServerService( NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount)
: Service(ServiceType::SERVER, address, core, factory, maxSessionCount)
{
}

ServerService::~ServerService()
{
}

bool ServerService::Start()
{
	if(CanStart() == false)
		return false;

	_listener = make_shared<Listener>();
	if(_listener == nullptr)
		return false;

	shared_ptr<ServerService> service = static_pointer_cast<ServerService>(shared_from_this());
	if(_listener->StartAccept(service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{
	// TODO
	Service::CloseService();
}
