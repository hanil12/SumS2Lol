#include "framework.h"

#include "ClientSession.h"

void ClientSession::OnConnect()
{
	cout << "Hello Client!!!" << endl;
}

int32 ClientSession::OnRecv(BYTE* buffer, int32 len)
{
	cout << "Recv Len : " << len << endl;
	cout << buffer << endl;

	return len;
}
