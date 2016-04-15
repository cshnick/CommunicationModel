set(SAMPLE_NAME "RESTServer")

set(LOCAL_SRCS "")
aux_source_directory(src LOCAL_SRCS)

add_executable( ${SAMPLE_NAME} ${LOCAL_SRCS} )
set_property(TARGET ${SAMPLE_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries( ${SAMPLE_NAME} PocoNet PocoUtil PocoJSON PocoXML PocoFoundation )
