#pragma once

#include "Concepts.h"
#include "MallocAllocator.h"

namespace kw
{

// TODO: Description.
template <class T, class Allocator = MallocAllocator<T>>
class BasicString : protected Allocator
{
public:
	using ValueType = T;
	using AllocatorType = Allocator;

	using Iterator = RandomAccessIterator<ValueType>;
	using ConstIterator = RandomAccessIterator<const ValueType>;
	using ReverseIterator = ::kw::ReverseIterator<Iterator>;
	using ConstReverseIterator = ::kw::ReverseIterator<ConstIterator>;

	// TODO
	static constexpr size_t None = SIZE_MAX;

	// Construct the empty string.
	BasicString();
	explicit BasicString(const Allocator& Allocator);

	// TODO: Construct String from contiguous containers and views such as ArrayView<ValueType>,
	//   BasicStringView<ValueType>, Vector<ValueType>, BasicString<ValueType>, ValueType[N].

	// Construct the string from the given null-terminated character string.
	BasicString(const ValueType* Value);
	BasicString(const ValueType* Value, const Allocator& Allocator);

	// Construct the string with the given number of the specified character.
	BasicString(size_t Count, ValueType Value);
	BasicString(size_t Count, ValueType Value, const Allocator& Allocator);

	// Construct the string from the given character string of the specified length.
	BasicString(const ValueType* Value, size_t Count);
	BasicString(const ValueType* Value, size_t Count, const Allocator& Allocator);

	// Construct the string from the given range of characters.
	template <class InIterator>
	BasicString(InIterator First, InIterator Last);
	template <class InIterator>
	BasicString(InIterator First, InIterator Last, const Allocator& Allocator);

	// TODO: Description.
	template <class OtherAllocator>
	BasicString(const BasicString<ValueType, OtherAllocator>& Other);
	template <class OtherAllocator>
	BasicString(const BasicString<ValueType, OtherAllocator>& Other, const Allocator& Allocator);

	// TODO: Description.
	BasicString(BasicString&& Other);

	// TODO: Description.
	~BasicString();

	// TODO: Description.
	template <class OtherAllocator>
	BasicString& operator=(const BasicString<ValueType, OtherAllocator>& Other);

	// TODO: Description.
	BasicString& operator=(BasicString&& Other);

	// Assign a new value to the string from the given null-terminated character string.
	BasicString& operator=(const ValueType* Value);

	// TODO: Description.
	template <class OtherAllocator>
	BasicString& operator+=(const BasicString<ValueType, OtherAllocator>& Value);

	// TODO: Description.
	BasicString& operator+=(const ValueType* Value);

	// TODO: Description.
	BasicString& operator+=(char Value);

	// TODO: Operator+ and more...

	// Replace the contents of the string with the given number of the specified character.
	void Assign(size_t Count, ValueType Value);

	// Replace the contents of the string with the given character string of the specified length.
	void Assign(const ValueType* Value, size_t Count);

	// Replace the contents of the string with the given range of characters.
	template <class InIterator>
	void Assign(InIterator First, InIterator Last);

	// Resize the string to the given size. New characters are set to the specified character.
	void Resize(size_t Size, ValueType Value);

	// Allocate at least the given number of characters in the string.
	// If the current capacity is already equal or greater, the function does nothing.
	void Reserve(size_t Capacity);

	// Clear the string.
	void Clear();

	// TODO
	template <class OtherAllocator>
	BasicString& Insert(size_t Position, const BasicString<ValueType, OtherAllocator>& Value);

	// TODO
	template <class OtherAllocator>
	BasicString& Insert(size_t Position, const ValueType* Value);

	// TODO
	template <class OtherAllocator>
	BasicString& Insert(size_t Position, const ValueType* Value, size_t Count);

	// Insert the given object before the specified character. `iterator` must be valid.
	Iterator Insert(ConstIterator Iterator, ValueType Value);

	// Insert the given range of objects before the specified character. `iterator` must be valid.
	// `first` and `last` must be valid. `first` must be dereferenceable. Both must not reference this string.
	template <class InIterator>
	Iterator Insert(ConstIterator Iterator, InIterator First, InIterator Last);

	// Remove the specified portion of the string. Position and length must be a valid combination.
	Iterator Erase(size_t Position = 0, size_t Length = None);

	// Remove the specified character from the string. `iterator` must be valid and dereferenceable.
	Iterator Erase(ConstIterator Iterator);

	// Remove the specified range [First, Last) of characters from the string.
	// `first` must be valid and dereferenceable. `last` must be valid.
	Iterator Erase(ConstIterator First, ConstIterator Last);

	// TODO
	template <class OtherAllocator>
	BasicString& Append(const BasicString<ValueType, OtherAllocator>& Value);

	// TODO
	BasicString& Append(const ValueType* Value);

	// TODO
	BasicString& Append(const ValueType* Value, size_t Count);

	// TODO
	BasicString& Append(size_t Count, ValueType Value);

	// TODO
	template <class InIterator>
	BasicString& Append(InIterator First, InIterator Last);

	// Add an character to the end.
	void PushBack(ValueType Value);

	// Remove the last character. The string must not be empty.
	void PopBack();

	// Return a character with given index. `index` must be less than the string's length.
	ValueType& operator[](size_t Index);
	const ValueType& operator[](size_t Index) const;

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

	// Return whether the string is empty.
	bool IsEmpty() const;

	// Return how many characters are stored in the string.
	size_t GetSize() const;

	// Return how many characters are allocated in the string.
	size_t GetCapacity() const;

	// Return the first character. The string must not be empty.
	ValueType& GetFront();
	const ValueType& GetFront() const;

	// Return the last character. The string must not be empty.
	ValueType& GetBack();
	const ValueType& GetBack() const;

	// Return the underlying array. May be null.
	ValueType* GetData();
	const ValueType* GetData() const;

	// Return the associated allocator.
	const Allocator& GetAllocator() const;

	// TODO: <=>
};

using String = BasicString<char>;

} // namespace kw
