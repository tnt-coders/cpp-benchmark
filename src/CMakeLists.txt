tnt_project_AddLibrary(${PROJECT_NAME} TARGET benchmark INTERFACE)

target_compile_features(benchmark INTERFACE cxx_std_17)