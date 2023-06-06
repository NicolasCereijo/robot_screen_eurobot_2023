#include "../headers/primitives.hpp"
#include <cstdlib>

using namespace uahruart::primitives;

Int::Int(const Int::Underlying_t& value)
    : m_value(value) {

}

uahruart::serial::SerialBuffer Int::serialize(uahruart::serial::SerialBuffer& buffer) const {
    Underlying_t tmp_value = abs(m_value);

    size_t cnt = 0;
    if (m_value < 0)
        buffer[cnt++] = '-';

    do {
        buffer[cnt++] = (tmp_value % 10) + '0';
        tmp_value /= 10;
    } while(tmp_value);

    auto reverse_buffer = buffer + (m_value < 0);
    size_t numbers = cnt - (m_value < 0);
    for (size_t i = 0; i < (numbers / 2); i++) {
        char swch = reverse_buffer[i];
        reverse_buffer[i] = reverse_buffer[numbers - 1 - i];
        reverse_buffer[numbers - 1 - i] = swch;
    }
    return buffer + cnt;
}

uahruart::serial::SerialBuffer Int::deserialize(const serial::SerialBuffer& buffer) {
    int cnt = 0;
    m_value = 0;
    bool negative = buffer[0] == '-';
    if (negative) cnt++;

    while ((buffer[cnt] != ':') && (cnt < buffer.size())) {
        m_value *= 10;
        m_value += buffer[cnt] - '0';
        cnt++;
    }

    if (negative)
        m_value *= -1;

    return buffer + cnt;
}

Int::Underlying_t Int::to_underlying() const {
    return m_value;
}

String::String(const char* msg)
    : m_value(msg) {

}

uahruart::serial::SerialBuffer String::serialize(serial::SerialBuffer &buffer) const {
    for (size_t i = 0; i < m_value.size(); i++)
        buffer[i] = m_value[i];

    return buffer + m_value.size();
}

uahruart::serial::SerialBuffer String::deserialize(const serial::SerialBuffer &buffer) {
    // Get size
    size_t cnt = 0;
    while (SEPARATOR.is_separator(buffer[cnt++]));

    m_value = Underlying_t(cnt, '\0');
    for (size_t i = 0; i < cnt; i++)
        m_value[i] = buffer[i];

    return buffer + cnt;
}

uahruart::serial::SerialBuffer Bool::serialize(serial::SerialBuffer &buffer) const {
    buffer[0] = m_value ? '1':'0'; 
    return buffer + 1;
}

uahruart::serial::SerialBuffer Bool::deserialize(const serial::SerialBuffer &buffer) {
    m_value = buffer[0] == '1';
    return buffer + 1;
}

Bool::Bool(const bool value)
    : m_value(value) {

}
