#include "State.h"

namespace cpu
{
  void State::LoadMemoryFromFile(const std::string& filename)
  {
    memory.LoadFile(filename);
  }
 
  unsigned char State::GetAddr()
  {
    auto currentUkkom = ukkom.GetUKKOM();
    return memory.GetByte(currentUkkom + 1) + ir.GetIR();
  }
  
  unsigned char State::GetRes()
  {
    auto addr = GetAddr();
    unsigned char value = 0;
    if (triggers.VIB == 0)
      value = memory.GetByte(addr);
    else
      value = addr;

    switch (triggers.OP)
    {
      case 0:
        return ron.GetSUM();
      case 1:
        return value;
      case 2:
        return ron.GetSUM() + value;
      case 3:
        return value - ron.GetSUM();
    }
  }  

  void State::UkkomAction(State& state)
  {
    if (triggers.PUSK)
    {
      if (triggers.PEREH)
      {
        state.ukkom.SetUKKOM(GetAddr());
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

  void State::MemoryAction(State& state)
  {
    if (triggers.ZAPP)
    {
      state.memory.SetByte(GetAddr(),GetRes());
    }
    else
    {
      state.memory = memory;
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
    MemoryAction(nextState);
  }
}
