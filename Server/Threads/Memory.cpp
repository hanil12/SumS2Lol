#include "framework.h"
#include "Memory.h"

Memory::Memory()
{
    int32 size = 0;
    int32 tableIndex = 0;

    // 32개의 Pool... 32바이트짜리 풀
    for (size = 0; size < 1024; size += 32)
    {
        MemoryPool* pool = new MemoryPool(size);
        _pools.push_back(pool);

        while (tableIndex <= size)
        {
            _poolTable[tableIndex] = pool;
            tableIndex++;
        }
    }

    for (size = 1024; size < 2048; size += 128)
    {
        MemoryPool* pool = new MemoryPool(size);
        _pools.push_back(pool);

        while (tableIndex <= size)
        {
            _poolTable[tableIndex] = pool;
            tableIndex++;
        }
    }

    for (size = 2048; size < 4096; size += 256)
    {
        MemoryPool* pool = new MemoryPool(size);
        _pools.push_back(pool);

        while (tableIndex <= size)
        {
            _poolTable[tableIndex] = pool;
            tableIndex++;
        }
    }
}

Memory::~Memory()
{
    for (MemoryPool* pool : _pools)
    {
        delete pool;
    }

    _pools.clear();
}

void* Memory::Allocate(int32 size)
{
    MemoryHeader* head = nullptr;

    const int32 allocSize = size + sizeof(MemoryHeader);

    // MAX_ALLOC_SIZE를 넘어가면 그냥 하던대로 동적할당.
    if (allocSize > MAX_ALLOC_SIZE)
    {
        head = reinterpret_cast<MemoryHeader*>(std::malloc(allocSize));
    }
    else
    {
        head = _poolTable[allocSize]->Pop();
    }

    return MemoryHeader::AttachHeader(head, allocSize);
}

void Memory::Release(void* ptr)
{
    MemoryHeader* head = MemoryHeader::DetachHeader(ptr);

    const int32 allocSize = head->_allocSize;

    if (allocSize > MAX_ALLOC_SIZE)
    {
        std::free(head);
    }
    else
    {
        _poolTable[allocSize]->Push(head);
    }
}
