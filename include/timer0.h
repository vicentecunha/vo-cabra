/*
  VO-Cabra: timer0.h
  Author: Vicente Cunha
  Date: November 2016
*/

#include <stdint.h>

class Timer0
{
public:

  // FLAGS

  static volatile bool outputCompareMatchA;
  static volatile bool outputCompareMatchB;
  static volatile bool overflow;
  static volatile uint64_t ovfCounter;
  static volatile uint8_t reload;

  // ENUMERATORS

  enum CompareOutputMode
  {
    NORMAL,
    TOGGLE,
    CLEAR,
    SET
  };

  enum Clock
  {
    NO_CLOCK,
    PRE1,
    PRE8,
    PRE64,
    PRE256,
    PRE1024,
    EXTERNAL_FALLING,
    EXTERNAL_RISING
  };

  // GETTER

  static uint8_t getCounter();

  // SETTERS

  static void setCompareOutputAMode(CompareOutputMode);
  static void setCompareOutputBMode(CompareOutputMode);
  static void setWaveformGenerationMode(int);
  static void setClock(Clock);
  static void setCounter(uint8_t);
  static void setCompareA(uint8_t);
  static void setCompareB(uint8_t);
  static void setPeriod_s(double);

  // ENABLERS

  static void enableOutputCompareMatchAInterrupt(bool);
  static void enableOutputCompareMatchBInterrupt(bool);
  static void enableOverflowInterrupt(bool);

  // PUBLIC FUNCTIONS

  static void forceOutputCompareA();
  static void forceOutputCompareB();
  static void start();
  static void stop();
  static void init();
};
