#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <format>
#include "vm/vm.h"


void firstProgram()
{
    std::istringstream  firstProgram{"9,32768,32769,4,19,32768"};

    Synacor::VM vm{firstProgram, Synacor::VM::Source::text};

    vm.run();
}



int main()
try
{
//    firstProgram();

    std::ifstream  source{"challenge.bin", std::ios::in|std::ios::binary};
    
    if(!source)
    {
        throw_system_error("Couldn't open challenge.bin");
    }

    Synacor::VM challenge{source, Synacor::VM::Source::binary};

    challenge.run();

}
catch(std::exception &e)
{
    std::cout << "Caught : " << e.what() << "\n";
}