#ifndef _INC_TRIGGERS_
#define _INC_TRIGGERS_

namespace cpu
{
  class Triggers
  {
    public:
      Triggers()
      {
        PUSK = ZAPP = ZAM1 = ZAM2 = false;
        VZAP1 = VIB = CHIST = PEREH = false;
        OP = 0;
      }

      unsigned char OP;
      bool PEREH;
      bool PUSK;
      bool ZAPP;
      bool ZAM1;
      bool ZAM2;
      bool VZAP1;
      bool VIB;
      bool CHIST;    
  };
}
#endif
