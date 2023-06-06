set(SOURCES reading_header reading_body idle waiting_ack)

list(TRANSFORM SOURCES APPEND .cpp)

add_library(states ${SOURCES} ../../headers/parser.hpp)
# target_link_libraries(states protocol)
