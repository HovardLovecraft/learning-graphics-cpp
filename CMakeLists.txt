cmake_minimum_required(VERSION 3.16)
project(learning-graphics-cpp)

set(CMAKE_CXX_STANDARD 17)

# Production executable
add_executable(raytracer
    MyVec3/main.cpp
)
target_include_directories(raytracer PRIVATE MyVec3)

# Test executable
add_executable(raytracer_tests
    tests/test_main.cpp
    tests/test_vec3.cpp
    tests/test_sphere.cpp
    tests/test_camera.cpp
)
target_include_directories(raytracer_tests PRIVATE MyVec3)
