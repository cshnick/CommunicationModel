set(SAMPLE_NAME "CMServer")

message("CMAKE_CURRENT_SOURCE_DIR for ${SAMPLE_NAME}: ${CMAKE_CURRENT_SOURCE_DIR}")
message("EXECUTABLE_OUTPUT_PATH for ${SAMPLE_NAME}: ${EXECUTABLE_OUTPUT_PATH}")

add_custom_target(
    gen_sql_bindings
    COMMAND ${EXECUTABLE_OUTPUT_PATH}/litesql-gen -t c++ --output-dir=${CMAKE_CURRENT_SOURCE_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/src/NCConsole.xml
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(LOCAL_SRCS "")
include_directories(
    ${LITESQL_INCLUDE}
)
aux_source_directory(src LOCAL_SRCS)

add_executable( ${SAMPLE_NAME} ${LOCAL_SRCS} )
set_property(TARGET ${SAMPLE_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries( ${SAMPLE_NAME} PocoNet PocoUtil PocoJSON PocoXML PocoFoundation ${litesql-target})

add_dependencies(${SAMPLE_NAME} gen_sql_bindings)
