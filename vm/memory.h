#pragma once

#include "architecture.h"
#include <array>
#include <stack>


namespace Memory
{
    using Main      = std::array<Arch::Word, Arch::MaxWord>;
    using Stack     = std::stack<Arch::Word>;
    using Registers = std::array<Arch::Word,Arch::NumRegisters>;


}