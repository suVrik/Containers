#pragma once

#include "Concepts.h"
#include "Iterators.h"

namespace kw
{

// Points to a character sequence. Not necessarily null-terminated.
template <class T>
class BasicStringView
{
public:
	using ValueType = T;

	using Iterator = RandomAccessIterator<const ValueType>;
	using ReverseIterator = ::kw::ReverseIterator<Iterator>;

	// Construct an empty string view.
	BasicStringView();

	// TODO: Construct StringView from contiguous containers and views such as ArrayView<ValueType>,
	//   BasicStringView<ValueType>, Vector<ValueType>, BasicString<ValueType>, ValueType[N].
	//template <Concept Container>
	//BasicStringView(Container Value);

	// Construct a string view from a null-terminated string.
	BasicStringView(const ValueType* Value);

	// Construct a string view over the range [Begin, Begin + Size).
	template <class InIterator> // TODO: Must be a contiguous iterator.
	BasicStringView(InIterator Begin, size_t Size);

	// Construct a string view over the range [Begin, End).
	template <class InIterator> // TODO: Must be a contiguous iterator.
	BasicStringView(InIterator Begin, InIterator End);

	// Return a string view of the given length that starts at the specified position.
	BasicStringView SubString(size_t Begin, size_t Length) const;

	// Return a character with given index. Index must be less than the view's size.
	const ValueType& operator[](size_t Index) const;

	// Return an iterator to the beginning.
	Iterator GetBegin() const;

	// Return an iterator to the end.
	Iterator GetEnd() const;

	// Return a reverse iterator to the beginning.
	ReverseIterator GetReverseBegin() const;

	// Return a reverse iterator to the end.
	ReverseIterator GetReverseEnd() const;

	// These are for ranged-based for loop support. Please don't use them since they violate the code style.
	Iterator begin() const;
	Iterator end() const;

	// Return whether the view is empty.
	bool IsEmpty() const;

	// Return how many characters are stored in the view.
	size_t GetSize() const;

	// Return the first character. The view must not be empty.
	const ValueType& GetFront() const;

	// Return the last character. The view must not be empty.
	const ValueType& GetBack() const;

	// Return the underlying characters. Not necessarily null-terminated. May be null.
	const ValueType* GetData() const;

	// TODO: <=>

private:
	const ValueType* mBegin;
	size_t mSize;
};

using StringView = BasicStringView<char>;

} // namespace kw
