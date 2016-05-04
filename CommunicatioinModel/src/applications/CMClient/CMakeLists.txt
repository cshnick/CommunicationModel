set(SAMPLE_NAME "CMClient")

set(LOCAL_SRCS "")
aux_source_directory(src LOCAL_SRCS)

add_executable( ${SAMPLE_NAME} ${LOCAL_SRCS} )
set_property(TARGET ${SAMPLE_NAME} PROPERTY CXX_STANDARD 11)
if (MSVC_IDE)
   target_link_libraries( ${SAMPLE_NAME} PocoNet PocoNetSSLWin PocoUtil PocoJSON PocoXML PocoFoundation )
else (MSVC_IDE)
   target_link_libraries( ${SAMPLE_NAME} PocoNet PocoNetSSL PocoUtil PocoJSON PocoXML PocoFoundation )
endif (MSVC_IDE)

add_custom_target(
    copy_${SAMPLE_NAME}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/any.pem ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/rootcert.pem ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE_NAME}.properties ${EXECUTABLE_OUTPUT_PATH}
    COMMENT "Copying ${SAMPLE_NAME} resources"
)

add_dependencies(${SAMPLE_NAME} gen_sql_bindings copy_${SAMPLE_NAME})
