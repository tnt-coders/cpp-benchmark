#pragma once

#include <chrono>

namespace tnt::benchmark
{

template <typename Duration, typename Code>
Duration Benchmark(const Code& code, const size_t iterations = 1)
{
    using namespace std::chrono;

    size_t i = iterations;
    const auto start = high_resolution_clock::now();
    while(i--) code();
    const auto stop = high_resolution_clock::now();

    return duration_cast<Duration>(stop - start) / iterations;
}

}