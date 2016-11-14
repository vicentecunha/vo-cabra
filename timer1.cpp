/*
  VO-Cabra: timer1.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "timer1.h"
#include <avr/interrupt.h>
#include <avr/io.h>

//=============//
//=== FLAGS ===//
//=============//

volatile bool Timer1::inputCapture = false;
volatile bool Timer1::outputCompareMatchA = false;
volatile bool Timer1::outputCompareMatchB = false;
volatile bool Timer1::overflow = false;
volatile uint64_t Timer1::ovfCounter = 0;
volatile uint16_t Timer1::reload = 0xFFFF;

//==================//
//=== INTERRUPTS ===//
//==================//

ISR(TIMER1_CAPT_vect)
{
  Timer1::inputCapture = true;
}

ISR(TIMER1_COMPA_vect)
{
  Timer1::outputCompareMatchA = true;
}

ISR(TIMER1_COMPB_vect)
{
  Timer1::outputCompareMatchB = true;
}

ISR(TIMER1_OVF_vect)
{
//  Timer1::overflow = true;
//  Timer1::ovfCounter++;
  Timer1::setCounter(Timer1::reload);
}

//===============//
//=== GETTERS ===//
//===============//

unsigned int Timer1::getCounter()
{
  return TCNT1;
}

unsigned int Timer1::getInputCapture()
{
  return ICR1;
}

//===============//
//=== SETTERS ===//
//===============//

void Timer1::setCompareOutputAMode(CompareOutputMode com)
{
  switch (com)
  {
    case NORMAL:
      TCCR1A &= ~((1 << COM1A1)|(1 << COM1A0));
      break;
    case TOGGLE:
      TCCR1A &= ~(1 << COM1A1);
      TCCR1A |=  (1 << COM1A0);
      break;
    case CLEAR:
      TCCR1A |=  (1 << COM1A1);
      TCCR1A &= ~(1 << COM1A0);
      break;
    case SET:
      TCCR1A |= (1 << COM1A1)|(1 << COM1A0);
      break;
  }
}

void Timer1::setCompareOutputBMode(CompareOutputMode com)
{
  switch (com)
  {
    case NORMAL:
      TCCR1A &= ~((1 << COM1B1)|(1 << COM1B0));
      break;
    case TOGGLE:
      TCCR1A &= ~(1 << COM1B1);
      TCCR1A |=  (1 << COM1B0);
      break;
    case CLEAR:
      TCCR1A |=  (1 << COM1B1);
      TCCR1A &= ~(1 << COM1B0);
      break;
    case SET:
      TCCR1A |= (1 << COM1B1)|(1 << COM1B0);
      break;
  }
}

void Timer1::setWaveformGenerationMode(int mode)
{
  switch (mode)
  {
    case 0:
      TCCR1B &= ~((1 << WGM13)|(1 << WGM12));
      TCCR1A &= ~((1 << WGM11)|(1 << WGM10));
      break;
    case 1:
      TCCR1B &= ~((1 << WGM13)|(1 << WGM12));
      TCCR1A &= ~(1 << WGM11);
      TCCR1A |=  (1 << WGM10);
      break;
    case 2:
      TCCR1B &= ~((1 << WGM13)|(1 << WGM12));
      TCCR1A |=  (1 << WGM11);
      TCCR1A &= ~(1 << WGM10);
      break;
    case 3:
      TCCR1B &= ~((1 << WGM13)|(1 << WGM12));
      TCCR1A |= (1 << WGM11)|(1 << WGM10);
      break;
    case 4:
      TCCR1B &= ~(1 << WGM13);
      TCCR1B |=  (1 << WGM12);
      TCCR1A &= ~((1 << WGM11)|(1 << WGM10));
      break;
    case 5:
      TCCR1B &= ~(1 << WGM13);
      TCCR1B |=  (1 << WGM12);
      TCCR1A &= ~(1 << WGM11);
      TCCR1A |=  (1 << WGM10);
      break;
    case 6:
      TCCR1B &= ~(1 << WGM13);
      TCCR1B |=  (1 << WGM12);
      TCCR1A |=  (1 << WGM11);
      TCCR1A &= ~(1 << WGM10);
      break;
    case 7:
      TCCR1B &= ~(1 << WGM13);
      TCCR1B |=  (1 << WGM12);
      TCCR1A |= (1 << WGM11)|(1 << WGM10);
      break;
    case 8:
      TCCR1B |=  (1 << WGM13);
      TCCR1B &= ~(1 << WGM12);
      TCCR1A &= ~((1 << WGM11)|(1 << WGM10));
      break;
    case 9:
      TCCR1B |=  (1 << WGM13);
      TCCR1B &= ~(1 << WGM12);
      TCCR1A &= ~(1 << WGM11);
      TCCR1A |=  (1 << WGM10);
      break;
    case 10:
      TCCR1B |=  (1 << WGM13);
      TCCR1B &= ~(1 << WGM12);
      TCCR1A |=  (1 << WGM11);
      TCCR1A &= ~(1 << WGM10);
      break;
    case 11:
      TCCR1B |=  (1 << WGM13);
      TCCR1B &= ~(1 << WGM12);
      TCCR1A |= (1 << WGM11)|(1 << WGM10);
      break;
    case 12:
      TCCR1B |= (1 << WGM13)|(1 << WGM12);
      TCCR1A &= ~((1 << WGM11)|(1 << WGM10));
      break;
    case 13:
      TCCR1B |= (1 << WGM13)|(1 << WGM12);
      TCCR1A &= ~(1 << WGM11);
      TCCR1A |=  (1 << WGM10);
      break;
    case 14:
      TCCR1B |= (1 << WGM13)|(1 << WGM12);
      TCCR1A |=  (1 << WGM11);
      TCCR1A &= ~(1 << WGM10);
      break;
    case 15:
      TCCR1B |= (1 << WGM13)|(1 << WGM12);
      TCCR1A |= (1 << WGM11)|(1 << WGM10);
      break;
  }
}

void Timer1::setInputCaptureEdge(InputCaptureEdge ice)
{
  switch (ice)
  {
    case FALLING: TCCR1B &= ~(1 << ICES1); break;
    case RISING:  TCCR1B |=  (1 << ICES1); break;
  }
}

void Timer1::setClock(Clock clock)
{
  switch (clock)
  {
    case NO_CLOCK:
      TCCR1B &= ~((1 << CS12)|(1 << CS11)|(1 << CS10));
      break;
    case PRE1:
      TCCR1B &= ~((1 << CS12)|(1 << CS11));
      TCCR1B |= (1 << CS10);
      break;
    case PRE8:
      TCCR1B &= ~((1 << CS12)|(1 << CS10));
      TCCR1B |= (1 << CS11);
      break;
    case PRE64:
      TCCR1B &= ~(1 << CS12);
      TCCR1B |= (1 << CS11)|(1 << CS10);
      break;
    case PRE256:
      TCCR1B |= (1 << CS12);
      TCCR1B &= ~((1 << CS11)|(1 << CS10));
      break;
    case PRE1024:
      TCCR1B |= (1 << CS12)|(1 << CS10);
      TCCR1B &= ~(1 << CS11);
      break;
    case EXTERNAL_FALLING:
      TCCR1B |= (1 << CS12)|(1 << CS11);
      TCCR1B &= ~(1 << CS10);
      break;
    case EXTERNAL_RISING:
      TCCR1B |= (1 << CS12)|(1 << CS11)|(1 << CS10);
      break;
  }
}

void Timer1::setCounter(uint16_t counts)
{
  TCNT1 = counts;
}

void Timer1::setCompareA(uint16_t counts)
{
  OCR1A = counts;
}

void Timer1::setCompareB(uint16_t counts)
{
  OCR1B = counts;
}

void Timer1::setPeriod_s(double period)
{
  reload = 0x10000 - (16000000/1024)*period;
}

//================//
//=== ENABLERS ===//
//================//

void Timer1::enableInputCaptureNoiseCanceler(bool b)
{
  if (b) TCCR1B |=  (1 << ICNC1);
  else   TCCR1B &= ~(1 << ICNC1);
}

void Timer1::enableInputCaptureInterrupt(bool b)
{
  if (b) TIMSK1 |=  (1 << ICIE1);
  else   TIMSK1 &= ~(1 << ICIE1);
}

void Timer1::enableOutputCompareMatchAInterrupt(bool b)
{
  if (b) TIMSK1 |=  (1 << OCIE1A);
  else   TIMSK1 &= ~(1 << OCIE1A);
}

void Timer1::enableOutputCompareMatchBInterrupt(bool b)
{
  if (b) TIMSK1 |=  (1 << OCIE1B);
  else   TIMSK1 &= ~(1 << OCIE1B);
}

void Timer1::enableOverflowInterrupt(bool b)
{
  if (b) TIMSK1 |=  (1 << TOIE1);
  else   TIMSK1 &= ~(1 << TOIE1);
}

//========================//
//=== PUBLIC FUNCTIONS ===//
//========================//

void Timer1::forceOutputCompareA()
{
  TCCR1C |= (1 << FOC1A);
}

void Timer1::forceOutputCompareB()
{
  TCCR1C |= (1 << FOC1B);
}

void Timer1::start()
{
  setCounter(reload);
  setClock(PRE1024);
}

void Timer1::stop()
{
  setClock(NO_CLOCK);
}

void Timer1::init()
{
  enableOverflowInterrupt(true);
}
