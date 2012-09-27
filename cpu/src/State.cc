#include "State.h"

namespace cpu
{
  State::State() : 
    memory(triggers),
    ukkom(triggers),
    ir(triggers),
    ron(triggers) 
  {}

  void State::LoadMemoryFromFile(const std::string& filename)
  {
    memory.LoadFile(filename);
  }
  
  void State::NextState()
  {
    State newState;
    auto currentUkkom = ukkom.GetUKKOM();
    auto kop = memory.GetByte(currentUkkom);
    auto addr = memory.GetByte(currentUkkom + 1);
    triggers = DEKKOM::GetTriggers(kop);
    printf("%x %x\n",kop,addr);

       

    throw StopException();  
  }
}
