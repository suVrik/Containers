#pragma once

#include "Concepts.h"
#include "MallocAllocator.h"

namespace kw
{

// TODO: Description.
template <class T, class Allocator = MallocAllocator<T>>
class List : protected Allocator
{
public:
	using ValueType = T;
	using AllocatorType = Allocator;

	using Iterator = BidirectionalIterator<T>;
	using ConstIterator = BidirectionalIterator<const T>;
	using ReverseIterator = ::kw::ReverseIterator<Iterator>;
	using ConstReverseIterator = ::kw::ReverseIterator<ConstIterator>;

	// Construct an empty container.
	List();
	explicit List(const Allocator& allocator);

	// Construct a container with the given number of default-constructed elements.
	explicit List(size_t count);
	List(size_t count, const Allocator& allocator);

	// Construct a container with the given number of copies of the specified object.
	List(size_t count, const ValueType& value);
	List(size_t count, const ValueType& value, const Allocator& allocator);

	// Construct a container from the given list of objects.
	List(std::initializer_list<ValueType> list);
	List(std::initializer_list<ValueType> list, const Allocator& allocator);

	// Construct a container from the given range of objects.
	template <class InIterator>
	List(InIterator first, InIterator last);
	template <class InIterator>
	List(InIterator first, InIterator last, const Allocator& allocator);

	List(const List& other) requires Concepts::CopyConstructible<ValueType>;
	List(List&& other);
	~List();
	List& operator=(const List& other) requires Concepts::CopyConstructible<ValueType>;
	List& operator=(List&& other);

	// Replace all elements of the container with the given list of objects.
	List& operator=(std::initializer_list<ValueType> list);

	// Replace all elements of the container with the given number of default-constructed elements.
	void Assign(size_t count);

	// Replace all elements of the container with the given number of copies of specified object.
	void Assign(size_t count, const ValueType& value);

	// Replace all elements of the container with the given list of objects.
	void Assign(std::initializer_list<ValueType> list);

	// Resize the container to the given size. New elements are default-constructed.
	void Resize(size_t size);

	// Resize the container to the given size. New elements are copied from the specified object.
	void Resize(size_t size, const ValueType& value);

	// Clear the container.
	void Clear();

	// Insert the given object before the specified element. `iterator` must be valid.
	Iterator Insert(ConstIterator iterator, const ValueType& value);
	Iterator Insert(ConstIterator iterator, ValueType&& value);

	// Insert the given range of objects before the specified element. `iterator` must be valid.
	// `first` and `last` must be valid. `first` must be dereferenceable. Both must not reference this container.
	template <class InIterator>
	Iterator Insert(ConstIterator iterator, InIterator first, InIterator last);

	// Remove the specified element from the container. `iterator` must be valid and dereferenceable.
	Iterator Erase(ConstIterator iterator);

	// Remove the specified range [first, last) of elements from the container.
	// `first` must be valid and dereferenceable. `last` must be valid.
	Iterator Erase(ConstIterator first, ConstIterator last);

	// Add an element to the end.
	void PushBack(const ValueType& value);
	void PushBack(ValueType&& value);

	// Construct an element in-place at the end.
	template <class... Args>
	ValueType& EmplaceBack(Args&&... args);

	// Remove the last element. The container must not be empty.
	void PopBack();

	// Add an element to the beginning.
	void PushFront(const ValueType& value);
	void PushFront(ValueType&& value);

	// Construct an element in-place at the beginning.
	template <class... Args>
	ValueType& EmplaceFront(Args&&... args);

	// Remove the first element. The container must not be empty.
	void PopFront();

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

	// Return the first element. The container must not be empty.
	ValueType& GetFront();
	const ValueType& GetFront() const;

	// Return the last element. The container must not be empty.
	ValueType& GetBack();
	const ValueType& GetBack() const;

	// Return the associated allocator.
	const Allocator& GetAllocator() const;

private:
	Iterator mFront;
	Iterator mBack;
	size_t mSize;
};

} // namespace kw
