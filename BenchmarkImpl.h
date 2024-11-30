#pragma once

#include "Benchmark.h"

namespace kw
{

namespace benchmark_details
{

template <typename T>
char* GenerateTemplateName(const char* name)
{
    const char* templateName = typeid(T).name();
    int newNameLength = 1 + snprintf(nullptr, 0, "%s<%s>", name, templateName);
    if (newNameLength > 0)
    {
        char* newName = static_cast<char*>(Memory::Malloc(newNameLength));
        snprintf(newName, newNameLength, "%s<%s>", name, templateName);
        return newName;
    }
    return nullptr;
}

} // namespace benchmark_details

template <size_t sizesCount>
BenchmarkDescriptor::BenchmarkDescriptor(const char* name, const size_t(&sizes)[sizesCount], void(*benchmarkCallback)(size_t))
    : BenchmarkDescriptor(name, sizes, sizesCount, benchmarkCallback)
{
}

inline const char* BenchmarkDescriptor::GetName() const
{
    return m_name;
}

inline const size_t* BenchmarkDescriptor::GetSizes() const
{
    return m_sizes;
}

inline size_t BenchmarkDescriptor::GetCount() const
{
    return m_sizesCount;
}

template <template <typename> typename CallbackStruct, typename T>
BenchmarkDescriptorTemplateBase<CallbackStruct, T>::BenchmarkDescriptorTemplateBase(const char* name, const size_t* sizes, size_t sizesCount)
    : m_templateName(benchmark_details::GenerateTemplateName<T>(name))
    , m_benchmarkDescriptor(m_templateName, sizes, sizesCount, &CallbackStruct<T>::Run)
{
}

template <template <typename> typename CallbackStruct, typename T>
BenchmarkDescriptorTemplateBase<CallbackStruct, T>::~BenchmarkDescriptorTemplateBase()
{
    Memory::Free(m_templateName);
}

template <template <typename> typename CallbackStruct, typename T, typename... Ts>
BenchmarkDescriptorTemplateBase<CallbackStruct, T, Ts...>::BenchmarkDescriptorTemplateBase(const char* name, const size_t* sizes, size_t sizesCount)
    : BenchmarkDescriptorTemplateBase<CallbackStruct, Ts...>(name, sizes, sizesCount)
    , m_templateName(benchmark_details::GenerateTemplateName<T>(name))
    , m_benchmarkDescriptor(m_templateName, sizes, sizesCount, &CallbackStruct<T>::Run)
{
}

template <template <typename> typename CallbackStruct, typename T, typename... Ts>
BenchmarkDescriptorTemplateBase<CallbackStruct, T, Ts...>::~BenchmarkDescriptorTemplateBase()
{
    Memory::Free(m_templateName);
}

template <template <typename> typename CallbackStruct, typename... Ts>
BenchmarkDescriptorTemplate<CallbackStruct, BenchmarkTypes<Ts...>>::BenchmarkDescriptorTemplate(const char* name, const size_t* sizes, size_t sizesCount)
    : BenchmarkDescriptorTemplateBase<CallbackStruct, Ts...>(name, sizes, sizesCount)
{
}

template <template <typename> typename CallbackStruct, typename... Ts>
template <size_t sizesCount>
BenchmarkDescriptorTemplate<CallbackStruct, BenchmarkTypes<Ts...>>::BenchmarkDescriptorTemplate(const char* name, const size_t(&sizes)[sizesCount])
    : BenchmarkDescriptorTemplate(name, sizes, sizesCount)
{
}

template <template <typename> typename CallbackStruct, typename... Ts>
BenchmarkDescriptorTemplate<CallbackStruct, BenchmarkTypes<Ts...>>::BenchmarkDescriptorTemplate(const char* name, std::initializer_list<size_t> sizes)
    : BenchmarkDescriptorTemplate(name, sizes.begin(), sizes.size())
{
}

template <class T>
template <class U>
BenchmarkAllocator<T>::BenchmarkAllocator(const BenchmarkAllocator<U>& other)
{
}

template <class T>
T* BenchmarkAllocator<T>::Allocate(size_t count)
{
    return static_cast<T*>(BenchmarkAllocate(sizeof(T) * count, alignof(T)));
}

template <class T>
void BenchmarkAllocator<T>::Deallocate(T* address)
{
    // No-op.
}

template <class T>
T* BenchmarkAllocator<T>::allocate(size_t count)
{
    return static_cast<T*>(BenchmarkAllocate(sizeof(T) * count, alignof(T)));
}

template <class T>
void BenchmarkAllocator<T>::deallocate(T* address, size_t count)
{
    // No-op.
}

template<class T, class U>
bool operator==(const BenchmarkAllocator<T>& lhs, const BenchmarkAllocator<U>& rhs)
{
    return true;
}

template<class T, class U>
bool operator!=(const BenchmarkAllocator<T>& lhs, const BenchmarkAllocator<U>& rhs)
{
    return true;
}

} // namespace kw
