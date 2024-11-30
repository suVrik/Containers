#include "Memory.h"

#include <malloc.h>
#include <string.h>

namespace kw
{

void* Memory::Malloc(size_t size, size_t alignment)
{
    return _aligned_malloc(size, alignment);
}

void Memory::Free(void* address)
{
    return _aligned_free(address);
}

void Memory::Memcpy(void* dst, const void* src, size_t size)
{
    memcpy(dst, src, size);
}

void Memory::Memmove(void* dst, const void* src, size_t size)
{
    memmove(dst, src, size);
}

int Memory::Memcmp(const void* lhs, const void* rhs, size_t size)
{
    return memcmp(lhs, rhs, size);
}

void Memory::Memset(void* dst, int value, size_t size)
{
    memset(dst, value, size);
}

} // namespace kw
