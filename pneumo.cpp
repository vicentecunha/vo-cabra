/*
  VO-Cabra: pneumo.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "pneumo.h"
#include "io.h"

//========================//
//=== PUBLIC FUNCTIONS ===//
//========================//

void Pneumo::openValve()
{
  Io::setPin(Io::PORT_B, 4, true);
}

void Pneumo::closeValve()
{
  Io::setPin(Io::PORT_B, 4, false);
}

void Pneumo::startPump()
{
  Io::setPin(Io::PORT_B, 5, true);
}

void Pneumo::stopPump()
{
  Io::setPin(Io::PORT_B, 5, false);
}

void Pneumo::init()
{
  Io::setDirection(Io::PORT_B, 5, Io::OUTPUT);
  Io::setDirection(Io::PORT_B, 4, Io::OUTPUT);
  Io::setPin(Io::PORT_B, 5, false);
  Io::setPin(Io::PORT_B, 4, false);
}
