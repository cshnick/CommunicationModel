cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(MSVC)
    set(PLATFORM_NAME "win32")
else (MSVC)
    set(PLATFORM_NAME "linux")
endif(MSVC)

set (AXIS2C_HOME ${CMAKE_CURRENT_SOURCE_DIR}/axis2c-bin-1.6.0-${PLATFORM_NAME})
set(SERVICE_DIRECTORY ${AXIS2C_HOME}/services)

message(AXIS2C_HOME: ${AXIS2C_HOME})
    
add_subdirectory(jansson-2.7/src)
add_subdirectory(Axis)

link_directories(
    ${AXIS2C_HOME}/lib
)

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
SET(CMAKE_INSTALL_RPATH "${AXIS2C_HOME}/lib")

add_custom_target(
    run
    COMMAND ./axis2_http_server &
    DEPENDS ${AXIS2C_HOME}/bin/axis2_http_server
    WORKING_DIRECTORY ${AXIS2C_HOME}/bin
)

add_custom_target(
    stop
    COMMAND killall -9 axis2_http_server
    DEPENDS ${AXIS2C_HOME}/bin/axis2_http_server
)