#ifndef _INC_IR_
#define _INC_IR_

#include "Triggers.h"

namespace cpu
{
  class IR
  {
    unsigned char ir;
    public:
      IR() : ir(0) {}
      
      unsigned char GetIR() const 
      {
        return ir;
      }

      void SetIR(unsigned char ir)
      {
        this->ir = ir;       
      }
  };
}

#endif
