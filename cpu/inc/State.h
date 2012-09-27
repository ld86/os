#ifndef _INC_CONFIGURATION_
#define _INC_CONFIGURATION_

#include <exception>

#include "Memory.h"
#include "UKKOM.h"
#include "IR.h"
#include "RON.h"
#include "Triggers.h" 
#include "DEKKOM.h"

namespace cpu
{
  class StopException : public std::exception {};

  class State
  {
    Memory memory;
    UKKOM ukkom;
    IR ir;
    RON ron;
    Triggers triggers;   

      void UkkomAction(State& state);
      void MemoryAction(State& state);
      void IrAction(State& state);
      void RonAction(State& state); 

      unsigned char GetAddr();
      unsigned char GetRes();
      unsigned char GetPr();

    public:
      void LoadMemoryFromFile(const std::string& filename);
      void NextState();
  };
}
#endif
