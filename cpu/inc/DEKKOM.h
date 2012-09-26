#ifndef _INC_DEKKOM_
#define _INC_DEKKOM_

#include "Triggers.h"
#include "Memory.h"

namespace cpu
{
  class DEKKOM
  {
    public:
      static cpu::Triggers GetTriggers(unsigned char KOP)
      {
        cpu::Triggers triggers;

        unsigned char i = 0,p = 0,op = 0,pereh = 0;
        switch (KOP)
        {
          case 0x00:
            p = 0;
            op = 0;
            pereh = 0;
            break;
          case 0x11:
            i = 0;
            p = 1;
            op = 1;
            pereh = 0;
            break;
          case 0x15:
            i = 1;
            p = 1;
            op = 1;
            pereh = 0;
            break;
          case 0x02:
            p = 2;
            op = 0;
            pereh = 0;
            break;
          case 0x21:
            i = 0;
            p = 1;
            op = 2;
            pereh = 0;
            break;
          case 0x25:
            i = 1;
            p = 1;
            op = 2;
            pereh = 0;
            break;
          case 0x31:
            i = 0;
            p = 1;
            op = 3;
            pereh = 0;
            break;
          case 0xfe:
            p = 4;
            op = 0xf;
            pereh = 1;
            break;
          case 0xff:
            p = 4;
            p = 0xf;
            pereh = 0;
            break;
          default:
            throw cpu::MemoryException("Invalid KOP");
        }
        
        triggers.VZAP1 = (p == 3);
        triggers.CHIST = !(p == 2 || p == 3);
        triggers.ZAM2 = (p != 3);
        triggers.ZAM1 = (p == 1);
        triggers.ZAPP = (p == 0);
        triggers.VIB = i;
        triggers.PUSK = (KOP != 0xFF);
        triggers.OP = op;
        triggers.PEREH = pereh;
        return triggers;
      }
  };
}

#endif
