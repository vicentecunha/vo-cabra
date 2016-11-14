/*
  VO-Cabra: display.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "display.h"
#include "uart.h"
#include <string.h>

//========================//
//=== PUBLIC FUNCTIONS ===//
//========================//

void Display::send()
{
  Uart::sendData('{');
  line1[LINE_LENGTH-1] = '\0';
  line2[LINE_LENGTH-1] = '\0';
  line3[LINE_LENGTH-1] = '\0';
  line4[LINE_LENGTH-1] = '\0';
  Uart::sendString(line1);
  Uart::sendString(line3);
  Uart::sendString(line2);
  Uart::sendString(line4);
  Uart::sendData('}');
}

//====================//
//=== CONSTRUCTORS ===//
//====================//

Display::Display()
{
  strncpy(line1, "                    ", LINE_LENGTH);
  strncpy(line2, "                    ", LINE_LENGTH);
  strncpy(line3, "                    ", LINE_LENGTH);
  strncpy(line4, "                    ", LINE_LENGTH);
}
