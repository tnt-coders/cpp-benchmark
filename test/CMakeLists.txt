include(GoogleTest)

add_executable(benchmark_test
    main.cpp
    benchmark_test.cpp
)

target_link_libraries(benchmark_test
    TNT::benchmark
    CONAN_PKG::gtest
)

gtest_discover_tests(benchmark_test)