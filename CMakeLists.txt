cmake_minimum_required(VERSION 3.15)
project(L_Bike)

set(CMAKE_CXX_STANDARD 14)

set(as_subproject eCAL)

set(possible_subprojects
        tinyxml2)


# For each dependency, check if option to build was set or not
# if so append to `as_subproject` list
foreach (dep IN LISTS possible_subprojects)
    string(TOUPPER ${dep} dep_upper)
    if (ECAL_THIRDPARTY_BUILD_${dep_upper})
        list(APPEND as_subproject ${dep})
    endif ()
endforeach()

macro(find_package)
    if(NOT "${ARGV0}" IN_LIST as_subproject)
        _find_package(${ARGV})
    endif()
endmacro()

# if a package does need to be build, include the cmake file with build instructions
foreach (dep IN LISTS possible_subprojects)
    string(TOUPPER ${dep} dep_upper)
    string(TOLOWER ${dep} dep_lower)
    include(thirdparty/build-${dep_lower}.cmake)
endforeach ()

file(TO_CMAKE_PATH "${CMAKE_MODULE_PATH}" CMAKE_MODULE_PATH)
message(STATUS "Module Path: ${CMAKE_MODULE_PATH}")

set(CORE_INCLUDE src/core)


include_directories(include)
include_directories(${CORE_INCLUDE})
set(CORE_INCLUDE_SRC)

include_directories()
link_directories(lib)



find_library(GLOG glog)

add_executable(L_Bike main.cpp src/third/ThirdConfig.cpp src/third/ThirdConfig.h)
target_link_libraries(L_Bike ${GLOG})