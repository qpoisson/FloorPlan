cmake_minimum_required(VERSION 2.8)
project(FloorPlan)


find_package(PCL 1.7 REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp XyzToPCD.h ReadPCD.cpp ReadPCD.h XyzToPCD.cpp Ransac.cpp Ransac.h View/View.h)
add_executable(FloorPlan ${SOURCE_FILES})
target_link_libraries(FloorPlan ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})
