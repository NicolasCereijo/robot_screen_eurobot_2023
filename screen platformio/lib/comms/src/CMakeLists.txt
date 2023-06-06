set(HEADERS callback_store msg_ids utils serial primitives messages parser)
set(SOURCES callback_store serial primitives messages parser)

add_subdirectory(sources/parser_states)

list(TRANSFORM HEADERS PREPEND headers/)
list(TRANSFORM SOURCES PREPEND sources/)
list(TRANSFORM HEADERS APPEND .hpp)
list(TRANSFORM SOURCES APPEND .cpp)

add_library(protocol ${HEADERS} ${SOURCES})
target_link_libraries(protocol states)

