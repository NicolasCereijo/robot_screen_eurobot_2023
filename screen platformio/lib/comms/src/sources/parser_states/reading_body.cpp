#include "../../headers/parser.hpp"

using namespace uahruart::parser;

ParserState Protocol::s_reading_body() {
    // Deserialize depending on type_id
    m_store.invoke(m_read_header.type.to_underlying(), m_buffer);
    m_on_write_callback("1", 1); // Send ACK

    return std::bind(&Protocol::s_idle, this);
}
