/*
  VO-Cabra: timer0.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "timer0.h"
#include <avr/interrupt.h>
#include <avr/io.h>

//=============//
//=== FLAGS ===//
//=============//

volatile bool Timer0::outputCompareMatchA = false;
volatile bool Timer0::outputCompareMatchB = false;
volatile bool Timer0::overflow = false;
volatile uint64_t Timer0::ovfCounter = 0;
volatile uint8_t Timer0::reload = 0xFF;

//==================//
//=== INTERRUPTS ===//
//==================//

ISR(TIMER0_COMPA_vect)
{
  Timer0::outputCompareMatchA = true;
}

ISR(TIMER0_COMPB_vect)
{
  Timer0::outputCompareMatchB = true;
}

ISR(TIMER0_OVF_vect)
{
//  Timer0::overflow = true;
  Timer0::ovfCounter++;
  Timer0::setCounter(Timer0::reload);
}

//===============//
//=== GETTERS ===//
//===============//

uint8_t Timer0::getCounter()
{
  return TCNT0;
}

//===============//
//=== SETTERS ===//
//===============//

void Timer0::setCompareOutputAMode(CompareOutputMode com)
{
  switch (com)
  {
    case NORMAL:
      TCCR0A &= ~((1 << COM0A1)|(1 << COM0A0));
      break;
    case TOGGLE:
      TCCR0A &= ~(1 << COM0A1);
      TCCR0A |=  (1 << COM0A0);
      break;
    case CLEAR:
      TCCR0A |=  (1 << COM0A1);
      TCCR0A &= ~(1 << COM0A0);
      break;
    case SET:
      TCCR0A |= (1 << COM0A1)|(1 << COM0A0);
      break;
  }
}

void Timer0::setCompareOutputBMode(CompareOutputMode com)
{
  switch (com)
  {
    case NORMAL:
      TCCR0A &= ~((1 << COM0B1)|(1 << COM0B0));
      break;
    case TOGGLE:
      TCCR0A &= ~(1 << COM0B1);
      TCCR0A |=  (1 << COM0B0);
      break;
    case CLEAR:
      TCCR0A |=  (1 << COM0B1);
      TCCR0A &= ~(1 << COM0B0);
      break;
    case SET:
      TCCR0A |= (1 << COM0B1)|(1 << COM0B0);
      break;
  }
}

void Timer0::setWaveformGenerationMode(int mode)
{
  switch (mode)
  {
    case 0:
      TCCR0B &= ~(1 << WGM02);
      TCCR0A &= ~((1 << WGM01)|(1 << WGM00));
      break;
    case 1:
      TCCR0B &= ~(1 << WGM02);
      TCCR0A &= ~(1 << WGM01);
      TCCR0A |=  (1 << WGM00);
      break;
    case 2:
      TCCR0B &= ~(1 << WGM02);
      TCCR0A |=  (1 << WGM01);
      TCCR0A &= ~(1 << WGM00);
      break;
    case 3:
      TCCR0B &= ~(1 << WGM02);
      TCCR0A |=  ((1 << WGM01)|(1 << WGM00));
      break;
    case 4:
      TCCR0B |=  (1 << WGM02);
      TCCR0A &= ~((1 << WGM01)|(1 << WGM00));
      break;
    case 5:
      TCCR0B |=  (1 << WGM02);
      TCCR0A &= ~(1 << WGM01);
      TCCR0A |=  (1 << WGM00);
      break;
    case 6:
      TCCR0B |=  (1 << WGM02);
      TCCR0A |=  (1 << WGM01);
      TCCR0A &= ~(1 << WGM00);
      break;
    case 7:
      TCCR0B |=  (1 << WGM02);
      TCCR0A |=  ((1 << WGM01)|(1 << WGM00));
      break;
  }
}

void Timer0::setClock(Clock clock)
{
  switch (clock)
  {
    case NO_CLOCK:
      TCCR0B &= ~((1 << CS02)|(1 << CS01)|(1 << CS00));
      break;
    case PRE1:
      TCCR0B &= ~((1 << CS02)|(1 << CS01));
      TCCR0B |= (1 << CS00);
      break;
    case PRE8:
      TCCR0B &= ~((1 << CS02)|(1 << CS00));
      TCCR0B |= (1 << CS01);
      break;
    case PRE64:
      TCCR0B &= ~(1 << CS02);
      TCCR0A |= (1 << CS01)|(1 << CS00);
      break;
    case PRE256:
      TCCR0B |= (1 << CS02);
      TCCR0B &= ~((1 << CS01)|(1 << CS00));
      break;
    case PRE1024:
      TCCR0B |= (1 << CS02)|(1 << CS00);
      TCCR0B &= ~(1 < CS01);
      break;
    case EXTERNAL_FALLING:
      TCCR0B |= (1 << CS02)|(1 << CS01);
      TCCR0B &= ~(1 << CS00);
      break;
    case EXTERNAL_RISING:
      TCCR0B |= (1 << CS02)|(1 << CS01)|(1 << CS00);
      break;
  }
}

void Timer0::setCounter(uint8_t counts)
{
  TCNT0 = counts;
}

void Timer0::setCompareA(uint8_t counts)
{
  OCR0A = counts;
}

void Timer0::setCompareB(uint8_t counts)
{
  OCR0B = counts;
}

void Timer0::setPeriod_s(double period)
{
  reload = 0x100 - (16000000/1024)*period;
}

//================//
//=== ENABLERS ===//
//================//

void Timer0::enableOutputCompareMatchAInterrupt(bool b)
{
  if (b) TIMSK0 |=  (1 << OCIE0A);
  else   TIMSK0 &= ~(1 << OCIE0A);
}

void Timer0::enableOutputCompareMatchBInterrupt(bool b)
{
  if (b) TIMSK0 |=  (1 << OCIE0B);
  else   TIMSK0 &= ~(1 << OCIE0B);
}

void Timer0::enableOverflowInterrupt(bool b)
{
  if (b) TIMSK0 |=  (1 << TOIE0);
  else   TIMSK0 &= ~(1 << TOIE0);
}

//========================//
//=== PUBLIC FUNCTIONS ===//
//========================//

void Timer0::forceOutputCompareA()
{
  TCCR0B |= (1 << FOC0A);
}

void Timer0::forceOutputCompareB()
{
  TCCR0B |= (1 << FOC0B);
}

void Timer0::start()
{
  setCounter(reload);
  setClock(PRE1024);
}

void Timer0::stop()
{
  setClock(NO_CLOCK);
}

Timer0::init()
{
  enableOverflowInterrupt(true);
}
