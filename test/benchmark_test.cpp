#include <chrono>
#include <gtest/gtest.h>
#include <thread>
#include <tnt/benchmark/benchmark.h>

using namespace std;
using namespace tnt;

void Function()
{
    this_thread::sleep_for(chrono::milliseconds(42));
}

void FunctionWithParam(size_t duration)
{
    this_thread::sleep_for(chrono::milliseconds(duration));
}

int FunctionWithReturn()
{
    this_thread::sleep_for(chrono::milliseconds(42));
    return 42;
}

int FunctionWithParamAndReturn(size_t duration)
{
    this_thread::sleep_for(chrono::milliseconds(duration));
    return 42;
}

TEST(BenchmarkTest, TestLambda)
{
    auto duration = benchmark::Benchmark<chrono::milliseconds>([] {
        this_thread::sleep_for(chrono::milliseconds(42));
        });

    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
}

TEST(BenchmarkTest, TestFunction)
{
    auto duration = benchmark::Benchmark<chrono::milliseconds>([] {
        Function();
        });

    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
}

TEST(BenchmarkTest, TestFunctionWithParam)
{
    auto duration = benchmark::Benchmark<chrono::milliseconds>([] {
        FunctionWithParam(42);
        });

    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
}

TEST(BenchmarkTest, TestFunctionWithReturn)
{
    int returnValue;
    auto duration = benchmark::Benchmark<chrono::milliseconds>([&] {
        returnValue = FunctionWithReturn();
        });

    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
    EXPECT_EQ(returnValue, 42);
}

TEST(BenchmarkTest, TestFunctionWithParamAndReturn)
{
    int returnValue;
    auto duration = benchmark::Benchmark<chrono::milliseconds>([&] {
        returnValue = FunctionWithParamAndReturn(42);
        });

    EXPECT_TRUE(duration.count() >= 41 && duration.count() <= 43);
    EXPECT_EQ(returnValue, 42);
}