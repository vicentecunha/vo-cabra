/*
  VO-Cabra: io.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "io.h"
#include <avr/io.h>

//===============//
//=== GETTERS ===//
//===============//

bool Io::getPin(Port port, int pin)
{
  switch (port)
  {
    case PORT_B: return PINB & (1 << pin);
    case PORT_C: return PINC & (1 << pin);
    case PORT_D: return PIND & (1 << pin);
  }
}

//===============//
//=== SETTERS ===//
//===============//

void Io::setDirection(Port port, int pin, Direction dir)
{
  switch (port)
  {
    case PORT_B:
      if (dir == INPUT) DDRB &= ~(1 << pin);
      else              DDRB |=  (1 << pin);
      break;
    case PORT_C:
      if (dir == INPUT) DDRC &= ~(1 << pin);
      else              DDRC |=  (1 << pin);
      break;
    case PORT_D:
      if (dir == INPUT) DDRD &= ~(1 << pin);
      else              DDRD |=  (1 << pin);
      break;
  }
}

void Io::setPin(Port port, int pin, bool b)
{
  switch (port)
  {
    case PORT_B:
      if (b) PORTB |=  (1 << pin);
      else   PORTB &= ~(1 << pin);
      break;
    case PORT_C:
      if (b) PORTC |=  (1 << pin);
      else   PORTC &= ~(1 << pin);
      break;
    case PORT_D:
      if (b) PORTD |=  (1 << pin);
      else   PORTD &= ~(1 << pin);
      break;
  }
}

//================//
//=== ENABLERS ===//
//================//

void Io::enablePullUp(bool b)
{
  if (b) MCUCR &= ~(1 << PUD);
  else   MCUCR |=  (1 << PUD);
}
