#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>

#include "Types.h"

using namespace std;

// Multi Thread CORE
#include "CoreTLS.h"
#include "GMacro.h"
#include "MyContainer.h"
#include "RWLock.h"
#include "Memory.h"

// Multi Thread Helper
#include "DeadLockProfiler.h"
#include "ThreadManager.h"

// RefCount
#include "RefCountable.h"


