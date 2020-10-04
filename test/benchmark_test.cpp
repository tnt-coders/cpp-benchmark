#include <chrono>
#include <gtest/gtest.h>
#include <thread>
#include <tnt/benchmark/benchmark.h>

using namespace std;
using namespace tnt;

void Foo()
{
    this_thread::sleep_for(chrono::milliseconds(42));
}

void FooWithArgs(size_t duration)
{
    this_thread::sleep_for(chrono::milliseconds(duration));
}

// Benchmark a void function with no arguments
TEST(Benchmark, Function)
{
    auto duration = benchmark::Benchmark<chrono::milliseconds>(Foo);
    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
}

// Benchmark a void function with input arguments
TEST(Benchmark, FunctionWithArgs)
{
    auto duration = benchmark::Benchmark<chrono::milliseconds>([] {
        FooWithArgs(42);
        });

    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
}

// Benchmark an arbitrary lambda function
TEST(Benchmark, Lambda)
{
    auto duration = benchmark::Benchmark<chrono::milliseconds>([] {
        this_thread::sleep_for(chrono::milliseconds(42));
        });

    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
}