#pragma once

#include "Assert.h"
#include "Iterators.h"

namespace kw
{

// Stores a contiguous set of elements of fixed size and specified type.
template<class T, size_t N>
class Array
{
public:
	using ValueType = T;

	using Iterator = RandomAccessIterator<ValueType>;
	using ConstIterator = RandomAccessIterator<const ValueType>;
	using ReverseIterator = ::kw::ReverseIterator<Iterator>;
	using ConstReverseIterator = ::kw::ReverseIterator<ConstIterator>;

	// Return an element with given index. Index must be less than the array's size.
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

	// Return whether the array is empty.
	constexpr bool IsEmpty() const;

	// Return how many elements are stored in the array.
	constexpr size_t GetSize() const;

	// Return the first element. The array must not be empty.
	ValueType& GetFront();
	const ValueType& GetFront() const;

	// Return the last element. The array must not be empty.
	ValueType& GetBack();
	const ValueType& GetBack() const;

	// Return address of the array.
	ValueType* GetData();
	const ValueType* GetData() const;

	// Return whether two arrays are equal.
	bool operator==(const Array<ValueType, N>& Other) const;

	// Return whether two arrays are not equal.
	bool operator!=(const Array<ValueType, N>& Other) const;

	// Return whether this array is lexicographically less than the specified array.
	template<size_t M>
	bool operator<(const Array<ValueType, M>& Other) const;

	// Return whether this array is lexicographically less or equal than the specified array.
	bool operator<=(const Array<ValueType, N>& Other) const;

	// Return whether this array is lexicographically greater than the specified array.
	template<size_t M>
	bool operator>(const Array<ValueType, M>& Other) const;

	// Return whether this array is lexicographically greater or equal than the specified array.
	bool operator>=(const Array<ValueType, N>& Other) const;

	// Do not access Data directly. Public memeber in order for implicit constructors & assignment operators to work.
	ValueType Data[N];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T, size_t N>
T& Array<T, N>::operator[](size_t Index)
{
	KW_ASSERT(Index < N);

	return Data[Index];
}

template<class T, size_t N>
const T& Array<T, N>::operator[](size_t Index) const
{
	KW_ASSERT(Index < N);

	return Data[Index];
}

template<class T, size_t N>
Array<T, N>::Iterator Array<T, N>::GetBegin()
{
	return Iterator(&Data);
}

template<class T, size_t N>
Array<T, N>::ConstIterator Array<T, N>::GetBegin() const
{
	return ConstIterator(&Data);
}

template<class T, size_t N>
Array<T, N>::ConstIterator Array<T, N>::GetConstBegin() const
{
	return GetBegin();
}

template<class T, size_t N>
Array<T, N>::Iterator Array<T, N>::GetEnd()
{
	return Iterator(&Data + N);
}

template<class T, size_t N>
Array<T, N>::ConstIterator Array<T, N>::GetEnd() const
{
	return ConstIterator(&Data + N);
}

template<class T, size_t N>
Array<T, N>::ConstIterator Array<T, N>::GetConstEnd() const
{
	return GetEnd();
}

template<class T, size_t N>
Array<T, N>::ReverseIterator Array<T, N>::GetReverseBegin()
{
	return ReverseIterator(Iterator(&Data + N - 1));
}

template<class T, size_t N>
Array<T, N>::ConstReverseIterator Array<T, N>::GetReverseBegin() const
{
	return ConstReverseIterator(ConstIterator(&Data + N - 1));
}

template<class T, size_t N>
Array<T, N>::ConstReverseIterator Array<T, N>::GetConstReverseBegin() const
{
	return GetReverseBegin();
}

template<class T, size_t N>
Array<T, N>::ReverseIterator Array<T, N>::GetReverseEnd()
{
	return ReverseIterator(Iterator(&Data - 1));
}

template<class T, size_t N>
Array<T, N>::ConstReverseIterator Array<T, N>::GetReverseEnd() const
{
	return ConstReverseIterator(ConstIterator(&Data - 1));
}

template<class T, size_t N>
Array<T, N>::ConstReverseIterator Array<T, N>::GetConstReverseEnd() const
{
	return GetReverseEnd() const;
}

template<class T, size_t N>
Array<T, N>::Iterator Array<T, N>::begin()
{
	return GetBegin();
}

template<class T, size_t N>
Array<T, N>::ConstIterator Array<T, N>::begin() const
{
	return GetBegin();
}

template<class T, size_t N>
Array<T, N>::Iterator Array<T, N>::end()
{
	return GetEnd();
}

template<class T, size_t N>
Array<T, N>::ConstIterator Array<T, N>::end() const
{
	return GetEnd();
}

template<class T, size_t N>
constexpr bool Array<T, N>::IsEmpty() const
{
	return N == 0;
}

template<class T, size_t N>
constexpr size_t Array<T, N>::GetSize() const
{
	return N;
}

template<class T, size_t N>
T& Array<T, N>::GetFront()
{
	static_assert(!IsEmpty());

	return Data[0];
}

template<class T, size_t N>
const T& Array<T, N>::GetFront() const
{
	static_assert(!IsEmpty());

	return Data[0];
}

template<class T, size_t N>
T& Array<T, N>::GetBack()
{
	static_assert(!IsEmpty());

	return Data[N - 1];
}

template<class T, size_t N>
const T& Array<T, N>::GetBack() const
{
	static_assert(!IsEmpty());

	return Data[N - 1];
}

template<class T, size_t N>
T* Array<T, N>::GetData()
{
	return &Data;
}

template<class T, size_t N>
const T* Array<T, N>::GetData() const
{
	return &Data;
}

template<class T, size_t N>
bool Array<T, N>::operator==(const Array<ValueType, N>& Other) const
{
	for (size_t Index = 0; Index < N; Index++)
	{
		if (Data[Index] != Other.Data[Index])
		{
			return false;
		}
	}

	return true;
}

template<class T, size_t N>
bool Array<T, N>::operator!=(const Array<ValueType, N>& Other) const
{
	return !(*this == Other);
}

template<class T, size_t N>
template<size_t M>
bool Array<T, N>::operator<(const Array<ValueType, M>& Other) const
{
	for (size_t Index = 0, Size = N < M ? N : M; Index < Size; Index++)
	{
		if (!(Data[Index] < Other.Data[Index]))
		{
			return false;
		}
	}

	return N < M;
}

template<class T, size_t N>
bool Array<T, N>::operator<=(const Array<ValueType, N>& Other) const
{
	return !(Other < *this);
}

template<class T, size_t N>
template<size_t M>
bool Array<T, N>::operator>(const Array<ValueType, M>& Other) const
{
	return Other < *this;
}

template<class T, size_t N>
bool Array<T, N>::operator>=(const Array<ValueType, N>& Other) const
{
	return !(*this < Other);
}

} // namespace kw
