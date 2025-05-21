#include "pch.h"
#include "Allocator.h"

void* BaseAllocator::Alloc(size_t size)
{
    void* ptr = std::malloc(size);

    return ptr;
}

void BaseAllocator::Release(void* ptr)
{
    std::free(ptr);
}

void* StompAllocator::Alloc(size_t size) // 8
{
    const int64 pageCount = (size + PAGE_SIZE - 1) / PAGE_SIZE;
    const int64 dataOffset = pageCount * PAGE_SIZE - size; // 4088
    void* baseAddress = ::VirtualAlloc(NULL, pageCount * PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    // 4096

    return static_cast<void*>(static_cast<int8*>(baseAddress) + dataOffset); // 4096 + 4088
}

void StompAllocator::Release(void* ptr)
{
    const int64 address = reinterpret_cast<int64>(ptr); // 4096 + 4088
    const int64 baseAddress = address - (address % PAGE_SIZE); //  4096 

    ::VirtualFree(reinterpret_cast<void*>(baseAddress), 0, MEM_RELEASE);
}

void* PoolAllocator::Alloc(size_t size)
{
    return ThreadManager::Instance()->PoolMemory()->Allocate(size);
}

void PoolAllocator::Release(void* ptr)
{
    ThreadManager::Instance()->PoolMemory()->Release(ptr);
}
