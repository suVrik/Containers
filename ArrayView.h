#pragma once

#include "Assert.h"
#include "Concepts.h"
#include "ContainerUtils.h"
#include "Iterators.h"

namespace kw
{

// Points to a contiguous array of elements of specified type.
template<class T>
class ArrayView
{
public:
	using ValueType = T;

	using Iterator = RandomAccessIterator<const ValueType>;
	using ReverseIterator = ::kw::ReverseIterator<Iterator>;

	// Construct an empty array view.
	ArrayView();

	 // Construct an array view from the given contiguous container or view.
	template<ContiguousIterable<ValueType> Iterable>
	ArrayView(const Iterable& InIterable);

	// Construct an array view over the given contiguous range [Begin, End).
	template<ContiguousIterator<ValueType> InIterator>
	ArrayView(InIterator Begin, InIterator End);

	// Construct a copy of the given array view.
	ArrayView(const ArrayView& Other) = default;

	// Return an array view of the given length that starts at the specified position.
	ArrayView SubArray(size_t Begin, size_t Length) const;

	// Return an element with given index. Index must be less than the view's size.
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

	// Return how many elements are stored in the view.
	size_t GetSize() const;

	// Return the first element. The view must not be empty.
	const ValueType& GetFront() const;

	// Return the last element. The view must not be empty.
	const ValueType& GetBack() const;

	// Return the underlying array. May be null.
	const ValueType* GetData() const;

	// Return whether two views are equal.
	bool operator==(const ArrayView& Other) const;

	// Return whether two views are not equal.
	bool operator!=(const ArrayView& Other) const;

	// Return whether this view is lexicographically less than the specified view.
	bool operator<(const ArrayView& Other) const;

	// Return whether this view is lexicographically less or equal than the specified view.
	bool operator<=(const ArrayView& Other) const;

	// Return whether this view is lexicographically greater than the specified view.
	bool operator>(const ArrayView& Other) const;

	// Return whether this view is lexicographically greater or equal than the specified view.
	bool operator>=(const ArrayView& Other) const;

private:
	const ValueType* mData;
	size_t mSize;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
ArrayView<T>::ArrayView()
	: mData(nullptr)
	, mSize(0)
{
}

template<class T>
template<ContiguousIterable<T> Iterable>
ArrayView<T>::ArrayView(const Iterable& InIterable)
	: ArrayView(ContainerUtils::GetBegin(InIterable), ContainerUtils::GetEnd(InIterable))
{
}

template<class T>
template<ContiguousIterator<T> InIterator>
ArrayView<T>::ArrayView(InIterator Begin, InIterator End)
	: mData(&*Begin)
	, mSize(End - Begin)
{
}

template<class T>
ArrayView<T> ArrayView<T>::SubArray(size_t Begin, size_t Length) const
{
	KW_ASSERT(Begin + Length <= mSize);

	return ArrayView<T>(mData + Begin, Length);
}

template<class T>
const ArrayView<T>::ValueType& ArrayView<T>::operator[](size_t Index) const
{
	KW_ASSERT(Index < mSize);

	return mData[Index];
}

template<class T>
ArrayView<T>::Iterator ArrayView<T>::GetBegin() const
{
	return Iterator(mData);
}

template<class T>
ArrayView<T>::Iterator ArrayView<T>::GetEnd() const
{
	return Iterator(mData + mSize);
}

template<class T>
ArrayView<T>::ReverseIterator ArrayView<T>::GetReverseBegin() const
{
	return ReverseIterator(Iterator(mData + mSize - 1));
}

template<class T>
ArrayView<T>::ReverseIterator ArrayView<T>::GetReverseEnd() const
{
	return ReverseIterator(Iterator(mData - 1));
}

template<class T>
ArrayView<T>::Iterator ArrayView<T>::begin() const
{
	return GetBegin();
}

template<class T>
ArrayView<T>::Iterator ArrayView<T>::end() const
{
	return GetEnd();
}

template<class T>
bool ArrayView<T>::IsEmpty() const
{
	return mSize == 0;
}

template<class T>
size_t ArrayView<T>::GetSize() const
{
	return mSize;
}

template<class T>
const ArrayView<T>::ValueType& ArrayView<T>::GetFront() const
{
	KW_ASSERT(!IsEmpty());

	return mData[0];
}

template<class T>
const ArrayView<T>::ValueType& ArrayView<T>::GetBack() const
{
	KW_ASSERT(!IsEmpty());

	return mData[mSize - 1];
}

template<class T>
const ArrayView<T>::ValueType* ArrayView<T>::GetData() const
{
	return mData;
}

template<class T>
bool ArrayView<T>::operator==(const ArrayView& Other) const
{
	if (mSize != Other.mSize)
	{
		return false;
	}

	for (size_t Index = 0; Index < mSize; Index++)
	{
		if (mData[Index] != Other.mData[Index])
		{
			return false;
		}
	}

	return true;
}

template<class T>
bool ArrayView<T>::operator!=(const ArrayView& Other) const
{
	return !(*this == Other);
}

template<class T>
bool ArrayView<T>::operator<(const ArrayView& Other) const
{
	for (size_t Index = 0, Size = mSize < Other.mSize ? mSize : Other.mSize; Index < Size; Index++)
	{
		if (!(mData[Index] < Other.mData[Index]))
		{
			return false;
		}
	}

	return mSize < Other.mSize;
}

template<class T>
bool ArrayView<T>::operator<=(const ArrayView& Other) const
{
	return !(Other < *this);
}

template<class T>
bool ArrayView<T>::operator>(const ArrayView& Other) const
{
	return Other < *this;
}

template<class T>
bool ArrayView<T>::operator>=(const ArrayView& Other) const
{
	return !(*this < Other);
}

} // namespace kw
