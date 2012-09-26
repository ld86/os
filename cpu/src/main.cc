#include <iostream>

#include "Memory.h"
#include "Triggers.h"
#include "UKKOM.h"
#include "DEKKOM.h"

int Usage()
{
  std::cout << "Usage: main.out <filename with memory snapshot>" << std::endl;
}

int main(int argc,char** argv)
{
  if (argc != 2)
    return Usage();


  auto memory = cpu::Memory::InstanceFromFile(argv[1]);  
  cpu::Triggers triggers;
  cpu::UKKOM ukkom(memory);
  triggers.PUSK = true;

  while (triggers.PUSK)
  {
    auto instruction = ukkom.GetCurrentInstruction();
    triggers = cpu::DEKKOM::GetTriggers((unsigned char) (instruction >> 8) );
    auto address = (unsigned char) (instruction & 0xFF);
  }

  return 0;
}
