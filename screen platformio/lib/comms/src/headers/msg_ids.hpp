#ifndef MSG_IDS_HPP
#define MSG_IDS_HPP

#include <cstdint>

namespace uahruart {
    enum class IDs : uint16_t {
        // Primitives
        PRIMITIVE_INT,
        PRIMITIVE_STR,
        PRIMITIVE_BOOL,
        // Messages
        TEST,
        RPC_CALL,
        RPC_RESPONSE,

        // Do not modify
        SIZE,
        UNDEF
    };
}

#endif // MSG_IDS_HPP
