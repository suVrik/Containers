#pragma once

#include "Vector.h"

namespace kw {

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector()
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Allocator& allocator)
    : Allocator(allocator)
    , m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count)
{
    DefaultInit(count);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count, const Allocator& allocator)
    : Allocator(allocator)
{
    DefaultInit(count);
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::DefaultInit(size_t count)
{
    if (count != 0)
    {
        m_data = Allocator::Allocate(count);
        m_size = count;
        m_capacity = count;

        DefaultConstructRange(m_data, count);
    }
    else
    {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count, const T& value)
{
    ValueInit(count, value);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count, const T& value, const Allocator& allocator)
    : Allocator(allocator)
{
    ValueInit(count, value);
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::ValueInit(size_t count, const T& value)
{
    if (count != 0)
    {
        m_data = Allocator::Allocate(count);
        m_size = count;
        m_capacity = count;

        ValueConstructRange(m_data, value, count);
    }
    else
    {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> list)
{
    CopyInit(list.begin(), list.size());
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> list, const Allocator& allocator)
    : Allocator(allocator)
{
    CopyInit(list.begin(), list.size());
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::CopyInit(const T* data, size_t size)
{
    if (size != 0)
    {
        m_data = Allocator::Allocate(size);
        m_size = size;
        m_capacity = size;

        CopyConstructRange(m_data, data, size);
    }
    else
    {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }
}

template <typename T, typename Allocator>
template <typename InIterator>
Vector<T, Allocator>::Vector(InIterator first, InIterator last)
{
    IteratorInit(first, last);
}

template <typename T, typename Allocator>
template <typename InIterator>
Vector<T, Allocator>::Vector(InIterator first, InIterator last, const Allocator& allocator)
    : Allocator(allocator)
{
    IteratorInit(first, last);
}

template <typename T, typename Allocator>
template <typename InIterator>
inline void Vector<T, Allocator>::IteratorInit(InIterator first, InIterator last)
{
    size_t count = Iterators::GetDistance(first, last);
    if (count != 0)
    {
        m_data = Allocator::Allocate(count);
        m_size = count;
        m_capacity = count;

        IteratorConstructRange(m_data, first, count);
    }
    else
    {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& other) requires Concepts::CopyConstructible<T>
    : Allocator(other)
{
    CopyInit(other.GetData(), other.GetSize());
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other)
    : Allocator(Move(other))
    , m_data(other.m_data)
    , m_size(other.m_size)
    , m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
    DestroyAllAndDeallocate();
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::DestroyAllAndDeallocate()
{
    DestroyRange(m_data, m_size);

    // `Deallocate` must handle `nullptr` by design.
    Allocator::Deallocate(m_data);
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& other) requires Concepts::CopyConstructible<T>
{
    // Currently, the allocator is not propagated from copy assignment.

    if (&other != this)
    {
        if (other.m_size > m_capacity)
        {
            DestroyAllAndDeallocate();
            CopyInit(other.m_data, other.m_size);
        }
        else
        {
            // Avoid deallocation & allocation when the container already has enough capacity for new data.
            AssignFromMemory(other.m_data, other.m_size);
        }
    }

    return *this;
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::AssignFromMemory(const T* data, size_t size)
{
    if (size > m_size)
    {
        if constexpr (TypeTraits::isTriviallyCopyAssignable<T> &&
                      TypeTraits::isTriviallyCopyConstructible<T>)
        {
            Memory::Memcpy(m_data, data, sizeof(T) * size);
        }
        else
        {
            CopyAssignRange(m_data, data, m_size);
            CopyConstructRange(m_data + m_size, data + m_size, size - m_size);
        }
    }
    else
    {
        CopyAssignRange(m_data, data, size);
        DestroyRange(m_data + size, m_size - size);
    }

    m_size = size;
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& other)
{
    // Currently, the allocator is not propagated from move assignment.

    if (&other != this)
    {
        DestroyAllAndDeallocate();

        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(std::initializer_list<T> list)
{
    // Currently, the allocator is not propagated from copy assignment.

	if (list.size() > m_capacity)
	{
		DestroyAllAndDeallocate();
		CopyInit(list.begin(), list.size());
	}
	else
	{
		// Avoid deallocation & allocation when the container already has enough capacity for new data.
		AssignFromMemory(list.begin(), list.size());
	}

    return *this;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::Assign(size_t count)
{
    if (count > m_capacity)
    {
        DestroyAllAndDeallocate();
        DefaultInit(count);
    }
    else
    {
        // Avoid deallocation & allocation when the container already has enough capacity for new data.

        if (count > m_size)
        {
            if constexpr (TypeTraits::isTriviallyDefaultConstructible<T> &&
                          TypeTraits::isTriviallyCopyAssignable<T>)
            {
                Memory::Memset(m_data, 0, count);
            }
            else
            {
                DefaultAssignRange(m_data, m_size);
                DefaultConstructRange(m_data + m_size, count - m_size);
            }
        }
        else
        {
            DefaultAssignRange(m_data, count);
            DestroyRange(m_data + count, m_size - count);
        }

        m_size = count;
    }
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::Assign(size_t count, const T& value)
{
    if (count > m_capacity)
    {
        DestroyAllAndDeallocate();
        ValueInit(count, value);
    }
    else
    {
        // Avoid deallocation & allocation when the container already has enough capacity for new data.

        if (count > m_size)
        {
            if constexpr (TypeTraits::isTriviallyCopyConstructible<T> &&
                          TypeTraits::isTriviallyCopyAssignable<T>)
            {
                if constexpr (sizeof(T) == 1)
                {
                    // Very fast Memset for one-byte-long trivially-copy-constructible data types.
                    char c;
                    Memory::Memcpy(&c, &value, 1);
                    Memory::Memset(m_data, c, count);
                }
                else
                {
                    if constexpr (TypeTraits::isTriviallyDefaultConstructible<T>)
                    {
                        T test{};
                        if (Memory::Memcmp(&value, &test, sizeof(T)) == 0)
                        {
                            // Just quickly clear the vector if `value` is zero.
                            Memory::Memset(m_data, 0, sizeof(T) * count);
                            return;
                        }
                    }

                    for (T* data = m_data; count != 0; count--, data++)
                    {
                        *data = value;
                    }
                }
            }
            else
            {
                T* data = m_data;

                for (size_t size = m_size; size != 0; size--, data++)
                {
                    *data = value;
                }

                for (size_t size = count - m_size; size != 0; size--, data++)
                {
                    new (data) T(value);
                }
            }
        }
        else
        {
            ValueAssignRange(m_data, value, count);
            DestroyRange(m_data + count, m_size - count);
        }

        m_size = count;
    }
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::Resize(size_t size)
{
    if (size > m_size)
    {
        if (size > m_capacity)
        {
            ReserveUnchecked(size);
        }

        DefaultConstructRange(m_data + m_size, size - m_size);

        m_size = size;
    }
    else if (size < m_size)
    {
        DestroyRange(m_data + size, m_size - size);

        m_size = size;
    }
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::Resize(size_t size, const T& value)
{
    if (size > m_size)
    {
        if (size > m_capacity)
        {
            ReserveUnchecked(size);
        }

        ValueConstructRange(m_data + m_size, value, size - m_size);

        m_size = size;
    }
    else if (size < m_size)
    {
        DestroyRange(m_data + size, m_size - size);

        m_size = size;
    }
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::Reserve(size_t capacity)
{
    if (capacity > m_capacity)
    {
        ReserveUnchecked(capacity);
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::ReserveUnchecked(size_t capacity)
{
    T* newData = Allocator::Allocate(capacity);

    MoveConstructRange(newData, m_data, m_size);

    DestroyAllAndDeallocate();

    m_data = newData;
    m_capacity = capacity;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::Clear()
{
    DestroyRange(m_data, m_size);
    m_size = 0;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Iterator Vector<T, Allocator>::Insert(ConstIterator iterator, const T& value)
{
    if (iterator != GetConstEnd())
    {
        // `ReserveUnchecked` invalidates iterators and addresses. Work with an index instead.
        ptrdiff_t index = iterator - GetConstBegin();

        if (m_size == m_capacity)
        {
            ReserveUnchecked(m_capacity > 0 ? m_capacity * 2 : 1);
        }

        // Move-constructs one element in the end, move-assignes the rest.
        ShiftElementsRight(index);

        // Since insertion happens not in the end, this element was constructed sometime earlier
        // and just recently was move-assigned to the next element.
        m_data[index] = value;

        return Iterator(m_data + index);
    }
    else
    {
        PushBack(value);
        return Iterator(m_data + m_size - 1);
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Iterator Vector<T, Allocator>::Insert(ConstIterator iterator, T&& value)
{
    if (iterator != GetConstEnd())
    {
        // `ReserveUnchecked` invalidates iterators and addresses. Work with an index instead.
        ptrdiff_t index = iterator - GetConstBegin();

        if (m_size == m_capacity)
        {
            ReserveUnchecked(m_capacity > 0 ? m_capacity * 2 : 1);
        }

        // Move-constructs one element in the end, move-assignes the rest.
        ShiftElementsRight(index);

        // Since insertion happens not in the end, this element was constructed sometime earlier
        // and just recently was move-assigned to the next element.
        m_data[index] = Move(value);

        return Iterator(m_data + index);
    }
    else
    {
        PushBack(Move(value));
        return Iterator(m_data + m_size - 1);
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::ShiftElementsRight(ptrdiff_t index)
{
    if constexpr (TypeTraits::isTriviallyMoveConstructible<T> &&
                  TypeTraits::isTriviallyMoveAssignable<T>)
    {
        // No need to separate construction and assignment here.
        Memory::Memmove(m_data + index + 1, m_data + index, sizeof(T) * (m_size - index));
    }
    else
    {
        // `m_size` is guaranteed to be less than `m_capacity`. `m_size` is guaranteed to be greater than 0.
        new (m_data + m_size) T(Move(m_data[m_size - 1]));

        // `index` is guaranteed to be less than `m_size`.
        MoveAssignOverlappedRange(m_data + index + 1, m_data + index, m_size - index - 1);
    }

    m_size++;
}

template <typename T, typename Allocator>
template <typename InIterator>
Vector<T, Allocator>::Iterator Vector<T, Allocator>::Insert(ConstIterator iterator, InIterator first, InIterator last)
{
    // `ReserveUnchecked` invalidates iterators and addresses. Work with an index instead.
    ptrdiff_t index = iterator - GetConstBegin();

    ptrdiff_t count = Iterators::GetDistance(first, last);

    size_t requiredCapacity = m_size + count;
    if (requiredCapacity > m_capacity)
    {
        size_t desiredCapacity = m_capacity * 2;
        ReserveUnchecked(desiredCapacity > requiredCapacity ? desiredCapacity : requiredCapacity);
    }

    // Check if we're inserting in the end. The end insertion is significantly simpler.
    if (index != m_size)
    {
        T* end = m_data + m_size;
        T* newEnd = end + count;

        // How many existing elements must be shifted right.
        ptrdiff_t elementsToShift = m_size - index;

        if (count >= elementsToShift)
        {
            MoveConstructRange(newEnd - elementsToShift, end - elementsToShift, elementsToShift);

            if constexpr (TypeTraits::isTriviallyCopyConstructible<T> &&
                          TypeTraits::isTriviallyCopyAssignable<T> &&
                          Iterators::isRandomAccessIterator<InIterator>)
            {
                Memory::Memcpy(end - elementsToShift, &*first, sizeof(T) * count);
            }
            else
            {
                IteratorAssignRange(end - elementsToShift, first, elementsToShift);
                IteratorConstructRange(end, first, count - elementsToShift);
            }
        }
        else
        {
            MoveConstructRange(end, end - count, count);
            MoveAssignOverlappedRange(newEnd - elementsToShift, end - elementsToShift, elementsToShift - count);
            IteratorAssignRange(end - elementsToShift, first, count);
        }
    }
    else
    {
        IteratorConstructRange(m_data + m_size, first, count);
    }

    m_size += count;

    return Iterator(m_data + index);
}

// TODO: Refactor this.
template <typename T, typename Allocator>
Vector<T, Allocator>::Iterator Vector<T, Allocator>::Erase(ConstIterator iterator)
{
    // This trick is just to get rid of `const` specifier required by the interface. It's optimized away.
    T* curr = m_data + (iterator - GetConstBegin());
    T* result = curr;
    T* next = curr + 1;
    T* end = m_data + m_size;

    m_size--;

    if constexpr (!TypeTraits::isTriviallyMoveAssignable<T>)
    {
        for (; next != end; curr = next, next++)
        {
            *curr = Move(*next);
        }
    }
    else
    {
        Memory::Memcpy(curr, next, sizeof(T) * (end - next));
    }

    if constexpr (!TypeTraits::isTriviallyDestructible<T>)
    {
        curr->~T();
    }

    return Iterator(result);
}

// TODO: Refactor this.
template <typename T, typename Allocator>
Vector<T, Allocator>::Iterator Vector<T, Allocator>::Erase(ConstIterator first, ConstIterator last)
{
    // This trick is just to get rid of `const` specifier required by the interface. It's optimized away.
    T* first2 = m_data + (first - GetConstBegin());
    T* last2 = m_data + (last - GetConstBegin());
    T* result = first2;
    T* end = m_data + m_size;

    m_size -= last2 - first2;

    if constexpr (!TypeTraits::isTriviallyMoveAssignable<T>)
    {
        for (; last2 != end; first2++, last2++)
        {
            *first2 = Move(*last2);
        }
    }
    else
    {
        Memory::Memcpy(first2, last2, sizeof(T) * (end - last2));
    }

    if constexpr (!TypeTraits::isTriviallyDestructible<T>)
    {
        for (; first2 != end; first2++)
        {
            first2->~T();
        }
    }

    return Iterator(result);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::PushBack(const T& value)
{
    if (m_size == m_capacity)
    {
        ReserveUnchecked(m_capacity > 0 ? m_capacity * 2 : 1);
    }

    new (m_data + m_size) T(value);
    m_size++;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::PushBack(T&& value)
{
    if (m_size == m_capacity)
    {
        ReserveUnchecked(m_capacity > 0 ? m_capacity * 2 : 1);
    }

    new (m_data + m_size) T(Move(value));
    m_size++;
}

template <typename T, typename Allocator>
template <typename... Args>
T& Vector<T, Allocator>::EmplaceBack(Args&&... args)
{
    if (m_size == m_capacity)
    {
        ReserveUnchecked(m_capacity > 0 ? m_capacity * 2 : 1);
    }

    new (m_data + m_size) T(Forward(args)...);
    return m_data[m_size++];
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::PopBack()
{
    if constexpr (!TypeTraits::isTriviallyDestructible<T>)
    {
        GetBack().~T();
    }
    m_size--;
}

template <typename T, typename Allocator>
inline T& Vector<T, Allocator>::operator[](size_t index)
{
    return m_data[index];
}

template <typename T, typename Allocator>
inline const T& Vector<T, Allocator>::operator[](size_t index) const
{
    return m_data[index];
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::Iterator Vector<T, Allocator>::GetBegin()
{
    return Iterator(m_data);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetBegin() const
{
    return ConstIterator(m_data);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetConstBegin() const
{
    return ConstIterator(m_data);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::Iterator Vector<T, Allocator>::GetEnd()
{
    return Iterator(m_data + m_size);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetEnd() const
{
    return ConstIterator(m_data + m_size);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::GetConstEnd() const
{
    return ConstIterator(m_data + m_size);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseBegin()
{
    return ReverseIterator(Iterator(m_data + m_size - 1));
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseBegin() const
{
    return ConstReverseIterator(ConstIterator(m_data + m_size - 1));
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetConstReverseBegin() const
{
    return ConstReverseIterator(ConstIterator(m_data + m_size - 1));
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::GetReverseEnd()
{
    return ReverseIterator(Iterator(m_data - 1));
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetReverseEnd() const
{
    return ConstReverseIterator(ConstIterator(m_data - 1));
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::GetConstReverseEnd() const
{
    return ConstReverseIterator(ConstIterator(m_data - 1));
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::Iterator Vector<T, Allocator>::begin()
{
    return Iterator(m_data);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::begin() const
{
    return ConstIterator(m_data);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::Iterator Vector<T, Allocator>::end()
{
    return Iterator(m_data + m_size);
}

template <typename T, typename Allocator>
inline Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::end() const
{
    return ConstIterator(m_data + m_size);
}

template <typename T, typename Allocator>
inline bool Vector<T, Allocator>::IsEmpty() const
{
    return m_size == 0;
}

template <typename T, typename Allocator>
inline size_t Vector<T, Allocator>::GetSize() const
{
    return m_size;
}

template <typename T, typename Allocator>
inline size_t Vector<T, Allocator>::GetCapacity() const
{
    return m_capacity;
}

template <typename T, typename Allocator>
inline T& Vector<T, Allocator>::GetFront()
{
    return m_data[0];
}

template <typename T, typename Allocator>
inline const T& Vector<T, Allocator>::GetFront() const
{
    return m_data[0];
}

template <typename T, typename Allocator>
inline T& Vector<T, Allocator>::GetBack()
{
    return m_data[m_size - 1];
}

template <typename T, typename Allocator>
inline const T& Vector<T, Allocator>::GetBack() const
{
    return m_data[m_size - 1];
}

template <typename T, typename Allocator>
inline T* Vector<T, Allocator>::GetData()
{
    return m_data;
}

template <typename T, typename Allocator>
inline const T* Vector<T, Allocator>::GetData() const
{
    return m_data;
}

template <typename T, typename Allocator>
inline const Allocator& Vector<T, Allocator>::GetAllocator() const
{
    return *this;
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::DefaultConstructRange(T* data, size_t count)
{
    if constexpr (TypeTraits::isTriviallyDefaultConstructible<T>)
    {
        Memory::Memset(data, 0, count);
    }
    else
    {
        for (; count != 0; count--, data++)
        {
            new (data) T();
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::ValueConstructRange(T* data, const T& value, size_t count)
{
    if constexpr (TypeTraits::isTriviallyCopyConstructible<T> &&
                  sizeof(T) == 1)
    {
        // Very fast Memset for one-byte-long trivially-copy-constructible data types.
        char c;
        Memory::Memcpy(&c, &value, 1);
        Memory::Memset(data, c, count);
    }
    else
    {
        if constexpr (TypeTraits::isTriviallyDefaultConstructible<T>)
        {
            T test{};
            if (Memory::Memcmp(&value, &test, sizeof(T)) == 0)
            {
                // Just quickly Memset if `value` is zero.
                Memory::Memset(data, 0, sizeof(T) * count);
                return;
            }
        }

        for (; count != 0; count--, data++)
        {
            new (data) T(value);
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::CopyConstructRange(T* dst, const T* src, size_t count)
{
    if constexpr (TypeTraits::isTriviallyCopyConstructible<T>)
    {
        Memory::Memcpy(dst, src, sizeof(T) * count);
    }
    else
    {
        for (; count != 0; count--, dst++, src++)
        {
            new (dst) T(*src);
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::MoveConstructRange(T* dst, T* src, size_t count)
{
    if constexpr (TypeTraits::isTriviallyMoveConstructible<T>)
    {
        Memory::Memcpy(dst, src, sizeof(T) * count);
    }
    else
    {
        for (; count != 0; count--, dst++, src++)
        {
            new (dst) T(Move(*src));
        }
    }
}

template <typename T, typename Allocator>
template <typename InIterator>
inline void Vector<T, Allocator>::IteratorConstructRange(T* dst, InIterator src, size_t count)
{
    if constexpr (TypeTraits::isTriviallyCopyConstructible<T> &&
                  Iterators::isRandomAccessIterator<InIterator>)
    {
        Memory::Memcpy(dst, &*src, sizeof(T) * count);
    }
    else
    {
        for (; count != 0; count--, dst++, ++src)
        {
            new (dst) T(*src);
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::DefaultAssignRange(T* data, size_t count)
{
    if constexpr (TypeTraits::isTriviallyDefaultConstructible<T> &&
                  TypeTraits::isTriviallyCopyAssignable<T>)
    {
        Memory::Memset(data, 0, count);
    }
    else
    {
        for (; count != 0; count--, data++)
        {
            *data = T();
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::ValueAssignRange(T* data, const T& value, size_t count)
{
    if constexpr (TypeTraits::isTriviallyCopyConstructible<T> &&
                  TypeTraits::isTriviallyCopyAssignable<T> &&
                  sizeof(T) == 1)
    {
        // Very fast Memset for one-byte-long trivially-copy-constructible data types.
        char c;
        Memory::Memcpy(&c, &value, 1);
        Memory::Memset(data, c, count);
    }
    else
    {
        if constexpr (TypeTraits::isTriviallyDefaultConstructible<T>)
        {
            T test{};
            if (Memory::Memcmp(&value, &test, sizeof(T)) == 0)
            {
                // Just quickly Memset if `value` is zero.
                Memory::Memset(data, 0, sizeof(T) * count);
                return;
            }
        }

        for (; count != 0; count--, data++)
        {
            *data = value;
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::CopyAssignRange(T* dst, const T* src, size_t count)
{
    if constexpr (TypeTraits::isTriviallyCopyAssignable<T>)
    {
        Memory::Memcpy(dst, src, sizeof(T) * count);
    }
    else
    {
        for (; count != 0; count--, dst++, src++)
        {
            *dst = *src;
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::MoveAssignRange(T* dst, T* src, size_t count)
{
    if constexpr (TypeTraits::isTriviallyMoveAssignable<T>)
    {
        Memory::Memcpy(dst, src, sizeof(T) * count);
    }
    else
    {
        for (; count != 0; count--, dst++, src++)
        {
            *dst = Move(*src);
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::MoveAssignOverlappedRange(T* dst, T* src, size_t count)
{
    if constexpr (TypeTraits::isTriviallyMoveAssignable<T>)
    {
        Memory::Memmove(dst, src, sizeof(T) * count);
    }
    else
    {
        for (dst += count - 1, src += count - 1; count != 0; count--, dst--, src--)
        {
            *dst = Move(*src);
        }
    }
}

template <typename T, typename Allocator>
template <typename InIterator>
inline void Vector<T, Allocator>::IteratorAssignRange(T* dst, InIterator& src, size_t count)
{
    if constexpr (TypeTraits::isTriviallyCopyAssignable<T> &&
                  Iterators::isRandomAccessIterator<InIterator>)
    {
        Memory::Memcpy(dst, &*src, sizeof(T) * count);
        src += count; // Since this function is inlined, this is optimized out if `src` is not used later.
    }
    else
    {
        for (; count != 0; count--, dst++, ++src)
        {
            *dst = *src;
        }
    }
}

template <typename T, typename Allocator>
inline void Vector<T, Allocator>::DestroyRange(T* data, size_t count)
{
    if constexpr (!TypeTraits::isTriviallyDestructible<T>)
    {
        for (; count != 0; count--, data++)
        {
            data->~T();
        }
    }
}

} // namespace kw
