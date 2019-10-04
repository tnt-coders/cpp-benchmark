#include <chrono>
#include <gtest/gtest.h>
#include <thread>
#include <tnt/benchmark/benchmark.h>

TEST(BenchmarkTest, TestLambda)
{
    auto duration = tnt::benchmark::Benchmark<std::chrono::milliseconds>([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(42));
        });

    EXPECT_EQ(duration.count(), 42);
}