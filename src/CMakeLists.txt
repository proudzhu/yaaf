include_directories(${yaaf_SOURCE_DIR}/include
                    ${yaaf_SOURCE_DIR}/vendor/fftw3)

add_library(yaaf
			common.cpp
			iir2.cpp
			combFilter.cpp
			vibrato.cpp
			firCommon.cpp
			fir2.cpp
			fft.cpp
			window.cpp
		   )