#include "../../headers/parser.hpp"
#include "../../headers/primitives.hpp"
#include <functional>

using namespace uahruart::parser;

#include <iostream>

ParserState Protocol::s_waiting_ack() {
    // Read value
    primitives::ACK tmp_ack;
    m_buffer >> tmp_ack;
    std::cout << "ACK: " << tmp_ack.to_underlying() << '\n';

    // Check if ACK is valid
    if (tmp_ack.to_underlying()) {
        return std::bind(&Protocol::s_idle, this);
    }

    // Resend information, ACK was invalid
    m_on_write_callback(m_internal_buffer.data(), m_sent_size);
    return std::bind(&Protocol::s_waiting_ack, this);
}
