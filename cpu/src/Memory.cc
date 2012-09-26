#include "Memory.h"

namespace cpu
{
  unsigned char ctoi(unsigned char symbol)
  {
    if (symbol >= '0' && symbol <= '9')
      return symbol - '0';
    if (symbol >= 'a' && symbol <= 'f')
      return symbol - 'a' + 10;
    if (symbol >= 'A' && symbol <= 'F')
      return symbol - 'A' + 10;

    throw MemoryException("Wrong symbol in memory sample");
  }

  Memory Memory::InstanceFromFile(const std::string &filename)
  {
    std::ifstream fin(filename.c_str());    
    unsigned char offset = 0;   
    unsigned char byte,symbol;
    Memory memory;
    while (fin >> symbol)
    {
      byte = ( ctoi(symbol) ) << 4;
      if (! (fin >> symbol) )
        throw MemoryException("Byte not full");
      byte = byte | ctoi(symbol);

      memory.memory[offset] = byte;
      offset++;
      if (offset == 0)
        break;
    }  
    return memory;
  }

  unsigned char Memory::GetByte(unsigned char offset) const
  {
    return memory[offset];
  }

}