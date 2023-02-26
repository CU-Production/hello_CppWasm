cmake_minimum_required(VERSION 3.24)
project(testwasm3)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(3rdparty/wasm3)

add_subdirectory(3rdparty/wasm3/platforms/cpp/wasm3_cpp)

add_executable(testwasm3 main.cpp)
target_link_libraries(testwasm3 PRIVATE m3 wasm3_cpp)
