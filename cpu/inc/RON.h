#ifndef _INC_RON_
#define _INC_RON_

#include "Triggers.h"

namespace cpu
{
  class RON
  {
    unsigned char sum,prznk;
    public:
    RON() : sum(0),prznk(0) {}

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
      this->sum = sum;
      this->prznk = prznk;
    }
  };
}
#endif
