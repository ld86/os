#ifndef _INC_PEREHMULT_
#define _INC_PEREHMULT_

#include "Triggers.h"
#include "UKKOM.h"

namespace cpu
{
  class PerehMult
  {
    const Triggers& triggers;
    UKKOM& ukkom;
    public:
      PerehMult(const Triggers& tr,UKKOM& kkm) : triggers(tr),ukkom(kkm) {}
      
      void Call()
      {
        auto newUkkom = ukkom.GetUKKOM() + 2;
        ukkom.SetUKKOM()
      }

  };
}

#endif
