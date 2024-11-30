#pragma once

#include "Concepts.h"
#include "Iterators.h"
#include "Pair.h"

#include <initializer_list>

namespace kw
{

// TODO: Description
template<class Key, class ElementType, class ElementHash, class ElementEqual, class Allocator, bool IsUniqueKeys>
class HashBase
{
public:
	using KeyType = Key;
	using ElementType = ElementType;
	using ElementHashType = ElementHash;
	using ElementEqualType = ElementEqual;
	using AllocatorType = Allocator;

	using Iterator = RandomAccessIterator<ElementType>;
	using ConstIterator = RandomAccessIterator<const ElementType>;
	using ReverseIterator = ::kw::ReverseIterator<Iterator>;
	using ConstReverseIterator = ::kw::ReverseIterator<ConstIterator>;

	// Constructs an empty container.
	HashBase(const Allocator& InAllocator = Allocator());

	// Constructs a container from the given list.
	HashBase(std::initializer_list<ElementType> List, const Allocator& InAllocator = Allocator());

	// Constructs a container from the given container or view.
	template<ForwardIterable<ElementType> Container>
	HashBase(const Container& InContainer, const Allocator& InAllocator = Allocator());

	// Constructs a container from the given range of elements.
	template<ForwardIterator<ElementType> InIterator>
	HashBase(InIterator Begin, InIterator End, const Allocator& InAllocator = Allocator());

	// Constructs a copy of the given container.
	template<class AnotherAllocator>
	HashBase(const HashBase<KeyType, ElementType, ElementHashType, ElementEqualType, AnotherAllocator, IsUniqueKeys>& Other, const Allocator& InAllocator = Allocator());

	// Constructs a copy of the given container using move semantics.
	HashBase(HashBase&& Other);

	// Destructs the container.
	~HashBase();

	// Replaces the contents of this container with the given list's elements.
	HashBase& operator=(std::initializer_list<ElementType> List);

	// Replaces the contents of this container with the given container's elements.
	HashBase& operator=(const HashBase& Other);

	// Replaces the contents of this container with the given container's elements using move semantics.
	HashBase& operator=(HashBase&& Other);

	// Allocate at least the given number of elements in the container.
	// If the current capacity is already equal or greater, the function does nothing.
	void Reserve(size_t Capacity);

	// Clear the container.
	void Clear();

	// Insert the given element into the container. If an element with the same key already exists,
	// return its iterator and false. Otherwise return an iterator to the inserted element and true.
	Pair<Iterator, bool> Insert(const ElementType& Element);
	Pair<Iterator, bool> Insert(ElementType&& Element);

	// Insert all elements of the given list into the container. If any keys in the given list already
	// exist in this container, they are ignored.
	void Insert(std::initializer_list<ElementType> List);

	// Insert all elements of the given container into this container. If any keys in the given
	// container already exist in this container, they are ignored.
	template<ForwardIterable<ElementType> InContainer>
	void Insert(InContainer&& Container);

	// Insert the given range of elements into the container. The given range must be valid.
	// If any keys in the given range already exist in this container, they are ignored.
	template<ForwardIterator<ElementType> InIterator>
	void Insert(InIterator Begin, InIterator End);

	// Insert an element into the container constructed in-place from the given arguments. If an element
	// with the same key already exists in the container, return its iterator and false. Otherwise return
	// an iterator to the inserted element and true. Useful to avoid unnecessary copy or move operations.
	template<class... InArgs>
	Pair<Iterator, bool> Emplace(InArgs&&... Args);

	// Remove the given element from the container. Iterator must be valid and dereferenceable.
	Iterator Erase(ConstIterator Iterator);

	// Remove an element with the given key from the container. Return how many elements were removed.
	size_t Erase(const KeyType& Key);

	// Return the number of elements with the given key.
	size_t Count(const KeyType& Key) const;

	// Return an element with the given key. If such element doesn't exist, return end iterator.
	Iterator Find(const KeyType& Key);
	ConstIterator Find(const KeyType& Key) const;

	// Return a range of elements with the given key. If no such element exists, return a pair of end iterators.
	Pair<Iterator, Iterator> FindRange(const KeyType& Key);
	Pair<ConstIterator, ConstIterator> FindRange(const KeyType& Key) const;

	// Return whether an element with the given key exists in the container.
	bool Contains(const KeyType& Key) const;

	// Return an iterator to the beginning.
	Iterator GetBegin();
	ConstIterator GetBegin() const;
	ConstIterator GetConstBegin() const;

	// Return an iterator to the end.
	Iterator GetEnd();
	ConstIterator GetEnd() const;
	ConstIterator GetConstEnd() const;

	// Return a reverse iterator to the beginning.
	ReverseIterator GetReverseBegin();
	ConstReverseIterator GetReverseBegin() const;
	ConstReverseIterator GetConstReverseBegin() const;

	// Return a reverse iterator to the end.
	ReverseIterator GetReverseEnd();
	ConstReverseIterator GetReverseEnd() const;
	ConstReverseIterator GetConstReverseEnd() const;

	// These are for ranged-based for loop support. Please don't use them since they violate the code style.
	Iterator begin();
	ConstIterator begin() const;
	Iterator end();
	ConstIterator end() const;

	// Return whether the container is empty.
	bool IsEmpty() const;

	// Return how many elements are stored in the container.
	size_t GetSize() const;

	// Return how many elements are allocated in the container.
	size_t GetCapacity() const;

	// Return the associated allocator.
	const Allocator& GetAllocator() const;

protected:
	static constexpr uint32_t Empty = 0xFFFFFFFFU;
	static constexpr uint32_t Erased = 0xFFFFFFFEU;

	struct Node
	{
		ElementType Element;
		uint32_t Distance;
	};

	Node* mNodes;
	size_t mSize;
	size_t mCapacity;
};

} // namespace kw
