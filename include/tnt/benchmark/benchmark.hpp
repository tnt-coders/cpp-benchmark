#pragma once

#include <chrono>

namespace tnt::benchmark
{

/*!
\brief Benchmarks the runtime of a C++ code block

The \c Benchmark function is used to run a segment of code one or more times
and calculate the average runtime across all runs. the \c std::chrono library
is used to ensure accurate time measurements.

<b>Example:</b>
\code{.cpp}
#include <chrono>
#include <iostream>
#include <thread>
#include <tnt/benchmark/benchmark.h>

using namespace std;
using namespace tnt;

void Foo()
{
    this_thread::sleep_for(chrono::milliseconds(42));
}

void FooWithArgs(size_t arg)
{
    this_thread::sleep_for(chrono::milliseconds(arg));
}

int main()
{
    // Benchmark the runtime of "Foo" over 100 iterations
    auto duration1 = benchmark::Benchmark<chrono::milliseconds>(Foo, 100);

    // Benchmark the runtime of "FooWithArgs" over 100 iterations
    // Note that a lambda function is required to pass the args
    auto duration2 = benchmark::Benchmark<chrono::milliseconds>([] {
        FooWithArgs(42);
        }, 100);

    // Benchmark an arbitrary lambda function over 100 iterations
    auto duration3 = benchmark::Benchmark<chrono::milliseconds>([] {
        this_thread::sleep_for(chrono::milliseconds(42));
        }, 100);

    cout << "Benchmark1 duration: " << duration1.count() << endl;
    cout << "Benchmark2 duration: " << duration2.count() << endl;
    cout << "Benchmark3 duration: " << duration3.count() << endl;
}
\endcode

\tparam Duration std::chrono duration type to determine the granularity of the
        time measurement, for example \c std::chrono::milliseconds
\tparam Code An executable type that implements operator()()
\param[in] code A lambda expression, or other executable C++ entity containing
           code to benchmark
\param[in] iterations Number of iterations to perform (more iterations improves
           benchmark accuracy)
\return Duration object containing the average runtime of the code across all
        iterations
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