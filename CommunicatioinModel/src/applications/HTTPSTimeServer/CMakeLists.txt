set(SAMPLE_NAME "HTTPSTimeServer")

set(LOCAL_SRCS "")
aux_source_directory(src LOCAL_SRCS)

add_executable( ${SAMPLE_NAME} ${LOCAL_SRCS} )
target_link_libraries( ${SAMPLE_NAME} PocoNetSSL PocoCrypto PocoUtil PocoNet PocoXML PocoFoundation )

add_custom_target(
    copy_${SAMPLE_NAME}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/any.pem ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/rootcert.pem ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE_NAME}.properties ${EXECUTABLE_OUTPUT_PATH}
    COMMENT "Copying ${SAMPLE_NAME}"
)

add_dependencies(${SAMPLE_NAME} copy_${SAMPLE_NAME})
