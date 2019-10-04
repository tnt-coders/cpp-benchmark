add_library(benchmark INTERFACE)

add_library(TNT::benchmark
  ALIAS benchmark
)

target_compile_features(benchmark
  INTERFACE cxx_std_17
)

target_include_directories(benchmark
  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
)
