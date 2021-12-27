#pragma once
#include <cstdint>
#include <limits>
#include <variant>
#include <stdexcept>
#include <string>

#include "thrower.h"

namespace Synacor::Arch
{
    using Register = int8_t;
    using Word     = uint16_t;

    constexpr Word MaxWord{32767};
    constexpr Word Modulo {32768};
    constexpr int  NumRegisters {8};




}