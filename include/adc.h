/*
  VO-Cabra: adc.h
  Author: Vicente Cunha
  Date: November 2016
*/

#include <stdint.h>

class Adc
{
public:

  // FLAGS

  static volatile bool conversionComplete;

  // ENUMERATORS

  enum Reference
  {
    AREF,
    AVCC,
    INTERNAL
  };

  enum Adjustment
  {
    LEFT,
    RIGHT
  };

  enum Channel
  {
    ADC0 = 0,
    ADC1 = 1,
    ADC2 = 2,
    ADC3 = 3,
    ADC4 = 4,
    ADC5 = 5,
    ADC6,
    ADC7,
    VBG,
    GND
  };

  enum Prescaler
  {
    PRE1,
    PRE2,
    PRE4,
    PRE8,
    PRE16,
    PRE32,
    PRE64,
    PRE128
  };

  enum AutoTriggerSource
  {
    FREE_RUNNING,
    ANALOG_COMPARATOR,
    EXTERNAL_INTERRUPT,
    TIMER0_COMPARE_MATCH_A,
    TIMER0_OVERFLOW,
    TIMER1_COMPARE_MATCH_B,
    TIMER1_OVERFLOW,
    TIMER1_CAPTURE_EVENT
  };

  // GETTERS

  static uint16_t getData();

  // SETTERS

  static void setReference(Reference);
  static void setResultAdjustment(Adjustment);
  static void setChannel(Channel);
  static void setPrescaler(Prescaler);
  static void setAutoTriggerSource(AutoTriggerSource);

  // ENABLERS

  static void enable(bool);
  static void enableAutoTrigger(bool);
  static void enableConversionCompleteInterrupt(bool);
  static void enableDigitalInput(bool, Channel);

  // PUBLIC FUNCTIONS

  static void startConversion();
  static uint16_t performConversion(Channel);
  static void init();
};
