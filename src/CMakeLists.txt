include_directories(${yaaf_SOURCE_DIR}/include)

add_library(yaaf
			common.cpp
			iir2.cpp
			combFilter.cpp
			vibrato.cpp
			firCommon.cpp
			fir2.cpp
		   )
