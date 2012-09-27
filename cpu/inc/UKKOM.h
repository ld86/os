#ifndef _INC_UKKOM_
#define _INC_UKKOM_

#include "Triggers.h"

namespace cpu
{

  class UKKOM
  {
    unsigned char ukkom;
    public:
    UKKOM() : ukkom(0) {};

    void SetUKKOM(unsigned char ukkom)
    {
      this->ukkom = ukkom;
    }
    
    unsigned char GetUKKOM()
    {      
      return ukkom;
    }

  };
}
#endif
