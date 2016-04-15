cmake_minimum_required (VERSION 2.8.11)
project(jansson)

add_definitions( -DHAVE_STDINT_H)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -m32")

set(SOURCE_FILES
  dump.c 
  error.c 
  hashtable.c 
  hashtable_seed.c 
  load.c 
  memory.c 
  pack_unpack.c 
  strbuffer.c 
  strconv.c 
  utf.c 
  value.c
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} )