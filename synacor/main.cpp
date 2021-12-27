#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <format>
#include "vm/vm.h"



int main()
try
{
    std::istringstream  firstProgram{"9,32768,32769,4,19,32768"};

    Synacor::VM vm{firstProgram, Synacor::VM::Source::text};

    vm.run();

}
catch(std::exception &e)
{
    std::cout << "Caught : " << e.what() << "\n";
}