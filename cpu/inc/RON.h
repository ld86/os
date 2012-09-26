#ifndef _INC_RON_
#define _INC_RON_

#include "Triggers.h"

class RON
{
  const cpu::Triggers& triggers;
  unsigned char sum,prznk;
  public:
    RON(const cpu::Triggers& tr) : triggers(tr),sum(0),prznk(0) {}

    unsigned char GetSUM() const
    {
      return sum;
    }    

    unsigned char GetPRZNK() const
    {
      return prznk;
    }

    void SetSUMandPRZNK(unsigned char sum,unsigned prznk)
    {
      if (triggers.ZAM1)
      {
        this->sum = sum;
        this->prznk = prznk;
      }
    }
}

#endif
