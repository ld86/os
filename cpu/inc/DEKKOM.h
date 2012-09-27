#ifndef _INC_DEKKOM_
#define _INC_DEKKOM_

#include <fstream>
#include <iostream>

#include "Triggers.h"
#include "Memory.h"

namespace cpu
{
  class DEKKOM
  {
    public:
      static void Mask(Triggers& triggers)
      {
        std::ifstream fin("config");
        std::string configLine;
        while (fin >> configLine)
        {
          if (configLine[0] == '#')
            continue;
          
          std::string key = configLine.substr(0,configLine.find("="));
          std::string value = configLine.substr(configLine.find("=") + 1);
          unsigned char v = atoi(value.c_str());

          if (key == "PUSK")
            triggers.PEREH = v;
          else if (key == "ZAPP")
            triggers.ZAPP = v;
          else if (key == "ZAM1")
            triggers.ZAM1 = v;
          else if (key == "ZAM2")
            triggers.ZAM2 = v;
          else if (key == "VZAP1")
            triggers.VZAP1 = v;
          else if (key == "VIB")
            triggers.VIB = v;
          else if (key == "CHIST")
            triggers.CHIST = v;
          else if (key == "PEREH")
            triggers.PEREH = v;
          else if (key == "OP")
            triggers.OP = v;
        }
      }

      static cpu::Triggers GetTriggers(unsigned char KOP,RON& ron)
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
          case 0xf0:
            p = 4;
            op = 0xf;
            if (ron.GetPRZNK() == 1)
              pereh = 1;
            else 
              pereh = 0;
            break;
          case 0xf1:
            p = 4;
            op = 0xf;
            if (ron.GetPRZNK() == 0)
              pereh = 1;
            else 
              pereh = 0;
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

        Mask(triggers);

        return triggers;
      }
  };
}

#endif
