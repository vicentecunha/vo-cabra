/*
  VO-Cabra: timer1.h
  Author: Vicente Cunha
  Date: November 2016
*/

#include <stdint.h>

class Timer1
{
public:

  // FLAGS

  static volatile bool inputCapture;
  static volatile bool outputCompareMatchA;
  static volatile bool outputCompareMatchB ;
  static volatile bool overflow;
  static volatile uint64_t ovfCounter;
  static volatile uint16_t reload;

  // ENUMERATORS

  enum CompareOutputMode
  {
    NORMAL,
    TOGGLE,
    CLEAR,
    SET
  };

  enum InputCaptureEdge
  {
    FALLING,
    RISING
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

  // GETTERS

  static uint16_t getCounter();
  static uint16_t getInputCapture();

  // SETTERS

  static void setCompareOutputAMode(CompareOutputMode);
  static void setCompareOutputBMode(CompareOutputMode);
  static void setWaveformGenerationMode(int);
  static void setInputCaptureEdge(InputCaptureEdge);
  static void setClock(Clock);
  static void setCounter(uint16_t);
  static void setCompareA(uint16_t);
  static void setCompareB(uint16_t);
  static void setPeriod_s(double);

  // ENABLERS

  static void enableInputCaptureNoiseCanceler(bool);
  static void enableInputCaptureInterrupt(bool);
  static void enableOutputCompareMatchAInterrupt(bool);
  static void enableOutputCompareMatchBInterrupt(bool);
  static void enableOverflowInterrupt(bool);

  // PUBLIC FUNCTIONS

  static void forceOutputCompareA();
  static void forceOutputCompareB();
  static void setPeriod(double);
  static void start();
  static void stop();
  static void init();
};
