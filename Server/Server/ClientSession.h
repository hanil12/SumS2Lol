#pragma once
class ClientSession : public Session
{
public:

private:
	virtual void OnConnect() override;
	virtual int32 OnRecv(BYTE* buffer, int32 len) override;
};

