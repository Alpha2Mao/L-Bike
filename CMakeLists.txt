cmake_minimum_required(VERSION 3.15)
project(L_Bike VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)

#set(as_subproject eCAL)

set(possible_subprojects
        tinyxml2
        glog
        )

include(GNUInstallDirs)
message(STATUS "INSTALL APP dir is ${CMAKE_INSTALL_BINDIR}")
include(GNUInstallDirs)
set(lbike_install_app_dir           ${CMAKE_INSTALL_BINDIR})
set(lbike_install_archive_dir       ${CMAKE_INSTALL_LIBDIR})
set(lbike_install_archive_dyn_dir   ${CMAKE_INSTALL_LIBDIR})
set(lbike_install_bin_dir           ${CMAKE_INSTALL_BINDIR})
set(lbike_install_cmake_dir         ${CMAKE_INSTALL_LIBDIR}/cmake/lbike)
set(lbike_install_config_dir        ${CMAKE_INSTALL_SYSCONFDIR}/lbike)
set(lbike_install_doc_dir           ${CMAKE_INSTALL_DOCDIR})
set(lbike_install_include_dir       ${CMAKE_INSTALL_INCLUDEDIR})
set(lbike_install_lib_dir           ${CMAKE_INSTALL_LIBDIR})
set(lbike_install_samples_dir       ${CMAKE_INSTALL_BINDIR})
set(lbike_install_samples_src_dir   ${CMAKE_INSTALL_DATADIR}/lbike/samples/)
set(lbike_install_tests_dir         ${CMAKE_INSTALL_BINDIR})

set(lbike_config_dir                ${eCAL_BINARY_DIR}/cmake/)
set(lbike_config                    ${eCAL_config_dir}/LBikeConfig.cmake)
set(lbike_config_version            ${eCAL_config_dir}/LBikeConfigVersion.cmake)


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

set(CMAKE_DEBUG_POSTFIX d)

set(CORE_INCLUDE src/core)


set(CORE_INCLUDE_SRC)

#list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
#if("${isSystemDir}" STREQUAL "-1")
#    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#endif()

foreach (dep IN LISTS possible_subprojects)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${dep} ${CMAKE_BINARY_DIR}/dependencies/${dep}/prebuild)
endforeach ()

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/include)

find_package(tinyxml2 CONFIG REQUIRED)
if (tinyxml2_FOUND)
    message(STATUS "The tinyxml2 >>>>>> Found <<<<< version is ${tinyxml2_VERSION}")
endif ()

find_package(glog CONFIG REQUIRED)
if (glog_FOUND)
    message(STATUS "The glog >>>>>> Found <<<<< version is ${glog_VERSION}")
endif ()

include(cmake/lbikeversions.cmake)

add_executable(super_bike
        main.cpp
        src/src/utils/time.c
        src/src/utils/config.cpp
        src/src/utils/lbike_timer.cpp)

target_include_directories(super_bike
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated/lbike/include>
        $<INSTALL_INTERFACE:include/${PREFIX}>
        )

target_link_libraries(super_bike PRIVATE tinyxml2::tinyxml2 glog::glog)

set_target_properties(super_bike PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})


file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/log")
message(STATUS "The CMAKE_BINARY_DIR path is ${CMAKE_BINARY_DIR}")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

set(CMAKE_INSTALL_LIBDIR "lib")
message(STATUS "The CMAKE_INSTALL_LIBDIR path is ${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
message(STATUS "The CMAKE_INSTALL_CMAKEDIR is ${CMAKE_INSTALL_CMAKEDIR}")

install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
        COMPONENT dev
)

install(TARGETS super_bike
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
        PUBLIC_HEADER DESTINATION include
        )

message(STATUS "The cmake_install_includedir is ${CMAKE_INSTALL_INCLUDEDIR}")

message("")
message("thirdparty is as following:")
message("   tinyxml2.....................: ${tinyxml2_VERSION}")
message("   glog.........................: ${glog_VERSION}")
message("")

message("")
message("Build Properties")
message("   project name.................: ${CMAKE_PROJECT_NAME}")
message("   project version .............: ${PROJECT_VERSION}")
message("   c compiler...................: ${CMAKE_C_COMPILER}")
message("   c++ compiler.................: ${CMAKE_CXX_COMPILER}")
message("   cmake version................: ${CMAKE_VERSION}")
message("")

include(CPack)
