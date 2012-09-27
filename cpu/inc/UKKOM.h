#ifndef _INC_UKKOM_
#define _INC_UKKOM_

#include "Triggers.h"

namespace cpu
{

  class UKKOM
  {
    unsigned char ukkom;
    const cpu::Triggers& triggers;
    public:
    UKKOM(const cpu::Triggers& tr) : triggers(tr),ukkom(0) {};

    void SetUKKOM(unsigned char ukkom)
    {
      if (triggers.PUSK)
        this->ukkom = ukkom;
    }
    
    unsigned char GetUKKOM()
    {      
      return ukkom;
    }

  };
}
#endif
