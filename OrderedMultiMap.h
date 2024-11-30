#pragma once

#include "MallocAllocator.h"
#include "OrderedBase.h"
#include "Pair.h"
#include "Utility.h"

namespace kw
{

// A sorted associative container that contains key-value pairs that supports equivalent keys. Keys are sorted by using
// the specified comparison function. Search, removal, and insertion operations have logarithmic complexity.
template<class Key, class Value, class KeyLessThan = LessThan<Key>, class Allocator = MallocAllocator<Pair<const Key, Value>>>
class OrderedMultiMap : public OrderedBase<Key, Pair<const Key, Value>, PairKeyLessThan<const Key, Value, KeyLessThan>, Allocator, true>
{
public:
	using ValueType = Value;
	using KeyLessThanType = KeyLessThan;
};

} // namespace kw
