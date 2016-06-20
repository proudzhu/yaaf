include_directories(${yaaf_SOURCE_DIR}/include)

add_library(test_main test_main.cpp)

add_executable(test_iir2 test_iir2.cpp)
target_link_libraries(test_iir2 yaaf)

add_executable(test_combFilter test_combFilter.cpp)
target_link_libraries(test_combFilter yaaf)

add_executable(test_window test_window.cpp)
target_link_libraries(test_window test_main yaaf)

add_executable(test_common test_common.cpp)
target_link_libraries(test_common test_main yaaf)

add_executable(test_fir test_fir.cpp)
target_link_libraries(test_fir test_main yaaf)