/*
  VO-Cabra: sensors.h
  Author: Vicente Cunha
  Date: November 2016
*/

#include <stdint.h>

class Sensors
{
public:

  static uint16_t readTemperature();
  static uint16_t readBarometer();
  static uint16_t readFlow();
  static uint16_t readOxygen();
};
