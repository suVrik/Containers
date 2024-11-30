#define _CRT_SECURE_NO_WARNINGS

#include "Vector.h"
#include "Benchmark.h"
#include "Macros.h"

#include <vector>

using namespace kw;

//////////////////////////////////////////////////////////////////////////

static constexpr size_t smallStructSize = 32;
static constexpr size_t bigStructSize = 256;

struct PodStruct
{
    int data[smallStructSize];
};

struct BigPodStruct
{
    int data[bigStructSize];
};

struct Struct
{
    Struct();
    Struct(const Struct& other);
    Struct(Struct&& other);
    ~Struct();
    Struct& operator=(const Struct& other);
    Struct& operator=(Struct&& other);

    int* data;
};

KW_NOINLINE Struct::Struct()
    : data(static_cast<int*>(BenchmarkAllocate(sizeof(int) * smallStructSize, alignof(int))))
{
}

KW_NOINLINE Struct::Struct(const Struct& other)
    : data(static_cast<int*>(BenchmarkAllocate(sizeof(int) * smallStructSize, alignof(int))))
{
    Memory::Memcpy(data, other.data, sizeof(int) * smallStructSize);
}

KW_NOINLINE Struct::Struct(Struct&& other)
    : data(other.data)
{
    other.data = nullptr;
}

KW_NOINLINE Struct::~Struct()
{
}

KW_NOINLINE Struct& Struct::operator=(const Struct& other)
{
    if (&other != this)
    {
        if (data == nullptr)
        {
            data = static_cast<int*>(BenchmarkAllocate(sizeof(int) * smallStructSize, alignof(int)));
        }
        Memory::Memcpy(data, other.data, sizeof(int) * smallStructSize);
    }
    return *this;
}

KW_NOINLINE Struct& Struct::operator=(Struct&& other)
{
    if (&other != this)
    {
        data = other.data;
        other.data = nullptr;
    }
    return *this;
}

struct BigStruct
{
    BigStruct();
    BigStruct(const BigStruct& other);
    BigStruct(BigStruct&& other);
    ~BigStruct();
    BigStruct& operator=(const BigStruct& other);
    BigStruct& operator=(BigStruct&& other);

    int* data;
};

KW_NOINLINE BigStruct::BigStruct()
    : data(static_cast<int*>(BenchmarkAllocate(sizeof(int) * bigStructSize, alignof(int))))
{
}

KW_NOINLINE BigStruct::BigStruct(const BigStruct& other)
    : data(static_cast<int*>(BenchmarkAllocate(sizeof(int) * bigStructSize, alignof(int))))
{
    Memory::Memcpy(data, other.data, sizeof(int) * bigStructSize);
}

KW_NOINLINE BigStruct::BigStruct(BigStruct&& other)
    : data(other.data)
{
    other.data = nullptr;
}

KW_NOINLINE BigStruct::~BigStruct()
{
}

KW_NOINLINE BigStruct& BigStruct::operator=(const BigStruct& other)
{
    if (&other != this)
    {
        if (data == nullptr)
        {
            data = static_cast<int*>(BenchmarkAllocate(sizeof(int) * bigStructSize, alignof(int)));
        }
        Memory::Memcpy(data, other.data, sizeof(int) * bigStructSize);
    }
    return *this;
}

KW_NOINLINE BigStruct& BigStruct::operator=(BigStruct&& other)
{
    if (&other != this)
    {
        data = other.data;
        other.data = nullptr;
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////////

static const size_t defaultSizes[] = { 8, 64, 512, 16384 };

using DefaultTypes = kw::BenchmarkTypes<char, short, int, long long, PodStruct, BigPodStruct, Struct, BigStruct>;

KW_BENCHMARK_TEMPLATE(KwVectorConstructorCount, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value(size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorConstructorValue, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value(size, T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorConstructorInitializerList, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value{ T() };
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorConstructorIterator, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> other(size);
    Vector<T, BenchmarkAllocator<T>> value(other.GetBegin(), other.GetEnd());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorConstructorCopy, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> other(size);
    Vector<T, BenchmarkAllocator<T>> value(other);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorConstructorMove, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> other(size);
    Vector<T, BenchmarkAllocator<T>> value(Move(other));
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorAssignmentCopy, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> other(size);
    Vector<T, BenchmarkAllocator<T>> value;
    value = other;
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorAssignmentMove, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value;
    Vector<T, BenchmarkAllocator<T>> other(size);
    value = Move(other);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorAssignmentInitializerList, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value;
    value = { T() };
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorAssignCount, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value;
    value.Assign(size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorAssignCountValue, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value;
    value.Assign(size, T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorReserve, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value;
    value.Reserve(size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorClear, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value(size);
    value.Clear();
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorInsertSingleBegin, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value(size);
    value.Insert(value.GetBegin(), T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorInsertSingleMiddle, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value(size);
    value.Insert(value.GetBegin() + value.GetSize() / 2, T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorInsertSingleEnd, DefaultTypes, defaultSizes)
{
    Vector<T, BenchmarkAllocator<T>> value(size);
    value.Insert(value.GetEnd(), T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorInsertRangeBegin, DefaultTypes, KW_LIST(8, 64, 512))
{
    Vector<T, BenchmarkAllocator<T>> other(size);
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.Insert(value.GetBegin(), other.GetBegin(), other.GetEnd());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorInsertRangeMiddle, DefaultTypes, KW_LIST(8, 64, 512))
{
    Vector<T, BenchmarkAllocator<T>> other(size);
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.Insert(value.GetBegin() + value.GetSize() / 2, other.GetBegin(), other.GetEnd());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorInsertRangeEnd, DefaultTypes, KW_LIST(8, 64, 512))
{
    Vector<T, BenchmarkAllocator<T>> other(size);
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.Insert(value.GetEnd(), other.GetBegin(), other.GetEnd());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorEraseSingleBegin, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.Erase(value.GetBegin());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorEraseSingleMiddle, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.Erase(value.GetBegin() + value.GetSize() / 2);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorEraseSingleEnd, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.Erase(value.GetEnd() - 1);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorEraseRangeBegin, DefaultTypes, KW_LIST(8, 64, 512))
{
    Vector<T, BenchmarkAllocator<T>> value(size + 16);
    value.Erase(value.GetBegin(), value.GetBegin() + size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorEraseRangeMiddle, DefaultTypes, KW_LIST(8, 64, 512))
{
    Vector<T, BenchmarkAllocator<T>> value(size + 16);
    size_t beginIndex = value.GetSize() / 2 / size * size;
    value.Erase(value.GetBegin() + beginIndex, value.GetBegin() + beginIndex + size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorEraseRangeEnd, DefaultTypes, KW_LIST(8, 64, 512))
{
    Vector<T, BenchmarkAllocator<T>> value(size + 16);
    value.Erase(value.GetEnd() - size, value.GetEnd());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorPushBackValue, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.PushBack(T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorPushBackMove, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value(16);
    T other;
    value.PushBack(Move(other));
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorEmplaceBack, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.EmplaceBack();
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(KwVectorPopBack, DefaultTypes, KW_LIST(1))
{
    Vector<T, BenchmarkAllocator<T>> value(16);
    value.PopBack();
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorConstructorCount, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value(size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorConstructorValue, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value(size, T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorConstructorInitializerList, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value{ T() };
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorConstructorIterator, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value(other.begin(), other.end());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorConstructorCopy, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value(other);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorConstructorMove, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value(std::move(other));
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorAssignmentCopy, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value;
    value = other;
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorAssignmentMove, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value;
    value = std::move(other);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorAssignmentInitializerList, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value;
    value = { T() };
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorAssignCount, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value;
    value.assign(size, T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorAssignCountValue, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value;
    value.assign(size, T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorReserve, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value;
    value.reserve(size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorClear, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value(size);
    value.clear();
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorInsertSingleBegin, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value(size);
    value.insert(value.begin(), T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorInsertSingleMiddle, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value(size);
    value.insert(value.begin() + value.size() / 2, T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorInsertSingleEnd, DefaultTypes, defaultSizes)
{
    std::vector<T, BenchmarkAllocator<T>> value(size);
    value.insert(value.end(), T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorInsertRangeBegin, DefaultTypes, KW_LIST(8, 64, 512))
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.insert(value.begin(), other.begin(), other.end());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorInsertRangeMiddle, DefaultTypes, KW_LIST(8, 64, 512))
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.insert(value.begin() + value.size() / 2, other.begin(), other.end());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorInsertRangeEnd, DefaultTypes, KW_LIST(8, 64, 512))
{
    std::vector<T, BenchmarkAllocator<T>> other(size);
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.insert(value.end(), other.begin(), other.end());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorEraseSingleBegin, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.erase(value.begin());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorEraseSingleMiddle, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.erase(value.begin() + value.size() / 2);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorEraseSingleEnd, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.erase(value.end() - 1);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorEraseRangeBegin, DefaultTypes, KW_LIST(8, 64, 512))
{
    std::vector<T, BenchmarkAllocator<T>> value(size + 16);
    value.erase(value.begin(), value.begin() + size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorEraseRangeMiddle, DefaultTypes, KW_LIST(8, 64, 512))
{
    std::vector<T, BenchmarkAllocator<T>> value(size + 16);
    size_t beginIndex = value.size() / 2 / size * size;
    value.erase(value.begin() + beginIndex, value.begin() + beginIndex + size);
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorEraseRangeEnd, DefaultTypes, KW_LIST(8, 64, 512))
{
    std::vector<T, BenchmarkAllocator<T>> value(size + 16);
    value.erase(value.end() - size, value.end());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorPushBackValue, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.push_back(T());
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorPushBackMove, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value(16);
    T other;
    value.push_back(std::move(other));
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorEmplaceBack, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.emplace_back();
    KW_DONT_OPTIMIZE(value);
}

KW_BENCHMARK_TEMPLATE(StdVectorPopBack, DefaultTypes, KW_LIST(1))
{
    std::vector<T, BenchmarkAllocator<T>> value(16);
    value.pop_back();
    KW_DONT_OPTIMIZE(value);
}

int main(int argc, char* argv[])
{
    const char* output = "output.txt";
    if (argc > 1)
    {
        output = argv[1];
    }
    freopen(output, "w", stdout);

    kw::BenchmarkDatabase::GetInstance().Run();

    return 0;
}
