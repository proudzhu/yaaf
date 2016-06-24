include_directories(${yaaf_SOURCE_DIR}/include)
link_directories(${yaaf_SOURCE_DIR}/vendor/fftw3)

add_library(test_main test_main.cpp)

add_executable(test_iir2 test_iir2.cpp)
target_link_libraries(test_iir2 yaaf)

add_executable(test_comb_filter test_comb_filter.cpp)
target_link_libraries(test_comb_filter yaaf)

add_executable(test_window test_window.cpp)
target_link_libraries(test_window test_main yaaf)

add_executable(test_common test_common.cpp)
target_link_libraries(test_common test_main yaaf)

add_executable(test_fir test_fir.cpp)
target_link_libraries(test_fir test_main yaaf)

add_executable(test_fir2 test_fir2.cpp)
target_link_libraries(test_fir2 test_main yaaf fftw3 m)

add_executable(test_fft test_fft.cpp)
target_link_libraries(test_fft test_main yaaf fftw3 m)

add_executable(test_zero_crossing test_zero_crossing.cpp)
target_link_libraries(test_zero_crossing test_main yaaf)

add_executable(test_lpc test_lpc.cpp)
target_link_libraries(test_lpc test_main yaaf fftw3 m)
