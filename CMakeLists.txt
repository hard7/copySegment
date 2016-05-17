cmake_minimum_required(VERSION 3.4)
project(copySegment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic-errors")

find_package(CUDA REQUIRED)
CUDA_COMPILE_PTX(PTX_MODULE_LOCATION detail/kernel.cu OPTIONS --compiler-options -Wall)
set(CUDA_HELPER_LOCATE ${CUDA_TOOLKIT_ROOT_DIR}/samples/common/inc)

add_definitions(-DPTX_MODULE_LOCATION=${PTX_MODULE_LOCATION})


include_directories(${CUDA_INCLUDE_DIRS} ${CUDA_HELPER_LOCATE})
set(SOURCE_FILES main.cpp detail/mySpatialTraits.cpp)

#add_executable(copySegment ${SOURCE_FILES})
add_executable(copySegment ${SOURCE_FILES} ${PTX_MODULE_LOCATION})
target_link_libraries(copySegment cuda)
