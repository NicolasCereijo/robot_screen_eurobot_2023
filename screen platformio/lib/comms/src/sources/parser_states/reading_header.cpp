#include "../../headers/parser.hpp"
#include "../../headers/messages.hpp"

using namespace uahruart::parser;


ParserState Protocol::s_reading_header() {
    messages::Header header;
    m_buffer = m_buffer >> header >> primitives::SEPARATOR;

    LOG("Read header:", header.type.to_underlying());

    // Check header constraints
    if (header.type.to_underlying() > static_cast<int>(IDs::SIZE)) {
        // Invalid message
        m_on_write_callback("0", 1);
        return std::bind(&Protocol::s_idle, this);
    }

    m_read_header = header;

    return s_reading_body(); 
}
