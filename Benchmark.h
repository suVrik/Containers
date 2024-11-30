#pragma once

#include "Vector.h"

#include <typeinfo>

namespace kw
{

// TODO: Description.
void DontOptimize(void* address);

// TODO: Description.
class BenchmarkDatabase
{
public:
    static BenchmarkDatabase& GetInstance();

    void RegisterDescriptor(const class BenchmarkDescriptor* descriptor);

    void Run();

private:
    Vector<const class BenchmarkDescriptor*> m_descriptors;
};

// TODO: Description.
class BenchmarkDescriptor
{
public:
    BenchmarkDescriptor(const char* name, const size_t* sizes, size_t sizesCount, void(*benchmarkCallback)(size_t));

    template <size_t sizesCount>
    BenchmarkDescriptor(const char* name, const size_t(&sizes)[sizesCount], void(*benchmarkCallback)(size_t));

    BenchmarkDescriptor(const char* name, std::initializer_list<size_t> sizes, void(*benchmarkCallback)(size_t));

    ~BenchmarkDescriptor();

    void Run() const;

    const char* GetName() const;
    const size_t* GetSizes() const;
    size_t GetCount() const;

private:
    const char* m_name;
    size_t* m_sizes;
    size_t m_sizesCount;
    void (*m_benchmarkCallback)(size_t);
};

// TODO: Description.
template <template <typename> typename CallbackStruct, typename T, typename... Ts>
class BenchmarkDescriptorTemplateBase;

template <template <typename> typename CallbackStruct, typename T>
class BenchmarkDescriptorTemplateBase<CallbackStruct, T>
{
public:
    BenchmarkDescriptorTemplateBase(const char* name, const size_t* sizes, size_t sizesCount);
    ~BenchmarkDescriptorTemplateBase();

private:
    char* const m_templateName;
    const BenchmarkDescriptor m_benchmarkDescriptor;
};

template <template <typename> typename CallbackStruct, typename T, typename... Ts>
class BenchmarkDescriptorTemplateBase : public BenchmarkDescriptorTemplateBase<CallbackStruct, Ts...>
{
public:
    BenchmarkDescriptorTemplateBase(const char* name, const size_t* sizes, size_t sizesCount);
    ~BenchmarkDescriptorTemplateBase();

private:
    char* const m_templateName;
    const BenchmarkDescriptor m_benchmarkDescriptor;
};

// TODO: Description.
template <typename... Ts>
class BenchmarkTypes
{
};

// TODO: Description.
template <template <typename> typename CallbackStruct, typename TemplateTypes>
class BenchmarkDescriptorTemplate;

template <template <typename> typename CallbackStruct, typename... Ts>
class BenchmarkDescriptorTemplate<CallbackStruct, BenchmarkTypes<Ts...>> : public BenchmarkDescriptorTemplateBase<CallbackStruct, Ts...>
{
public:
    BenchmarkDescriptorTemplate(const char* name, const size_t* sizes, size_t sizesCount);

    template <size_t sizesCount>
    BenchmarkDescriptorTemplate(const char* name, const size_t(&sizes)[sizesCount]);

    BenchmarkDescriptorTemplate(const char* name, std::initializer_list<size_t> sizes);
};

// TODO: Description.
void* BenchmarkAllocate(size_t size, size_t alignment);

// TODO: Description.
template<class T>
class BenchmarkAllocator
{
public:
    typedef T value_type;

    BenchmarkAllocator() = default;

    template <class U>
    BenchmarkAllocator(const BenchmarkAllocator<U>& other);

    T* Allocate(size_t count);
    void Deallocate(T* address);

    T* allocate(size_t count);
    void deallocate(T* address, size_t count);
};

template<class T, class U>
bool operator==(const BenchmarkAllocator<T>& lhs, const BenchmarkAllocator<U>& rhs);

template<class T, class U>
bool operator!=(const BenchmarkAllocator<T>& lhs, const BenchmarkAllocator<U>& rhs);

} // namespace kw

// TODO: Description.
#define KW_BENCHMARK_TEMPLATE(name, types, sizes)                                                     \
template <typename T>                                                                                 \
struct CallbackStruct##name                                                                           \
{                                                                                                     \
    static void Run(size_t size);                                                                     \
};                                                                                                    \
                                                                                                      \
static const kw::BenchmarkDescriptorTemplate<CallbackStruct##name, types> benchmarkDescriptor##name = \
kw::BenchmarkDescriptorTemplate<CallbackStruct##name, types>(#name, sizes);                           \
                                                                                                      \
template <typename T>                                                                                 \
void CallbackStruct##name<T>::Run(size_t size)

// To use initializer lists inside of macros.
#define KW_LIST(...) { __VA_ARGS__ }

// TODO: Description.
#define KW_DONT_OPTIMIZE(value) kw::DontOptimize(&value)

#include "BenchmarkImpl.h"
