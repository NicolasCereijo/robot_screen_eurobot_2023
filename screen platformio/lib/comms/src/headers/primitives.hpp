#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "msg_ids.hpp"
#include "serial.hpp"
#include "utils.hpp"

#include <cstdint>

namespace uahruart::primitives {
    class Int : public virtual serial::Serializable {
        public:
            using Underlying_t = int32_t;

            Int(const Underlying_t& value);
            Int() = default;
        
            serial::SerialBuffer serialize(serial::SerialBuffer& buffer) const override;
            serial::SerialBuffer deserialize(const serial::SerialBuffer& buffer) override;

            virtual const IDs type_id() const override {return IDs::PRIMITIVE_INT;}
            
            Underlying_t to_underlying() const;
        private:
            int32_t m_value = 0;
    };

    class String : public virtual serial::Serializable {
        public:
            using Underlying_t = string;

            String(const char* str);
            String() = default;

            serial::SerialBuffer serialize(serial::SerialBuffer& buffer) const override;
            serial::SerialBuffer deserialize(const serial::SerialBuffer& buffer) override;

            virtual const IDs type_id() const override {return IDs::PRIMITIVE_STR;}

            Underlying_t to_underlying() const;
        private:
            string m_value = "";
    };

    class Bool: public virtual serial::Serializable {
        public:
            using Underlying_t = bool;

            Bool(const bool val);
            Bool() = default;

            serial::SerialBuffer serialize(serial::SerialBuffer& buffer) const override;
            serial::SerialBuffer deserialize(const serial::SerialBuffer& buffer) override;

            virtual const IDs type_id() const override {return IDs::PRIMITIVE_BOOL;}

            Underlying_t to_underlying() const {return m_value;}

            bool is_valid() const;
        private:
            bool m_value = false;
    };
    using ACK = Bool;
    
    class : public virtual serial::Serializable {
        public:
            serial::SerialBuffer serialize(serial::SerialBuffer& buffer) const override {
                buffer[0] = ':';
                return buffer + 1;
            }
            serial::SerialBuffer deserialize(const serial::SerialBuffer& buffer) override {
                return buffer + 1;
            }

            virtual const IDs type_id() const override {return IDs::UNDEF;}
            
            size_t size() {return 1;}
            bool is_separator(char value) {
                bool ret = false;
                for (auto& val : ":\n\0")
                    ret |= value == val;
                return ret;
            }
    } SEPARATOR;
}

#endif // PRIMITIVES_HPP
