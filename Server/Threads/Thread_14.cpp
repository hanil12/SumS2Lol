#include "framework.h"

void Hello()
{
	cout << "Hello World!" << endl;
}

int main()
{
	ThreadManager::Create();

	TM->Launch(&Hello);
	TM->Launch(&Hello);
	TM->Launch(&Hello);

	TM->Join();

	ThreadManager::Delete();

	return 0;	
}