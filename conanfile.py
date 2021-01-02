from conans import ConanFile, CMake, tools

class CppBenchmark(ConanFile):
    author = "TNT Coders <tnt-coders@googlegroups.com>"
    build_requires = "catch2/3.0.0@tnt-coders/stable"
    default_options = {"shared": False}
    description = "A simple way to benchmark C++ routines"
    exports_sources = "CMakeLists.txt", "docs/*", "include/*", "src/*", "test/*"
    generators = "cmake", "cmake_paths"
    license = "GNU Lesser General Public License v3.0"
    name = "cpp-benchmark"
    options = {"shared": [True, False]}
    settings = "os", "compiler", "build_type", "arch"
    topics = ("benchmark")
    url = "https://github.com/tnt-coders/cpp-benchmark"

    def configure(self):
        tools.check_min_cppstd(self, "17")

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake