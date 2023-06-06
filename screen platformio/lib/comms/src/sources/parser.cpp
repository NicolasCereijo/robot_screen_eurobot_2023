#include "../headers/parser.hpp"
#include "../headers/messages.hpp"

using namespace uahruart::parser;

ParserState& ParserState::operator=(ParserState &&other) {
    m_func = std::move(other.m_func);
    return *this;
}

ParserState ParserState::operator()() {
    return m_func();
};


Protocol::Protocol()
    : m_current_state(std::bind(&Protocol::s_idle, this)) {
    
    // Add callbacks for RPCCall and RPCResponse
    m_store.on(IDs::RPC_CALL, functor<void(const messages::RPCCall&)>{[&](auto& msg) {
        LOG("Call received: ", msg.arg.to_underlying());
        if (m_registered_methods.count(msg.function_hash.to_underlying()) != 0)
            m_registered_methods.at(msg.function_hash.to_underlying())(msg.arg.to_underlying());
        else {
            LOG("Function with hash:", msg.function_hash.to_underlying(), "not found");
        }
    }});

    m_store.on(IDs::RPC_RESPONSE, functor<void(const messages::RPCResponse&)>{[&](auto& msg) {
        LOG("Response received");
    }});
}

void Protocol::register_method(const char* device, const char* method, functor<void(int32_t)>&& callback) {
    utils::hash_t function_hash = utils::hash_string(device) ^ utils::hash_string(method);
        m_registered_methods.insert({function_hash, std::move(callback)});
}

void Protocol::receive(string& received) {
    // Update current state
    m_buffer = serial::SerialBuffer(received.length(), received.data());
    m_current_state = m_current_state();
}

bool Protocol::send(const uahruart::serial::Serializable& serializable) {
    // Data can only be sent if it SENDING_DATA is false
    if (m_flags & SENDING_DATA)
        return false;

    m_buffer = serial::SerialBuffer(BUFFER_SIZE, m_internal_buffer.data());

    messages::Header tmp_header;
    tmp_header.type = static_cast<size_t>(serializable.type_id());

    m_buffer = m_buffer << tmp_header << primitives::SEPARATOR << serializable << '\0';

    m_on_write_callback(m_internal_buffer.data(), m_buffer.ammount_rw());
    m_sent_size = m_buffer.ammount_rw();

    m_flags |= SENDING_DATA;
    m_current_state = m_current_state();

    return true;
}

bool Protocol::call(const char *device, const char *method) {
    messages::RPCCall tmp_call;

    tmp_call.function_hash = utils::hash_string(device) ^ utils::hash_string(method);
    m_call_uuid_seed = utils::hash_uint32(m_call_uuid_seed);
    tmp_call.call_uuid = m_call_uuid_seed;
    tmp_call.arg = 14;

    send(tmp_call);

    return true;
}

void Protocol::on_write(functor<void (const char *, size_t)> &&callback) {
    m_on_write_callback = std::move(callback);
}
