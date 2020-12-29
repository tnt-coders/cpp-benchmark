#pragma once

#include <chrono>

namespace tnt::benchmark
{

/*!
\brief Benchmarks the runtime of a C++ code block

The \c Benchmark function is used to run a segment of code one or more times and calculate the
average runtime across all runs. the \c std::chrono library is used to ensure accurate time
measurements.

<b>Example:</b>
\code{.cpp}
#include <chrono>
#include <iostream>
#include <thread>
#include <tnt/benchmark/benchmark.hpp>

using namespace std;
using namespace tnt;

void foo()
{
    this_thread::sleep_for(chrono::milliseconds(42));
}

void foo_with_args(size_t arg)
{
    this_thread::sleep_for(chrono::milliseconds(arg));
}

int main()
{
    // Benchmark the runtime of "foo" over 100 iterations
    auto duration1 = benchmark::benchmark<chrono::milliseconds>(foo, 100);

    // Benchmark the runtime of "FooWithArgs" over 100 iterations
    // Note that a lambda function is required to pass the args
    auto duration2 = benchmark::benchmark<chrono::milliseconds>([] {
        foo_with_args(42);
        }, 100);

    // Benchmark an arbitrary lambda function over 100 iterations
    auto duration3 = benchmark::benchmark<chrono::milliseconds>([] {
        this_thread::sleep_for(chrono::milliseconds(42));
        }, 100);

    cout << "Benchmark1 duration: " << duration1.count() << endl;
    cout << "Benchmark2 duration: " << duration2.count() << endl;
    cout << "Benchmark3 duration: " << duration3.count() << endl;
}
\endcode

\param[in] code A lambda expression, or other executable C++ entity containing code to benchmark
\param[in] iterations Number of iterations to perform (more iterations improves benchmark accuracy)
\return Duration object containing the average runtime of the code across all iterations
*/
template <typename Duration, typename Code>
Duration benchmark(const Code& code, const size_t iterations = 1)
{
    const auto start = std::chrono::high_resolution_clock::now();

    auto i = iterations;
    while (i--)
    {
        code();
    }

    const auto stop = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<Duration>(stop - start) / iterations;
}

}  // namespace tnt::benchmark
