#pragma once
#include <cstdint>
#include <iostream>
#include <format>

#include "architecture.h"
#include "memory.h"
#include "cpu.h"


namespace Synacor
{

class VM
{
public:
    enum class Source
    {
        text,       // comma delimited text
        binary,     // 

    };

    VM(std::istream &memoryContents, Source sourceType)
    {
        switch(sourceType)
        {
        case Source::text:
            constructRamFromText(memoryContents);
            break;

        case Source::binary:
            constructRamFromBinary(memoryContents);
        }
    }

    void run();

private:

    void constructRamFromText  (std::istream &memoryContents);
    void constructRamFromBinary(std::istream &memoryContents);

    CPU::Operand        decodeOperand    (Arch::Word    word);
    CPU::Instruction    decodeInstruction();

    Arch::Word          valueOf(CPU::Operand   operand);
    Arch::Word         &reg (CPU::Operand   operand);

private:
    Memory::Main        ram{};
    Memory::Stack       stack{};
    Memory::Registers   registers{};
    Arch::Word          pc;
};


}

#pragma comment(lib,"vm")
