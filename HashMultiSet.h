#pragma once

#include "HashBase.h"
#include "MallocAllocator.h"
#include "Utility.h"

namespace kw
{

// An associative container that contains set of possibly non-unique objects of the specified type.
// Search, insertion, and removal have average constant-time complexity.
template<class Key, class KeyHash = Hash<Key>, class KeyEqual = EqualTo<Key>, class Allocator = MallocAllocator<Key>>
class HashMultiSet : public HashBase<Key, Key, KeyHash, KeyEqual, Allocator, true>
{
public:
	using KeyHashType = KeyHash;
	using KeyEqualType = KeyEqual;
};

} // namespace kw
