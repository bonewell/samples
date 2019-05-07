cmake_minimum_required(VERSION 3.2)

project(sslbuf)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${PROJECT_NAME} "main.cpp")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}
    CONAN_PKG::boost
)
