#include "Benchmark.h"
#include "Memory.h"
#include "Macros.h"

#include <chrono>

namespace kw
{

KW_OPTIMIZATION_OFF
void DontOptimize(void* address)
{
    (void)address;
}
KW_OPTIMIZATION_ON

static char s_benchmarkAllocatorStorage[536870912]; // 512 MiB
static char* s_benchmarkAllocatorPointer = s_benchmarkAllocatorStorage;

void* BenchmarkAllocate(size_t size, size_t alignment)
{
    void* result = s_benchmarkAllocatorPointer;
    s_benchmarkAllocatorPointer += size;
    return result;
}

inline void BenchmarkResetAllocator()
{
    s_benchmarkAllocatorPointer = s_benchmarkAllocatorStorage;
}

class BenchmarkTimer
{
public:
    void Start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    void Stop()
    {
        m_end = std::chrono::high_resolution_clock::now();
    }

    double GetDurationMilliseconds() const
    {
        return static_cast<std::chrono::duration<double, std::milli>>(m_end - m_start).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};

BenchmarkDescriptor::BenchmarkDescriptor(const char* name, const size_t* sizes, size_t sizesCount, void(*benchmarkCallback)(size_t))
    : m_name(name)
    , m_sizesCount(sizesCount)
    , m_benchmarkCallback(benchmarkCallback)
{
    m_sizes = static_cast<size_t*>(Memory::Malloc(sizeof(size_t) * sizesCount, alignof(size_t)));
    Memory::Memcpy(m_sizes, sizes, sizeof(size_t) * sizesCount);
    
    BenchmarkDatabase::GetInstance().RegisterDescriptor(this);
}

BenchmarkDescriptor::BenchmarkDescriptor(const char* name, std::initializer_list<size_t> sizes, void(*benchmarkCallback)(size_t))
    : BenchmarkDescriptor(name, sizes.begin(), sizes.size(), benchmarkCallback)
{
}

BenchmarkDescriptor::~BenchmarkDescriptor()
{
    Memory::Free(m_sizes);
}

void BenchmarkDescriptor::Run() const
{
    for (size_t i = 0; i < GetCount(); i++)
    {
        size_t size = GetSizes()[i];

        double duration = 0.0;
        size_t iterations = 0;

        for (size_t j = 8; duration < 150.0; j = (j < 16777216 ? j * 2 : 16777216))
        {
            BenchmarkTimer timer;

            timer.Start();
            for (size_t k = 0; k < j; k++)
            {
                m_benchmarkCallback(size);
                BenchmarkResetAllocator();
            }
            timer.Stop();

            duration += timer.GetDurationMilliseconds();
            iterations += j;
        }

        duration /= iterations;

        printf("%.10f\t%s %zu\n", duration, GetName(), size);
    }
}

BenchmarkDatabase& BenchmarkDatabase::GetInstance()
{
    static BenchmarkDatabase database;
    return database;
}

void BenchmarkDatabase::RegisterDescriptor(const BenchmarkDescriptor* descriptor)
{
    m_descriptors.PushBack(descriptor);
}

void BenchmarkDatabase::Run()
{
    for (const BenchmarkDescriptor* descriptor : m_descriptors)
    {
        descriptor->Run();
    }
}

} // namespace kw
