#pragma once

#include <cstddef>

namespace kw::MemoryUtils
{

// TODO: Description.
void* Malloc(size_t Size, size_t Alignment = 1);

// TODO: Description.
void Free(void* Address);

// TODO: Description.
void Memcpy(void* Dst, const void* Src, size_t Size);

// TODO: Description.
void Memmove(void* Dst, const void* Src, size_t Size);

// TODO: Description.
int Memcmp(const void* Lhs, const void* Rhs, size_t Size);

// TODO: Description.
void Memset(void* Dst, int Value, size_t Size);

} // namespace kw::MemoryUtils
