#include "../headers/callback_store.hpp"
#include "../headers/primitives.hpp"
#include "../headers/messages.hpp"

using namespace uahruart;

CallbackStore::CallbackStore() {
    // Fill with default callbacks
    for (size_t i = 0; i < m_callbacks.size(); i++)
        m_callbacks[i] = [](){};
}

// template<typename... Types>
// struct TypeArray {

// };

template<typename T>
struct Invoker {
    static void invoke(functor<void()>& untyped, serial::SerialBuffer& buffer) {
        T serializable;
        buffer = buffer >> serializable;
        reinterpret_cast<functor<void(const T&)>*>(&untyped)->operator()(serializable);
    }
};

#define T(type) Invoker<type>::invoke
CallbackStore::InvokersArr_t CallbackStore::m_invokers {
    T(primitives::Int),
    T(primitives::String),
    T(primitives::Bool),
    
    T(messages::Test),
    T(messages::RPCCall),
    T(messages::RPCResponse)
};
#undef T
