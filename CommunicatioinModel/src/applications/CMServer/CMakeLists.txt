set(SAMPLE_NAME "CMServer")

message("CMAKE_CURRENT_SOURCE_DIR for ${SAMPLE_NAME}: ${CMAKE_CURRENT_SOURCE_DIR}")
message("EXECUTABLE_OUTPUT_PATH for ${SAMPLE_NAME}: ${EXECUTABLE_OUTPUT_PATH}")

if (MSVC_IDE)
	add_custom_target(
			gen_sql_bindings
			COMMAND ${EXECUTABLE_OUTPUT_PATH}/Debug/litesql-gen.exe -t c++ --output-dir=${CMAKE_CURRENT_SOURCE_DIR}/src
					${CMAKE_CURRENT_SOURCE_DIR}/src/NCConsole.xml
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
		)
else (MSVC_IDE)
	add_custom_target(
		gen_sql_bindings
		COMMAND ${EXECUTABLE_OUTPUT_PATH}/litesql-gen -t c++ --output-dir=${CMAKE_CURRENT_SOURCE_DIR}/src
				${CMAKE_CURRENT_SOURCE_DIR}/src/NCConsole.xml
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
	)
endif(MSVC_IDE)

set(LOCAL_SRCS "")
include_directories(
    ${LITESQL_INCLUDE}
)
aux_source_directory(src LOCAL_SRCS)

add_executable( ${SAMPLE_NAME} ${LOCAL_SRCS} )
set_property(TARGET ${SAMPLE_NAME} PROPERTY CXX_STANDARD 11)
if (MSVC_IDE)
	target_link_libraries( ${SAMPLE_NAME} PocoNet PocoNetSSLWin PocoUtil PocoJSON PocoXML PocoFoundation ${litesql-target})
else (MSVC_IDE)
	target_link_libraries( ${SAMPLE_NAME} PocoNet PocoNetSSL PocoUtil PocoJSON PocoXML PocoFoundation ${litesql-target})
endif(MSVC_IDE)

add_custom_target(
    copy_${SAMPLE_NAME}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/any.pem ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/rootcert.pem ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE_NAME}.properties ${EXECUTABLE_OUTPUT_PATH}
    COMMENT "Copying ${SAMPLE_NAME} resources"
)

add_dependencies(${SAMPLE_NAME} gen_sql_bindings copy_${SAMPLE_NAME})