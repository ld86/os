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

  std::ifstream fin("config");
  std::string configLine;
  std::map<std::string, bool> mask;
  while (fin >> configLine)
  {
      if (configLine[0] == '#')
          continue;

      std::string key = configLine.substr(0,configLine.find("="));
      std::string value = configLine.substr(configLine.find("=") + 1);
      mask[key] = atoi(value.c_str());
  }

  try
  {
      while (true)
      {
          state.NextState(mask);
      }
  }
  catch (cpu::StopException) {}
  state.PrintMemory();
  return 0;
}
