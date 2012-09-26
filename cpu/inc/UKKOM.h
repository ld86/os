#ifndef _INC_UKKOM_
#define _INC_UKKOM_

#include "Memory.h"

namespace cpu
{

  class UKKOM
  {
    unsigned char ukkom;
    const cpu::Memory& memory;
    public:
    UKKOM(const cpu::Memory& mem) : memory(mem),ukkom(0) {};

    void SetUKKOM(unsigned char ukkom)
    {
      this->ukkom = ukkom;
    }

    unsigned short GetCurrentInstruction()
    {
      return ( (memory.GetByte(ukkom) << 8) | memory.GetByte(ukkom + 1) );
    }
  };
}
#endif
