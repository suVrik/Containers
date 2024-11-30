#pragma once

#include "HashBase.h"
#include "MallocAllocator.h"
#include "Pair.h"
#include "Utility.h"

namespace kw
{

// An associative container that contains key-value pairs with unique keys.
// Search, insertion, and removal of elements have average constant-time complexity.
template<class Key, class Value, class KeyHash = Hash<Key>, class KeyEqual = EqualTo<Key>, class Allocator = MallocAllocator<Pair<const Key, Value>>>
class HashMap : public HashBase<Key, Pair<const Key, Value>, PairKeyHash<const Key, Value, KeyHash>, PairKeyEqualTo<const Key, Value, KeyEqual>, Allocator, false>
{
public:
	using ValueType = Value;
	using KeyHashType = KeyHash;
	using KeyEqualType = KeyEqual;

	// Return an element with given key. If there's no element with the given key, create and return this element.
	ValueType& operator[](const KeyType& Key);
};

} // namespace kw
