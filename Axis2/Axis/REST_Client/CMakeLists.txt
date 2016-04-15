cmake_minimum_required (VERSION 2.8.11)
project(REST_Client)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
  ${AXIS2C_HOME}/include/axis2-1.6.0
)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -m32")

set(SOURCE_FILES
  REST_Client.c
  rest_client_util.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

link_directories(${AXIS2C_HOME}/lib)

find_library(AXUTIL_LIB axutil "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_AXIOM_LIB axis2_axiom "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_PARSER_LIB axis2_parser "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_ENGINE_LIB axis2_engine "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_SENDER_LIB axis2_http_sender "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)
find_library(AXIS2_RECEIVER_LIB axis2_http_receiver "${AXIS2C_HOME}/lib" NO_DEFAULT_PATH)

message("LIBRARY_PATH " $ENV{LIBRARY_PATH})

target_link_libraries(${PROJECT_NAME} 
	${AXUTIL_LIB}
	${AXIS2_AXIOM_LIB}
	${AXIS2_PARSER_LIB}
	${AXIS2_ENGINE_LIB}
	${AXIS2_SENDER_LIB}
	${AXIS2_RECEIVER_LIB}
	-lpthread
	-ldl)