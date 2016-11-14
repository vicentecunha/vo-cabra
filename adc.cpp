/*
  VO-Cabra: adc.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "adc.h"
#include <avr/interrupt.h>
#include <avr/io.h>

//=============//
//=== FLAGS ===//
//=============//

volatile bool Adc::conversionComplete = false;

//==================//
//=== INTERRUPTS ===//
//==================//

ISR(ADC_vect)
{
  Adc::conversionComplete = true;
}

//===============//
//=== GETTERS ===//
//===============//

uint16_t Adc::getData()
{
  return ADC;
}

//===============//
//=== SETTERS ===//
//===============//

void Adc::setReference(Reference reference)
{
  switch (reference)
  {
    case AREF:
      ADMUX &= ~((1 << REFS1)|(1 << REFS0));
      break;
    case AVCC:
      ADMUX |= (1 << REFS0);
      ADMUX &= ~(1 << REFS1);
      break;
    case INTERNAL:
      ADMUX |= (1 << REFS1)|(1 << REFS0);
      break;
  }
}

void Adc::setResultAdjustment(Adjustment adjustment)
{
  switch (adjustment) {
    case LEFT: ADMUX |= (1 << ADLAR); break;
    case RIGHT: ADMUX &= ~(1 << ADLAR); break;
  }
}

void Adc::setChannel(Channel channel)
{
  switch (channel)
  {
    case ADC0:
      ADMUX &= ~((1 << MUX3)|(1 << MUX2)|(1 << MUX1)|(1 << MUX0));
      break;
    case ADC1:
      ADMUX |= (1 << MUX0);
      ADMUX &= ~((1 << MUX3)|(1 << MUX2)|(1 << MUX1));
      break;
    case ADC2:
      ADMUX |= (1 << MUX1);
      ADMUX &= ~((1 << MUX3)|(1 << MUX2)|(1 << MUX0));
      break;
    case ADC3:
      ADMUX |= ((1 << MUX1)|(1 << MUX0));
      ADMUX &= ~((1 << MUX3)|(1 << MUX2));
      break;
    case ADC4:
      ADMUX |= (1 << MUX2);
      ADMUX &= ~((1 << MUX3)|(1 << MUX1)|(1 << MUX0));
      break;
    case ADC5:
      ADMUX |= ((1 << MUX2)|(1 << MUX0));
      ADMUX &= ~((1 << MUX3)|(1 << MUX1));
      break;
    case ADC6:
      ADMUX |= ((1 << MUX2)|(1 << MUX1));
      ADMUX &= ~((1 << MUX3)|(1 << MUX0));
      break;
    case ADC7:
      ADMUX |= ((1 << MUX2)|(1 << MUX1)|(1 << MUX0));
      ADMUX &= ~(1 << MUX3);
      break;
    case VBG:
      ADMUX |= ((1 << MUX3)|(1 << MUX2)|(1 << MUX1));
      ADMUX &= ~(1 << MUX0);
      break;
    case GND:
      ADMUX |= ((1 << MUX3)|(1 << MUX2)|(1 << MUX1)|(1 << MUX0));
      break;
  }
}

void Adc::setPrescaler(Prescaler prescaler)
{
  switch (prescaler) {
    case PRE1:
      ADCSRA &= ~((1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0));
      break;
    case PRE2:
      ADCSRA |= (1 << ADPS0);
      ADCSRA &= ~((1 << ADPS2)|(1 << ADPS1));
      break;
    case PRE4:
      ADCSRA |= (1 << ADPS1);
      ADCSRA &= ~((1 << ADPS2)|(1 << ADPS0));
      break;
    case PRE8:
      ADCSRA |= (1 << ADPS1)|(1 << ADPS0);
      ADCSRA &= ~(1 << ADPS2);
      break;
    case PRE16:
      ADCSRA |= (1 << ADPS2);
      ADCSRA &= ~((1 << ADPS1)|(1 << ADPS0));
      break;
    case PRE32:
      ADCSRA |= (1 << ADPS2)|(1 << ADPS0);
      ADCSRA &= ~(1 << ADPS1);
      break;
    case PRE64:
      ADCSRA |= (1 << ADPS2)|(1 << ADPS1);
      ADCSRA &= ~(1 << ADPS0);
      break;
    case PRE128:
      ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
      break;
  }
}

void Adc::setAutoTriggerSource(AutoTriggerSource ats)
{
  switch (ats)
  {
    case FREE_RUNNING:
      ADCSRB &= ~((1 << ADTS2)|(1 << ADTS1)|(1 << ADTS0));
      break;
    case ANALOG_COMPARATOR:
      ADCSRB |= (1 << ADTS0);
      ADCSRB &= ~((1 << ADTS2)|(1 << ADTS1));
      break;
    case EXTERNAL_INTERRUPT:
      ADCSRB |= (1 << ADTS1);
      ADCSRB &= ~((1 << ADTS2)|(1 << ADTS0));
      break;
    case TIMER0_COMPARE_MATCH_A:
      ADCSRB |= (1 << ADTS1)|(1 << ADTS0);
      ADCSRB &= ~(1 << ADTS2);
      break;
    case TIMER0_OVERFLOW:
      ADCSRB |= (1 << ADTS2);
      ADCSRB &= ~((1 << ADTS1)|(1 << ADTS0));
      break;
    case TIMER1_COMPARE_MATCH_B:
      ADCSRB |= (1 << ADTS2)|(1 << ADTS0);
      ADCSRB &= ~(1 << ADTS1);
      break;
    case TIMER1_OVERFLOW:
      ADCSRB |= (1 << ADTS2)|(1 << ADTS1);
      ADCSRB &= ~(1 << ADTS0);
      break;
    case TIMER1_CAPTURE_EVENT:
      ADCSRB |= (1 << ADTS2)|(1 << ADTS1)|(1 << ADTS0);
      break;
  }
}

//================//
//=== ENABLERS ===//
//================//

void Adc::enable(bool b)
{
  if (b) ADCSRA |=  (1 << ADEN);
  else   ADCSRA &= ~(1 << ADEN);
}

void Adc::enableAutoTrigger(bool b)
{
  if (b) ADCSRA |=  (1 << ADATE);
  else   ADCSRA &= ~(1 << ADATE);
}

void Adc::enableConversionCompleteInterrupt(bool b)
{
  if (b) ADCSRA |=  (1 << ADIE);
  else   ADCSRA &= ~(1 << ADIE);
}

void Adc::enableDigitalInput(bool b, Channel channel)
{
  if (b) DIDR0 &= ~(1 << channel);
  else DIDR0 |= (1 << channel);
}

//========================//
//=== PUBLIC FUNCTIONS ===//
//========================//

void Adc::startConversion()
{
  ADCSRA |= (1 << ADSC);
}

uint16_t Adc::performConversion(Channel channel)
{
  setChannel(channel);
  startConversion();
  while (ADCSRA & (1 << ADSC)) ;
  return getData();
}

void Adc::init()
{
  setPrescaler(PRE128);
  enable(true);
}
