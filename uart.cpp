/*
  VO-Cabra: uart.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>

//=============//
//=== FLAGS ===//
//=============//

volatile bool Uart::rxComplete = false;
volatile bool Uart::txComplete = false;
volatile bool Uart::dataRegisterEmpty = true;

//==================//
//=== INTERRUPTS ===//
//==================//

ISR(USART_RX_vect)
{
  Uart::rxComplete = true;
}

ISR(USART_TX_vect)
{
  Uart::txComplete = true;
}

ISR(USART_UDRE_vect)
{
  Uart::dataRegisterEmpty = true;
}

//===============//
//=== GETTERS ===//
//===============//

char Uart::getData()
{
  while (!(UCSR0A & (1 << RXC0))) ;
  return UDR0;
}

bool Uart::getFrameError()
{
  return UCSR0A & (1 << FE0);
}

bool Uart::getDataOverrun()
{
  return UCSR0A & (1 << DOR0);
}

bool Uart::getParityError()
{
  return UCSR0A & (1 << UPE0);
}

bool Uart::getRxDataBit8()
{
  return UCSR0A & (1 << RXB80);
}

//===============//
//=== SETTERS ===//
//===============//

void Uart::setDoubleSpeed(bool b)
{
  if (b) UCSR0A |=  (1 << U2X0);
  else   UCSR0A &= ~(1 << U2X0);
}

void Uart::setMultiprocessorCommunicationMode(bool b)
{
  if (b) UCSR0A |=  (1 << MPCM0);
  else   UCSR0A &= ~(1 << MPCM0);
}

void Uart::setTxDataBit8(bool b)
{
  if (b) UCSR0A |=  (1 << TXB80);
  else   UCSR0A &= ~(1 << TXB80);
}

void Uart::setMode(Mode m)
{
  switch (m)
  {
    case ASYNCHRONOUS:
      UCSR0C &= ~((1 << UMSEL01)|(1 << UMSEL00));
      break;
    case SYNCHRONOUS:
      UCSR0C &= ~(1 << UMSEL01);
      UCSR0C |=  (1 << UMSEL00);
      break;
    case MSPIM:
      UCSR0C |= (1 << UMSEL01)|(1 << UMSEL00);
      break;
  }
}

void Uart::setParityMode(ParityMode pm)
{
  switch (pm)
  {
    case DISABLED:
      UCSR0C &= ~((1 << UPM01)|(1 << UPM00));
      break;
    case EVEN:
      UCSR0C |=  (1 << UPM01);
      UCSR0C &= ~(1 << UPM00);
      break;
    case ODD:
      UCSR0C |= (1 << UPM01)|(1 << UPM00);
      break;
  }
}

void Uart::setStopBits(StopBits sb)
{
  switch (sb)
  {
    case ONE_BIT:
      UCSR0C &= ~(1 << USBS0);
      break;
    case TWO_BIT:
      UCSR0C |= (1 << USBS0);
      break;
  }
}

void Uart::setCharacterSize(CharacterSize cs)
{
  switch (cs)
  {
    case FIVE_BIT:
      UCSR0B &= ~(1 << UCSZ02);
      UCSR0C &= ~((1 << UCSZ01)|(1 << UCSZ00));
      break;
    case SIX_BIT:
      UCSR0B &= ~(1 << UCSZ02);
      UCSR0C &= ~(1 << UCSZ01);
      UCSR0C |=  (1 << UCSZ00);
      break;
    case SEVEN_BIT:
      UCSR0B &= ~(1 << UCSZ02);
      UCSR0C |=  (1 << UCSZ01);
      UCSR0C &= ~(1 << UCSZ00);
      break;
    case EIGHT_BIT:
      UCSR0B &= ~(1 << UCSZ02);
      UCSR0C |=  (1 << UCSZ01)|(1 << UCSZ00);
      break;
    case NINVE_BIT:
      UCSR0B |= (1 << UCSZ02);
      UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00);
      break;
  }
}

void Uart::setClockPolarity(ClockPolarity cp)
{
  switch (cp)
  {
    case POL0:
      UCSR0C &= ~(1 << UCPOL0);
      break;
    case POL1:
      UCSR0C |= (1 << UCPOL0);
      break;
  }
}

void Uart::setBaudrate(Baudrate baud)
{
  UBRR0 = baud;
}

//================//
//=== ENABLERS ===//
//================//

void Uart::enableRxCompleteInterrupt(bool b)
{
  if (b) UCSR0B |=  (1 << RXCIE0);
  else   UCSR0B &= ~(1 << RXCIE0);
}

void Uart::enableTxCompleteInterrupt(bool b)
{
  if (b) UCSR0B |=  (1 << TXCIE0);
  else   UCSR0B &= ~(1 << TXCIE0);
}

void Uart::enableDataRegisterEmptyInterrupt(bool b)
{
  if (b) UCSR0B |=  (1 << UDRIE0);
  else   UCSR0B &= ~(1 << UDRIE0);
}

void Uart::enableReceiver(bool b)
{
  if (b) UCSR0B |=  (1 << RXEN0);
  else   UCSR0B &= ~(1 << RXEN0);
}

void Uart::enableTransmitter(bool b)
{
  if (b) UCSR0B |=  (1 << TXEN0);
  else   UCSR0B &= ~(1 << TXEN0);
}

//========================//
//=== PUBLIC FUNCTIONS ===//
//========================//

void Uart::sendData(char data)
{
  while (!(UCSR0A & (1 << UDRE0))) ;
  UDR0 = data;
}

void Uart::sendString(char* str)
{
  int i = 0;
  while (str[i] != '\0')
  {
    while (!(UCSR0A & (1 << UDRE0))) ;
    sendData(str[i++]);
  }
}

void Uart::init()
{
  setDoubleSpeed(true);
  setBaudrate(BAUD4800);
  enableReceiver(true);
  enableTransmitter(true);
}
