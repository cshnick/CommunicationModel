cmake_minimum_required (VERSION 2.8.11)
project(echo_build)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SERVICE_DIRECTORY}/${PROJECT_NAME})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${AXIS2C_HOME}/include/axis2-1.6.0
    ../../jansson-2.7/src
)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -m32")

set(SOURCE_FILES
  echo.c
  echo_skeleton.c
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

link_directories(${AXIS2C_HOME}/lib)

find_library(AXUTIL_LIB axutil "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_AXIOM_LIB axis2_axiom "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_PARSER_LIB axis2_parser "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_ENGINE_LIB axis2_engine "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_SENDER_LIB axis2_http_sender "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_RECEIVER_LIB axis2_http_receiver "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(JANSSON_LIB jansson "${CMAKE_CURRENT_SOURCE_DIR}" NO_DEFAULT_PATH)

target_link_libraries(${PROJECT_NAME} 
	${AXUTIL_LIB}
	${AXIS2_AXIOM_LIB}
	${AXIS2_PARSER_LIB}
	${AXIS2_ENGINE_LIB}
	${AXIS2_SENDER_LIB}
	${AXIS2_RECEIVER_LIB}
	${JANSSON_LIB}
	-lpthread
	-ldl)