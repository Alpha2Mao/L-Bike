cmake_minimum_required(VERSION 3.16)
project(tinyxml2-build)


include(ProcessorCount)
ProcessorCount(N)

if (NOT N EQUAL 0)
    if(((${CMAKE_VERSION} VERSION_GREATER "3.12.0") OR ${CMAKE_VERSION} VERSION_EQUAL "3.12.0"))
        set(CMAKE_BUILD_FLAGS -j ${N})
        elseif(LINUX OR QNX)
        set(CMAKE_BUILD_FLAGS -- j ${N})
    endif()
endif()

# set download config, source and build paths
set(DOWNLOAD_CONFIG_DIR ${CMAKE_BINARY_DIR}/dependencies/tinyxml2/download)
set(SOURCE_DIR  ${CMAKE_BINARY_DIR}/dependencies/tinyxml2/src)
set(BUILD_DIR  ${CMAKE_BINARY_DIR}/dependencies/tinyxml2/build)
set(INSTALL_DIR ${CMAKE_BINARY_DIR}/dependencies/install)

# Download and unpack tinyxml2 at configure time
configure_file(tinyxml2.cmake.in ${DOWNLOAD_CONFIG_DIR}/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} ${ENABLE_STATIC_DEBUG} -G "${CMAKE_GENERATOR}" "${COMPILER_FLAGS}"
        "${DOWNLOAD_CONFIG_DIR}"
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${DOWNLOAD_CONFIG_DIR})

if(result)
    message(FETAL_ERROR "CMake step [configure download] for tinyxml2 failed: ${result}")
endif()

#Build
file(MAKE_DIRECTORY "${BUILD_DIR}")

#Parse additional cmake flags
set(ADDITIONAL_CMAKE_FLAGS "")
foreach(flag IN LISTS ARGN)
    list(APPEND ADDITIONAL_CMAKE_FLAGS ${flag})
endforeach()

string(REPLACE ";" " " ADDITIONAL_CMAKE_FLAGS "${ADDITIONAL_CMAKE_FLAGS}")
execute_process(COMMAND ${CMAKE_COMMAND} --build . ${CMAKE_BUILD_FLAGS}
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${DOWNLOAD_CONFIG_DIR})

if(result)
    message(FATAL_ERROR "CMake Step [download] for ${name} failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} ${ENABLE_STATIC_DEBUG}  -G "${CMAKE_GENERATOR}"
        "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}" "{EXTRA_CMAKE_ARGS}" "${SOURCE_DIR}"
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${BUILD_DIR})

if(result)
    message(FATAL_ERROR "Build step [configure] for ${name} failed: ${result}")
endif()


execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install ${CMAKE_BUILD_FLAGS}
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${BUILD_DIR})
if(result)
    message(FATAL_ERROR "Build step [build and install] for tinyxml2 failed: ${result}")
endif()

install(DIRECTORY ${SOURCE_DIR}/resources DESTINATION ${BUILD_DIR})
list(APPEND CMAKE_PREFIX_PATH ${INSTALL_DIR})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} CACHE INTERNAL "" FORCE)

