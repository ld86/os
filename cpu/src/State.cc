#include "State.h"

namespace cpu
{
  void State::LoadMemoryFromFile(const std::string& filename)
  {
    memory.LoadFile(filename);
  }
 
  void State::UkkomAction(State& state)
  {
    if (triggers.PUSK)
    {
      if (triggers.PEREH)
      {
        auto currentUkkom = ukkom.GetUKKOM();
        auto addr = memory.GetByte(currentUkkom) + ir.GetIR();
        state.ukkom.SetUKKOM(addr);
      }
      else
      {
        state.ukkom.SetUKKOM(ukkom.GetUKKOM() + 2);
      }
    }
    else
    {
      state.ukkom = ukkom;
    }
  }

  void State::NextState()
  {
    State nextState;
    auto currentUkkom = ukkom.GetUKKOM();
    auto kop = memory.GetByte(currentUkkom);
    auto addr = memory.GetByte(currentUkkom + 1);
    triggers = DEKKOM::GetTriggers(kop);
    printf("%x %x\n",kop,addr);

    if (kop == 0xff)
      throw StopException();  

    UkkomAction(nextState);
  }
}
