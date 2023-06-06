#include "../../headers/parser.hpp"
#include <functional>

using namespace uahruart::parser;

ParserState Protocol::s_idle() {
    // Check if data was sent
    if (m_flags & SENDING_DATA) {
        return std::bind(&Protocol::s_waiting_ack, this);
    } else {
        return s_reading_header();
    }

    return std::bind(&Protocol::s_idle, this);
}
