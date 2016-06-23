cmake_minimum_required(VERSION 3.1.0)

project(yaaf CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME test_window COMMAND test_window)
add_test(NAME test_common COMMAND test_common)
add_test(NAME test_fft COMMAND test_fft)
add_test(NAME test_fir COMMAND test_fir)
add_test(NAME test_fir2 COMMAND test_fir2)
add_test(NAME test_zero_crossing COMMAND test_zero_crossing)
