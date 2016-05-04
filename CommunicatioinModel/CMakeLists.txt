cmake_minimum_required(VERSION 3.1.0) # For CXX_STANDARD declaration

set(CMAKE_C_COMPILER "gcc-5")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-5")
set(CMAKE_CXX_STANDARD 11)

project(CommunicationModel)


SET(LIB_DIR lib)
SET(BIN_DIR bin)
IF (MSVC)
	SET(LIB_DIR ${BIN_DIR})
ENDIF (MSVC)

SET (EXECUTABLE_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/${BIN_DIR}"
)
SET(LIBRARY_OUTPUT_PATH 
	"${PROJECT_BINARY_DIR}/${LIB_DIR}"
)	

SET (INCLUDES_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set (DEFAULT_LIB_TYPE SHARED)
if (MSVC)
  set (DEFAULT_LIB_TYPE STATIC)
endif (MSVC)

set (BUILD_TYPE_NAME Release)
set (CMAKE_DEBUG_POSTFIX "")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set (BUILD_TYPE_NAME Debug)
    if (MSVC)
        set(CMAKE_DEBUG_POSTFIX "d")
    endif (MSVC)
endif (CMAKE_BUILD_TYPE MATCHES Debug)

set(litesql litesql)
set(PocoNet PocoNet)
set(PocoUtil PocoUtil)
set(PocoJSON PocoJSON)
set(PocoXML PocoXML)
set(PocoFoundation PocoFoundation)
if (MSVC_IDE)
    set(PocoNetSSL PocoNetSSLWin)
else (MSVC_IDE)
    set(PocoNetSSL PocoNetSSL)
endif (MSVC_IDE)

set(LITESQL_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/litesql/include
)

add_definitions ( -D_HAS_ITERATOR_DEBUGGING=0
)

SET (TOP_LEVEL ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
