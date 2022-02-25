cmake_minimum_required(VERSION 3.15)
project(L_Bike)

set(CMAKE_CXX_STANDARD 14)

#set(as_subproject eCAL)

set(possible_subprojects
        tinyxml2
        glog
        )


# For each dependency, check if option to build was set or not
# if so append to `as_subproject` list
#foreach (dep IN LISTS possible_subprojects)
#    string(TOUPPER ${dep} dep_upper)
#    if (ECAL_THIRDPARTY_BUILD_${dep_upper})
#        list(APPEND as_subproject ${dep})
#    endif ()
#endforeach()

#macro(find_package)
#    if(NOT "${ARGV0}" IN_LIST as_subproject)
#        _find_package(${ARGV})
#    endif()
#endmacro()

# if a package does need to be build, include the cmake file with build instructions
#foreach (dep IN LISTS possible_subprojects)
#    string(TOUPPER ${dep} dep_upper)
#    string(TOLOWER ${dep} dep_lower)
#    include(thirdparty/build-${dep_lower}.cmake)
#endforeach ()

#file(TO_CMAKE_PATH "${CMAKE_MODULE_PATH}" CMAKE_MODULE_PATH)
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
##
#message(STATUS "Module Path: ${CMAKE_MODULE_PATH}")


set(CORE_INCLUDE src/core)


set(CORE_INCLUDE_SRC)

#list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
#if("${isSystemDir}" STREQUAL "-1")
#    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#endif()

foreach(dep IN LISTS possible_subprojects)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${dep} ${CMAKE_BINARY_DIR}/dependencies/${dep}/prebuild)
endforeach()



message("The cmake prefix path is ${CMAKE_PREFIX_PATH}")

find_package(tinyxml2 CONFIG REQUIRED)
if(tinyxml2_FOUND)
    message(STATUS "The tinyxml2 version is ${tinyxml2_VERSION}")
endif()

find_package(glog CONFIG REQUIRED)
if(glog_FOUND)
    message(STATUS "The glog version is ${glog_VERSION}")
endif()

add_executable(test_main main.cpp)

target_link_libraries(test_main PRIVATE tinyxml2::tinyxml2 glog::glog)


file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/log")
message(STATUS "The CMAKE_BINARY_DIR path is ${CMAKE_BINARY_DIR}")

message("")
message("thirdparty is as following:")
message("   tinyxml2.....................: ${tinyxml2_VERSION}")
message("   glog.........................: ${glog_VERSION}")
message("")

message("")
message("Build Properties")
message("   project name.................: ${CMAKE_PROJECT_NAME}")
message("   c compiler...................: ${CMAKE_C_COMPILER}")
message("   c++ compiler.................: ${CMAKE_CXX_COMPILER}")
message("   cmake version................: ${CMAKE_VERSION}")
message("")