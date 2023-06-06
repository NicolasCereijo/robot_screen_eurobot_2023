#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

// Fix macro collision with Arduino.h
#ifdef Arduino_h
    #undef max
    #undef min
#endif

#include "headers/callback_store.hpp"
#include "headers/messages.hpp"
#include "headers/msg_ids.hpp"
#include "headers/primitives.hpp"
#include "headers/serial.hpp"
#include "headers/utils.hpp"
#include "headers/parser.hpp"

#endif // PROTOCOL_HPP
