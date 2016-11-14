/*
  VO-Cabra: sensors.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "adc.h"
#include "sensors.h"

//========================//
//=== PUBLIC FUNCTIONS ===//
//========================//

uint16_t Sensors::readTemperature()
{
  return Adc::performConversion(Adc::ADC0);
}

uint16_t Sensors::readBarometer()
{
  return Adc::performConversion(Adc::ADC1);
}

uint16_t Sensors::readFlow()
{
  return Adc::performConversion(Adc::ADC2);
}

uint16_t Sensors::readOxygen()
{
  return Adc::performConversion(Adc::ADC3);
}
