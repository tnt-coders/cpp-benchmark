#pragma once

#include <chrono>

namespace tnt::benchmark
{

/**
 * @brief Calculates the runtime of the provided code segment
 *
 * The *Benchmark* function is used to run a segment of code one or more times
 * and calculate the average runtime across all runs. This function uses the
 * *std::chrono* library to ensure accurate time measurements.
 *
 * @tparam Duration - Duration type from std::chrono (for example
 *         std::chrono::milliseconds)
 * @param code - A lambda expression containing the code to benchmark
 * @param iterations - (optional) Number of iterations to run the benchmark
 *        (default = 1)
 *        
 */
template <typename Duration, typename Code>
Duration Benchmark(const Code& code, const size_t iterations = 1)
{
    using namespace std::chrono;

    auto i = iterations;
    const auto start = high_resolution_clock::now();
    while(i--) code();
    const auto stop = high_resolution_clock::now();

    return duration_cast<Duration>(stop - start) / iterations;
}

}