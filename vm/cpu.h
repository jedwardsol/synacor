#pragma once
#include <array>

namespace Synacor::CPU
{
    enum class OpCode
    {
        Halt,       // : 0              stop execution and terminate the program
        Set ,       // : 1 a b          set register <a> to the value of <b>
        Push,       // : 2 a            push <a> onto the stack
        Pop ,       // : 3 a            remove the top element from the stack and write it into <a>; empty stack = error
        Eq  ,       // : 4 a b c        set <a> to 1 if <b> is equal to <c>; set it to 0 otherwise
        Gt  ,       // : 5 a b c        set <a> to 1 if <b> is greater than <c>; set it to 0 otherwise
        Jmp ,       // : 6 a            jump to <a>
        Jt  ,       // : 7 a b          if <a> is nonzero, jump to <b>
        Jf  ,       // : 8 a b          if <a> is zero, jump to <b>
        Add ,       // : 9 a b c        assign into <a> the sum of <b> and <c> (modulo 32768)
        Mult,       // : 10 a b c       store into <a> the product of <b> and <c> (modulo 32768)
        Mod ,       // : 11 a b c       store into <a> the remainder of <b> divided by <c>
        And ,       // : 12 a b c       stores into <a> the bitwise and of <b> and <c>
        Or  ,       // : 13 a b c       stores into <a> the bitwise or of <b> and <c>
        Not ,       // : 14 a b         stores 15-bit bitwise inverse of <b> in <a>
        Rmem,       // : 15 a b         read memory at address <b> and write it to <a>
        Wmem,       // : 16 a b         write the value from <b> into memory at address <a>
        Call,       // : 17 a           write the address of the next instruction to the stack and jump to <a>
        Ret ,       // : 18             remove the top element from the stack and jump to it; empty stack = halt
        Out ,       // : 19 a           write the character represented by ascii code <a> to the terminal
        In  ,       // : 20 a           read a character from the terminal and write its ascii code to <a>; it can be assumed that once input starts, it will continue until a newline is encountered; this means that you can safely read whole lines from the keyboard and trust that they will be fully read
        Noop,       // : 21             no operation
    };

    inline constexpr std::array<int,22> numOperands
    {
       0,       // Halt,        : 0            
       2,       // Set ,        : 1 a b        
       1,       // Push,        : 2 a          
       1,       // Pop ,        : 3 a          
       3,       // Eq  ,        : 4 a b c      
       3,       // Gt  ,        : 5 a b c      
       1,       // Jmp ,        : 6 a          
       2,       // Jt  ,        : 7 a b        
       2,       // Jf  ,        : 8 a b        
       3,       // Add ,        : 9 a b c      
       3,       // Mult,        : 10 a b c     
       3,       // Mod ,        : 11 a b c     
       3,       // And ,        : 12 a b c     
       3,       // Or  ,        : 13 a b c     
       2,       // Not ,        : 14 a b       
       2,       // Rmem,        : 15 a b       
       2,       // Wmem,        : 16 a b       
       1,       // Call,        : 17 a         
       0,       // Ret ,        : 18           
       1,       // Out ,        : 19 a         
       1,       // In  ,        : 20 a         
       0,       // Noop,        : 21           
    };

    using Operand = std::variant<std::monostate, Arch::Word, Arch::Register>;

    struct Instruction
    {
        OpCode                  opcode;
        Arch::Word              length;
        std::array<Operand,3>   operands;
    };


}