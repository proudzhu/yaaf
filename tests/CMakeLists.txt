include_directories(${yaaf_SOURCE_DIR}/include)

add_executable(test_iir2 test_iir2.cpp)
target_link_libraries(test_iir2 yaaf)
