cmake_minimum_required(VERSION 3.10)
project("server")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${PROJECT_NAME}
  "main.cpp"
  "tcp_server.cpp"
  "tcp_connection.cpp"
  "udp_server.cpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::boost)
