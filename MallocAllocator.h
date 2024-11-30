#pragma once

#include "Memory.h"

namespace kw
{

// TODO: Description.
template <class T>
class MallocAllocator
{
public:
    T* Allocate(size_t count)
    {
        return static_cast<T*>(Memory::Malloc(sizeof(T) * count, alignof(T)));
    }

    void Deallocate(T* address)
    {
        Memory::Free(address);
    }
};

} // namespace kw
