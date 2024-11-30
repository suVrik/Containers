#pragma once

#include "MallocAllocator.h"
#include "OrderedBase.h"
#include "Utility.h"

namespace kw
{

// A sorted associative container that contains set of possibly non-unique objects of the given type. Keys are sorted
// by using the specified comparison function. Search, removal, and insertion operations have logarithmic complexity.
template<class Key, class KeyLessThan = LessThan<Key>, class Allocator = MallocAllocator<Key>>
class OrderedMultiSet : public OrderedBase<Key, Key, KeyLessThan, Allocator, true>
{
public:
	using KeyLessThanType = KeyLessThan;
};

} // namespace kw
