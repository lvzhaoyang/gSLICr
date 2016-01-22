cmake_minimum_required(VERSION 2.8)
project(gSLICr)
  
IF(MSVC_IDE)
  set(OpenCV_STATIC OFF)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DUSING_CMAKE=1)
ELSE(MSVC_IDE)
  set(CFLAGS_WARN "-Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing")
  set(CMAKE_CXX_FLAGS "-fPIC -O3 -march=native ${CFLAGS_WARN} ${CMAKE_CXX_FLAGS}")
ENDIF(MSVC_IDE)

if(APPLE)
  set(CUDA_HOST_COMPILER /usr/bin/clang)
endif(APPLE)

find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(ORUtils)

set(GSLICR_SRC
gSLICr_Lib/gSLICr_defines.h
gSLICr_Lib/gSLICr.h
)

set(GSLICR_ENGINE
gSLICr_Lib/engines/gSLICr_core_engine.h
gSLICr_Lib/engines/gSLICr_seg_engine.h
gSLICr_Lib/engines/gSLICr_seg_engine_GPU.h
gSLICr_Lib/engines/gSLICr_seg_engine_shared.h
gSLICr_Lib/engines/gSLICr_core_engine.cpp
gSLICr_Lib/engines/gSLICr_seg_engine.cpp
gSLICr_Lib/engines/gSLICr_seg_engine_GPU.cu
)

set(GSLICR_OBJECT
gSLICr_Lib/objects/gSLICr_settings.h
gSLICr_Lib/objects/gSLICr_spixel_info.h
)


list(APPEND "-std=c++11 -ftree-vectorize")
SOURCE_GROUP(engines FILES ${GSLICR_LIB})

cuda_add_library(gSLICr_lib
                        ${GSLICR_SRC} ${GSLICR_ENGINE} ${GSLICR_OBJECT}
			NVTimer.h
			OPTIONS -gencode arch=compute_30,code=compute_30)
target_link_libraries(gSLICr_lib ${CUDA_LIBRARY})

add_executable(demo demo.cpp)
target_link_libraries(demo gSLICr_lib ${OpenCV_LIBS})

install(FILES ${GSLICR_SRC} DESTINATION include/gSLICr_lib)
install(FILES ${GSLICR_ENGINE} DESTINATION include/gSLICr_lib/engines)
install(FILES ${GSLICR_OBJECT} DESTINATION include/gSLICr_lib/objects)

install(TARGETS gSLICr_lib DESTINATION lib)

# add examples here
file(GLOB exes "exes/*.cpp")
foreach(exe IN ITEMS ${exes})
  get_filename_component(script_name ${exe} NAME_WE)

  # Add executable
  add_executable(${script_name} ${exe})
  target_link_libraries(${script_name}
    gSLICr_lib
    ${OpenCV_LIBS})
endforeach()
