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
    return memory.GetByte(2 * currentUkkom + 1) + ir.GetIR();
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
        state.ukkom.SetUKKOM(ukkom.GetUKKOM() + 1);
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

  void State::IrAction(State& state)
  {
    if (triggers.ZAM2)
    {
      if (triggers.CHIST)
      {
        state.ir.SetIR(0);
      }
      else
      {
        state.ir.SetIR(GetRes());
      }
    }
    else
    {
      state.ir = ir;
    }
  }

  void State::RonAction(State& state)
  {
    if (triggers.ZAM1)
    {
      state.ron.SetSUMandPRZNK(GetRes(), GetRes() == 0 );
    }
    else
    {
      state.ron = ron;
    }
  }

  void State::Replace(State& state)
  {
    ukkom = state.ukkom;
    memory = state.memory;
    ir = state.ir;
    ron = state.ron;
  }

  void State::PrintMemory()
  {
    printf("Final memory snapshot");
    for (int i = 0; i <= 255; ++i)
    {
      if (i % 16 == 0)
        printf("\n");
      printf("%02X ",memory.GetByte(i));
    }
    printf("\n");
  }

  void State::NextState(std::map<std::string, bool>& mask)
  {
    State nextState;
    auto currentUkkom = ukkom.GetUKKOM();
    auto kop = memory.GetByte(2 * currentUkkom);
    auto addr = memory.GetByte(2 * currentUkkom + 1);
    triggers = DEKKOM::GetTriggers(kop,ron,mask);
    printf("%x %x\n",kop,addr);

    if (kop == 0xff)
      throw StopException();  

    UkkomAction(nextState);
    MemoryAction(nextState);
    IrAction(nextState);
    RonAction(nextState);
    Replace(nextState);

    printf("UKKOM: %x, RON: %x, IR: %x\n",ukkom.GetUKKOM(),ron.GetSUM(),ir.GetIR());
  }
}
