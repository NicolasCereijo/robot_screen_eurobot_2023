#ifndef CALLBACK_STORE_HPP
#define CALLBACK_STORE_HPP

#include "msg_ids.hpp"
#include "utils.hpp"
#include "serial.hpp"
#include <array>

namespace uahruart {
    class CallbackStore {
        public:
            CallbackStore();

            template<typename Callback_Arg>
            void on(const IDs id, functor<void(Callback_Arg&)> callback) {
                auto retreived_id = static_cast<uint16_t>(id);
                // Remove type
                m_callbacks[static_cast<size_t>(retreived_id)] = *reinterpret_cast<functor<void()>*>(&callback);
            }
            
            void invoke(const uint16_t id, serial::SerialBuffer& buffer) {
                // Retreive type
                // Check if inside range
                m_invokers[id](m_callbacks[id], buffer);
            }

        private:
            using InvokersArr_t = std::array<void(*)(functor<void()>&, serial::SerialBuffer&), (uint16_t)IDs::SIZE>;
            static InvokersArr_t m_invokers;
            std::array<functor<void()>, (size_t)IDs::SIZE> m_callbacks;
    };
}
#endif // CALLBACK_STORE_HPP
