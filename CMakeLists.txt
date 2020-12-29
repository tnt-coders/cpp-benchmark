cmake_minimum_required(VERSION 3.11.4)

# Define the project
project(cpp-benchmark LANGUAGES CXX)

# Get CMake modules from Git
include(FetchContent)
FetchContent_Declare(cmake-modules
  GIT_REPOSITORY https://github.com/tnt-coders/cmake-modules.git
  GIT_TAG main
)
FetchContent_MakeAvailable(cmake-modules)

# Include the required modules
include(tnt/project/Project)

# Initialize the project
tnt_project_New(${PROJECT_NAME}
  NAMESPACE tnt
  CONANFILE conanfile.py
)

# Install dependencies
tnt_project_ConanInstall(${PROJECT_NAME})

# Enable testing for the project
# Note: must be in top level CMakeLists.txt
enable_testing()

add_subdirectory(src)
add_subdirectory(test)

# install project targets
tnt_project_Install(${PROJECT_NAME})