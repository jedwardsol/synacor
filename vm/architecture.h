#pragma once
#include <cstdint>
#include <limits>
#include <variant>
#include <stdexcept>
#include <string>

#include "thrower.h"

namespace Arch
{
    using Register = int8_t;
    using Word     = uint16_t;

    constexpr Word MaxWord{32767};
    constexpr Word Modulo {32768};
    constexpr int  NumRegisters {8};


    using Operand = std::variant<std::monostate, Word, Register>;


    Operand decodeOperand(Arch::Word    word)
    {
        if(word <= Arch::MaxWord)
        {
            return word;
        }

        word %= Arch::Modulo;

        if(word < Arch::NumRegisters)
        {
            return static_cast<Arch::Register>(NumRegisters);
        }
        else
        {
            throw_runtime_error("Invalid operand MaxWord+" + std::to_string(word));
        }


    }

}