include_directories(${yaaf_SOURCE_DIR}/include
                    ${yaaf_SOURCE_DIR}/vendor/fftw3)

add_library(yaaf
			common.cpp
			iir2.cpp
			comb_filter.cpp
			vibrato.cpp
			fir_common.cpp
			fir2.cpp
			fft.cpp
			window.cpp
			zero_crossing.cpp
			lpc.cpp
		   )