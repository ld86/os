#include <iostream>

#include "State.h"

int Usage()
{
  std::cout << "Usage: main.out <filename with memory snapshot>" << std::endl;
}

int main(int argc,char** argv)
{
  if (argc != 2)
    return Usage();

  cpu::State state;
  state.LoadMemoryFromFile(argv[1]);
  while (true)
  {
    try
    {
      state.NextState();
    }
    catch (cpu::StopException)
    {
      break;
    }
  }
  return 0;
}
