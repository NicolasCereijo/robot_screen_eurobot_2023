#include "../headers/messages.hpp"

using namespace uahruart::messages;

#include <iostream>

uahruart::serial::SerialBuffer Header::serialize(serial::SerialBuffer &buffer) const {
    return buffer << type;
}

uahruart::serial::SerialBuffer Header::deserialize(const serial::SerialBuffer &buffer) {
    return buffer >> type;
}

uahruart::serial::SerialBuffer Test::serialize(serial::SerialBuffer &buffer) const {
    return buffer << number;
}

uahruart::serial::SerialBuffer Test::deserialize(const serial::SerialBuffer &buffer) {
    return buffer >> number;
}

uahruart::serial::SerialBuffer RPCCall::serialize(serial::SerialBuffer &buffer) const {
    return buffer << function_hash << primitives::SEPARATOR << call_uuid << primitives::SEPARATOR << arg;
}

uahruart::serial::SerialBuffer RPCCall::deserialize(const serial::SerialBuffer &buffer) {
    return buffer >> function_hash >> primitives::SEPARATOR >> call_uuid >> primitives::SEPARATOR >> arg;
}

uahruart::serial::SerialBuffer RPCResponse::serialize(serial::SerialBuffer &buffer) const {
    return buffer << call_uuid << primitives::SEPARATOR << ret;
}

uahruart::serial::SerialBuffer RPCResponse::deserialize(const serial::SerialBuffer &buffer) {
    return buffer >> call_uuid >> primitives::SEPARATOR >> ret;
}

