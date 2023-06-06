#ifndef SERIAL_HPP
#define SERIAL_HPP

#include "msg_ids.hpp"
#include <cstddef>

namespace uahruart::serial {
    class Serializable;

    class SerialBuffer {
        public:
            SerialBuffer(const size_t size, char* buffer);
            SerialBuffer(const size_t size, char* buffer, const size_t start);
            SerialBuffer();

            char& operator[](const size_t index);
            char operator[](const size_t index) const;
            SerialBuffer operator+(const size_t ammount) const;
            SerialBuffer& operator+=(const size_t ammount);

            size_t size() const {return m_SIZE;}
            size_t ammount_rw() const {return m_ammount_rw;}

            operator char*() const;
        private:
            size_t m_SIZE;
            char* m_buffer;
            size_t m_buffer_start;
            mutable size_t m_ammount_rw;

            friend serial::SerialBuffer operator<<(SerialBuffer buffer, const Serializable& serializable);
            friend serial::SerialBuffer operator>>(const SerialBuffer buffer, Serializable& serializable);
            friend serial::SerialBuffer operator<<(SerialBuffer buffer, const char msg);
            friend serial::SerialBuffer operator>>(const SerialBuffer buffer, char& msg);
    };

    class Serializable {
        public: 
            virtual SerialBuffer serialize(SerialBuffer& buffer) const = 0;
            virtual SerialBuffer deserialize(const SerialBuffer& buffer) = 0;
            virtual const IDs type_id() const = 0;
    };

    serial::SerialBuffer operator<<(SerialBuffer buffer, const Serializable& serializable);
    serial::SerialBuffer operator>>(const SerialBuffer buffer, Serializable& serializable);
    serial::SerialBuffer operator<<(SerialBuffer buffer, const char msg);
    serial::SerialBuffer operator>>(const SerialBuffer buffer, char& msg);
}

#endif // SERIAL_HPP
