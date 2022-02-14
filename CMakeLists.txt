cmake_minimum_required(VERSION 3.14)
project(L_Bike)

set(CMAKE_CXX_STANDARD 14)


set(CORE_INCLUDE src/core)


include_directories(include)
include_directories(${CORE_INCLUDE})
set(CORE_INCLUDE_SRC)

include_directories()
link_directories(lib)



find_library(GLOG glog)

add_executable(L_Bike main.cpp src/third/ThirdConfig.cpp src/third/ThirdConfig.h)
target_link_libraries(L_Bike ${GLOG})