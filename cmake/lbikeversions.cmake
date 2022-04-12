execute_process(COMMAND
        git describe --match=None --always --abbrev=40 --dirty
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE LBIKE_SHA1
        OUTPUT_STRIP_TRAILING_WHITESPACE)

string(TIMESTAMP LBIKE_BUILDDATE UTC)
set(LBIKE_VERSION_TWEAK "0")

if(DEFINED ${PROJECT_VERSION_TWEAK})
    set(LBIKE_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/lbike_versions.hpp.in"
        "${CMAKE_BINARY_DIR}/generated/lbike/include/lbike_versions.hpp" @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/generated/lbike/include/lbike_versions.hpp
        DESTINATION include/${PREFIX}
        COMPONENT dev)
