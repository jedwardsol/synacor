#include <string>
#include <format>

#include "vm.h"
#include "thrower.h"


using namespace Synacor;

void VM::constructRamFromText(std::istream &source)
{
    std::string     number;
    Arch::Word      address{};

    while(std::getline(source,number,','))
    {
        auto word=stoi(number);

        if(   word < 0
           || word > Arch::MaxWord + Arch::NumRegisters)
        {
            throw_runtime_error(std::format("Bad source code {:x}",word));
        }

        ram[address]=word;
        address++;

    }
}

void VM::constructRamFromBinary(std::istream &source)
{
    Arch::Word      address{};
    Arch::Word      word{};

    while(source.read(reinterpret_cast<char*>(&word),sizeof(word)))
    {
        if(   word < 0
           || word > Arch::MaxWord + Arch::NumRegisters)
        {
            throw_runtime_error(std::format("Bad source code {:x}",word));
        }

        ram[address]=word;
        address++;
    }
}



CPU::Operand VM::decodeOperand(Arch::Word    word)
{
    if(word <= Arch::MaxWord)
    {
        return word;
    }

    word %= Arch::Modulo;

    if(word < Arch::NumRegisters)
    {
        return static_cast<Arch::Register>(word);
    }
    else
    {
        throw_runtime_error(std::format("Invalid operand MaxWord+{}",word));
    }
}

CPU::Instruction    VM::decodeInstruction()
{
    CPU::Instruction    instruction{};

    instruction.opcode = static_cast<CPU::OpCode>(ram.at(pc));

    auto const numOperands = CPU::numOperands.at(ram[pc]);                          // fault here on invalid opcode

    instruction.length = 1 + numOperands;                              

    for(int operand=0;operand < numOperands; operand++)
    {
        instruction.operands[operand] = decodeOperand (ram.at(pc+1+operand));
    }

    return instruction;
}

Arch::Word VM::read(CPU::Operand   operand)
{
    if(std::holds_alternative<Arch::Word>(operand))
    {
        return std::get<Arch::Word>(operand);
    }
    else if(std::holds_alternative<Arch::Register>(operand))
    {
        auto regnum = std::get<Arch::Register>(operand);

        return registers.at(regnum);
    }
    else
    {
        throw_runtime_error("Invalid operand type for reading");
    }
}

Arch::Word &VM::reg(CPU::Operand   operand)
{
    if(std::holds_alternative<Arch::Register>(operand))
    {
        auto regnum = std::get<Arch::Register>(operand);

        return registers.at(regnum);
    }
    else
    {
        throw_runtime_error("Invalid operand type for writing");
    }
}



void VM::run()
{
    bool running{true};

    while(running)
    {
        auto const &instruction{decodeInstruction()};

        switch(instruction.opcode)
        {
        case CPU::OpCode::Halt:
            return;

        case CPU::OpCode::Noop:
            break;

        case CPU::OpCode::Out:
            std::cout << static_cast<char>(read(instruction.operands[0]));
            break;

        case CPU::OpCode::Add:
        
            reg(instruction.operands[0]) =   read(instruction.operands[1])
                                           + read(instruction.operands[2]); 

            break;


        default:
            throw_runtime_error(std::format("Invalid instruction {} at pc {}",static_cast<int>(instruction.opcode),pc));
        }

        pc+=instruction.length;
    }


}
