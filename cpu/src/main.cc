#include <iostream>

#include "Memory.h"

int Usage()
{
  std::cout << "Usage: main.out <filename with memory snapshot>" << std::endl;
}

int main(int argc,char** argv)
{
  if (argc != 2)
    return Usage();
  auto memory = cpu::Memory::InstanceFromFile(argv[1]);  
  return 0;
}
