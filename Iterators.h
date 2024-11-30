#pragma once

#include "TypeTraits.h"

#include <compare>

namespace kw
{

// TODO: Description.
class Iterators
{
public:
    Iterators() = delete;

    template <class Iterator>
    struct IsRandomAccessIterator;

    template <class Iterator>
    static constexpr bool isRandomAccessIterator = IsRandomAccessIterator<Iterator>::value;

    template <class Iterator>
    static Iterator GetPrev(Iterator iterator);

    template <class Iterator>
    static Iterator GetNext(Iterator iterator);

    template <class Iterator>
    static ptrdiff_t GetDistance(Iterator first, Iterator last);
};

// TODO: Description.
template <class T>
class RandomAccessIterator
{
public:
    using ValueType = T;

    RandomAccessIterator() = default;
    explicit RandomAccessIterator(T* element);
    RandomAccessIterator(const RandomAccessIterator<TypeTraits::RemoveConst<T>>& iterator);

	ValueType& operator*() const;
	ValueType* operator->() const;

    RandomAccessIterator& operator++();
    RandomAccessIterator operator++(int);

    RandomAccessIterator& operator--();
    RandomAccessIterator operator--(int);

    RandomAccessIterator& operator+=(size_t delta);
    RandomAccessIterator& operator-=(size_t delta);

    template <class U>
    friend RandomAccessIterator<U> operator+(const RandomAccessIterator<U>& lhs, size_t rhs);

    template <class U>
    friend RandomAccessIterator<U> operator+(size_t lhs, const RandomAccessIterator<U>& rhs);

    template <class U>
    friend RandomAccessIterator<U> operator-(const RandomAccessIterator<U>& lhs, size_t rhs);

    template <class U>
    friend ptrdiff_t operator-(const RandomAccessIterator<U>& lhs, const RandomAccessIterator<U>& rhs);

    friend auto operator<=>(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) = default;

private:
    T* m_element;
};

// TODO: Description.
template <class Iterator>
class ReverseIterator
{
public:
    using ValueType = Iterator::ValueType;

    ReverseIterator() = default;
    explicit ReverseIterator(Iterator iterator);

    ValueType& operator*() const;
    ValueType* operator->() const;

    ReverseIterator& operator++();
    ReverseIterator operator++(int);

    ReverseIterator& operator--();
    ReverseIterator operator--(int);

    ReverseIterator& operator+=(size_t delta);
    ReverseIterator& operator-=(size_t delta);

    template <class U>
    friend ReverseIterator<U> operator+(const ReverseIterator<U>& lhs, size_t rhs);

    template <class U>
    friend ReverseIterator<U> operator+(size_t lhs, const ReverseIterator<U>& rhs);

    template <class U>
    friend ReverseIterator<U> operator-(const ReverseIterator<U>& lhs, size_t rhs);

    template <class U>
    friend ptrdiff_t operator-(const ReverseIterator<U>& lhs, const ReverseIterator<U>& rhs);

    template <class U>
    friend auto operator<=>(const ReverseIterator<U>& lhs, const ReverseIterator<U>& rhs);

private:
    Iterator m_iterator;
};

} // namespace kw

#include "IteratorsImpl.h"
