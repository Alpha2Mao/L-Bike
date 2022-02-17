find_path(glog_INCLUDE_DIR
        NAMES logging.h
        PATHS
        ${CMAKE_CURRENT_LIST_DIR}/../thirdparty/glog/include
        )

if(glog_INCLUDE_DIR-NOTFOUND)
    message(FATAL_ERROR "Could not find Glog library")
    set(glog_FOUND False)
else()
    set(glog_FOUND True)
    # Add workaround for stupid eprosima_find_package()
    set(ASIO_INCLUDE_DIR ${glog_INCLUDE_DIR})
endif()

if(glog_FOUND)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(glog
            REQUIRED_VARS glog_INCLUDE_DIR
            )

    if(NOT TARGET asio::asio)
        set(glog_INCLUDE_DIRS ${glog_INCLUDE_DIR})

        add_library(asio::asio INTERFACE IMPORTED)
        set_target_properties(asio::asio PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES ${glog_INCLUDE_DIR}
                INTERFACE_COMPILE_DEFINITIONS ASIO_STANDALONE)
        mark_as_advanced(glog_INCLUDE_DIR)
    endif()
endif()