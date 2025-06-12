#pragma once

#include <iostream>

#include <winsock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>

#include "Types.h"

using namespace std;

#pragma comment(lib,"ws2_32.lib")

// Multi Thread CORE
#include "CoreTLS.h"
#include "GMacro.h"
#include "MyContainer.h"
#include "RWLock.h"
#include "Memory.h"
#include "MemoryPool.h"

// Multi Thread Helper
#include "DeadLockProfiler.h"
#include "ThreadManager.h"

// RefCount
#include "RefCountable.h"

// NetWork
#include "NetAddress.h"
#include "IocpCore.h"
#include "Session.h"
#include "IocpEvent.h"
#include "Listener.h"

// Utils
#include "SocketUtils.h"