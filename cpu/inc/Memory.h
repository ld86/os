#ifndef _INC_MEMORY_
#define _INC_MEMORY_

#include <string>
#include <iostream>
#include <fstream>
#include <exception>

namespace cpu
{
  class MemoryException : public std::exception
  {
      std::string message;
    public:
      MemoryException(const std::string& message)
      {
        this->message = message;
      }

      virtual const char* what() const throw()
      {
        return message.c_str();
      }
  };

  class Memory
  {
    unsigned char memory[256];
    public:
    static Memory InstanceFromFile(const std::string& filename);
    unsigned char GetByte(unsigned char offset) const;
  };
}
#endif
