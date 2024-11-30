#pragma once

#include "Concepts.h"
#include "Iterators.h"
#include "MallocAllocator.h"
#include "Utility.h"

#include <initializer_list>

namespace kw
{

// TODO: Description.
template <class T, class Allocator = MallocAllocator<T>>
class Vector : protected Allocator
{
public:
    using ValueType = T;
    using AllocatorType = Allocator;

    using Iterator = RandomAccessIterator<T>;
    using ConstIterator = RandomAccessIterator<const T>;
    using ReverseIterator = ::kw::ReverseIterator<Iterator>;
    using ConstReverseIterator = ::kw::ReverseIterator<ConstIterator>;

    // Construct an empty container.
	explicit Vector(const Allocator& InAllocator = Allocator());

    // Construct a container with the given number of default-constructed elements.
	explicit Vector(size_t Size, const Allocator& InAllocator = Allocator());

    // Construct a container with the given number of copies of the specified object.
    Vector(size_t Size, const T& Value, const Allocator& InAllocator = Allocator());

    // Construct a container from the given list of objects.
    Vector(std::initializer_list<T> List, const Allocator& InAllocator = Allocator());

    // Construct a container from the given range of objects. The range must be valid.
    template <class InIterator>
	Vector(InIterator First, InIterator Last, const Allocator& InAllocator = Allocator());

	// TODO
	template <class OtherAllocator>
    Vector(const Vector<T, OtherAllocator>& Other, const Allocator& InAllocator = Allocator()) requires Concepts::CopyConstructible<T>;

	// TODO
	Vector(const Vector& Other) requires Concepts::CopyConstructible<T>;

	// TODO
    Vector(Vector&& Other);

	// TODO
	~Vector();

	// TODO
	template <class OtherAllocator>
    Vector& operator=(const Vector<T, OtherAllocator>& Other) requires Concepts::CopyConstructible<T>;

	// TODO
    Vector& operator=(Vector&& Other);

    // Replace all elements of the container with the given list of objects.
    Vector& operator=(std::initializer_list<T> List);

    // Replace all elements of the container with the given number of default-constructed elements.
    void Assign(size_t Size);

    // Replace all elements of the container with the given number of copies of specified object.
    void Assign(size_t Size, const T& Value);

	// Replace all elements of the container with the given range of objects.
	template <class InIterator>
    void Assign(InIterator First, InIterator Last);

    // Resize the container to the given Size. New elements are default-constructed.
    void Resize(size_t Size);

    // Resize the container to the given Size. New elements are copied from the specified object.
    void Resize(size_t Size, const T& Value);

    // Allocate at least the given number of elements in the container.
    // If the current capacity is already equal or greater, the function does nothing.
    void Reserve(size_t Capacity);

    // Clear the container.
    void Clear();

    // Insert the given object before the specified element. `iterator` must be valid.
    Iterator Insert(ConstIterator Iterator, const T& Value);
    Iterator Insert(ConstIterator Iterator, T&& Value);

    // Insert the given range of objects before the specified element. Iterator must be valid.
    // `first` and `last` must be valid. `first` must be dereferenceable. Both must not reference this container.
    template <class InIterator>
    Iterator Insert(ConstIterator Iterator, InIterator First, InIterator Last);

    // Remove the specified element from the container. Iterator must be valid and dereferenceable.
    Iterator Erase(ConstIterator Iterator);

    // Remove the specified range [first, last) of elements from the container.
    // `first` must be valid and dereferenceable. `last` must be valid.
    Iterator Erase(ConstIterator First, ConstIterator Last);

	// TODO: Append containers, views, and arrays with known size.
	// TODO: Append InIterator first, InIterator last

    // Add an element to the end.
    void PushBack(const T& Value);
    void PushBack(T&& Value);

    // Construct an element in-place at the end.
    template <class... Args>
    T& EmplaceBack(Args&&... Args);

    // Remove the last element. The container must not be empty.
    void PopBack();

    // Return an element with given index. Index must be less than the container's size.
    T& operator[](size_t Index);
    const T& operator[](size_t Index) const;

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

    // Return the first element. The container must not be empty.
    T& GetFront();
    const T& GetFront() const;

    // Return the last element. The container must not be empty.
    T& GetBack();
    const T& GetBack() const;

    // Return the underlying array. May be null.
    T* GetData();
    const T* GetData() const;

    // Return the associated allocator.
    const Allocator& GetAllocator() const;

	// TODO: <=>

protected:
    void DefaultInit(size_t Size);
    void ValueInit(size_t Size, const T& Value);
    void CopyInit(const T* Data, size_t Size);

    template <class InIterator>
    void IteratorInit(InIterator First, InIterator Last);

    void DefaultConstructRange(T* Data, size_t Size);
    void ValueConstructRange(T* Data, const T& Value, size_t Size);
    void CopyConstructRange(T* Dst, const T* Src, size_t Size);
    void MoveConstructRange(T* Dst, T* Src, size_t Size);

    template <class InIterator>
    void IteratorConstructRange(T* Dst, InIterator Src, size_t Size);

    void DefaultAssignRange(T* Data, size_t Size);
    void ValueAssignRange(T* Data, const T& Value, size_t Size);
    void CopyAssignRange(T* Dst, const T* Src, size_t Size);
    void MoveAssignRange(T* Dst, T* Src, size_t Size);
    void MoveAssignOverlappedRange(T* Dst, T* Src, size_t Size);

    template <class InIterator>
    void IteratorAssignRange(T* Dst, InIterator& Src, size_t Size);

    void DestroyRange(T* Data, size_t Size);

    void DestroyAllAndDeallocate();
    void AssignFromMemory(const T* Data, size_t Size);
    void ReserveUnchecked(size_t Capacity);
    void ShiftElementsRight(ptrdiff_t Index);

    T* m_data;
    size_t m_size;
    size_t m_capacity;
};

} // namespace kw

#include "VectorImpl.h"
