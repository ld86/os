#ifndef _INC_IR_
#define _INC_IR_

#include "Triggers.h"

namespace cpu
{
  class IR
  {
    const cpu::Triggers& triggers;
    unsigned char ir;
    public:
      IR(const cpu::Triggers& tr) : triggers(tr),ir(0) {}
      
      unsigned char GetIR() const 
      {
        return ir;
      }

      void SetIR(unsigned char ir)
      {
        if (triggers.ZAM2)
          this->ir = ir;       
      }
  };
}

#endif
