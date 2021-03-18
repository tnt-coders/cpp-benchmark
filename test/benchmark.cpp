#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <thread>
#include <tnt/benchmark/benchmark.hpp>

using namespace tnt;

void foo();
void foo_with_args(size_t duration);

// Benchmark a void function with no arguments
TEST_CASE("benchmark", "[benchmark]")
{
    SECTION("function")
    {
        auto duration = benchmark::benchmark<std::chrono::milliseconds>(foo);
        CHECK(duration.count() >= 41);
        CHECK(duration.count() <= 43);
    }

    SECTION("function with arguments")
    {
        auto duration = benchmark::benchmark<std::chrono::milliseconds>([] {
            foo_with_args(42);
        });

        CHECK(duration.count() >= 41);
        CHECK(duration.count() <= 43);
    }

    SECTION("lambda expression")
    {
        auto duration = benchmark::benchmark<std::chrono::milliseconds>([] {
            std::this_thread::sleep_for(std::chrono::milliseconds(42));
        });

        CHECK(duration.count() >= 41);
        CHECK(duration.count() <= 43);
    }
}

void foo()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(42));
}

void foo_with_args(size_t duration)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}
