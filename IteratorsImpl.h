#pragma once

#include "Iterators.h"

namespace kw
{

template <typename Iterator>
struct Iterators::IsRandomAccessIterator : TypeTraits::FalseType {};

template <typename T>
struct Iterators::IsRandomAccessIterator<T*> : TypeTraits::TrueType {};

template <typename T>
struct Iterators::IsRandomAccessIterator<RandomAccessIterator<T>> : TypeTraits::TrueType {};

template <typename Iterator>
inline Iterator Iterators::GetPrev(Iterator iterator)
{
    return --iterator;
}

template <typename Iterator>
inline Iterator Iterators::GetNext(Iterator iterator)
{
    return ++iterator;
}

template <typename Iterator>
inline ptrdiff_t Iterators::GetDistance(Iterator first, Iterator last)
{
    if constexpr (Iterators::isRandomAccessIterator<Iterator>)
    {
        return last - first;
    }
    else
    {
        ptrdiff_t result = 0;
        while (first != last)
        {
            ++first;
            ++result;
        }
        return result;
    }
}

template <typename T>
inline RandomAccessIterator<T>::RandomAccessIterator(T* element)
    : m_element(element)
{
}

template <typename T>
inline RandomAccessIterator<T>::RandomAccessIterator(const RandomAccessIterator<TypeTraits::RemoveConst<T>>& iterator)
    : m_element(&*iterator)
{
}

template <typename T>
inline RandomAccessIterator<T>::ValueType& RandomAccessIterator<T>::operator*() const
{
    return *m_element;
}

template <typename T>
inline RandomAccessIterator<T>::ValueType* RandomAccessIterator<T>::operator->() const
{
    return m_element;
}

template <typename T>
inline RandomAccessIterator<T>& RandomAccessIterator<T>::operator++()
{
    m_element++;
    return *this;
}

template <typename T>
inline RandomAccessIterator<T> RandomAccessIterator<T>::operator++(int)
{
    RandomAccessIterator result(m_element);
    m_element++;
    return result;
}

template <typename T>
inline RandomAccessIterator<T>& RandomAccessIterator<T>::operator--()
{
    m_element--;
    return *this;
}

template <typename T>
inline RandomAccessIterator<T> RandomAccessIterator<T>::operator--(int)
{
    RandomAccessIterator result(m_element);
    m_element--;
    return result;
}

template <typename T>
inline RandomAccessIterator<T>& RandomAccessIterator<T>::operator+=(size_t delta)
{
    m_element += delta;
    return *this;
}

template <typename T>
inline RandomAccessIterator<T>& RandomAccessIterator<T>::operator-=(size_t delta)
{
    m_element += delta;
    return *this;
}

template <typename T>
inline RandomAccessIterator<T> operator+(const RandomAccessIterator<T>& lhs, size_t rhs)
{
    return RandomAccessIterator(lhs.m_element + rhs);
}

template <typename T>
inline RandomAccessIterator<T> operator+(size_t lhs, const RandomAccessIterator<T>& rhs)
{
    return RandomAccessIterator(lhs + rhs.m_element);
}

template <typename T>
inline RandomAccessIterator<T> operator-(const RandomAccessIterator<T>& lhs, size_t rhs)
{
    return RandomAccessIterator(lhs.m_element - rhs);
}

template <typename T>
inline ptrdiff_t operator-(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<T>& rhs)
{
    return lhs.m_element - rhs.m_element;
}

template <typename Iterator>
inline ReverseIterator<Iterator>::ReverseIterator(Iterator iterator)
    : m_iterator(iterator)
{
}

template <typename Iterator>
inline ReverseIterator<Iterator>::ValueType& ReverseIterator<Iterator>::operator*() const
{
    return *m_iterator;
}

template <typename Iterator>
inline ReverseIterator<Iterator>::ValueType* ReverseIterator<Iterator>::operator->() const
{
    return m_iterator;
}

template <typename Iterator>
inline ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator++()
{
    m_iterator--;
    return *this;
}

template <typename Iterator>
inline ReverseIterator<Iterator> ReverseIterator<Iterator>::operator++(int)
{
    ReverseIterator result(m_iterator);
    m_iterator--;
    return result;
}

template <typename Iterator>
inline ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator--()
{
    m_iterator++;
    return *this;
}

template <typename Iterator>
inline ReverseIterator<Iterator> ReverseIterator<Iterator>::operator--(int)
{
    ReverseIterator result(m_iterator);
    m_iterator++;
    return result;
}

template <typename Iterator>
inline ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator+=(size_t delta)
{
    m_iterator -= delta;
    return *this;
}

template <typename Iterator>
inline ReverseIterator<Iterator>& ReverseIterator<Iterator>::operator-=(size_t delta)
{
    m_iterator -= delta;
    return *this;
}

template <typename Iterator>
inline ReverseIterator<Iterator> operator+(const ReverseIterator<Iterator>& lhs, size_t rhs)
{
    return ReverseIterator(lhs.m_iterator - rhs);
}

template <typename Iterator>
inline ReverseIterator<Iterator> operator+(size_t lhs, const ReverseIterator<Iterator>& rhs)
{
    return ReverseIterator(rhs.m_iterator - lhs);
}

template <typename Iterator>
inline ReverseIterator<Iterator> operator-(const ReverseIterator<Iterator>& lhs, size_t rhs)
{
    return ReverseIterator(lhs.m_iterator + rhs);
}

template <typename Iterator>
inline ptrdiff_t operator-(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
    return rhs.m_iterator - lhs.m_iterator;
}

template <typename Iterator>
inline auto operator<=>(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
    return rhs.m_iterator <=> lhs.m_iterator;
}

} // namespace kw
