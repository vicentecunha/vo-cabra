/*
  VO-Cabra: eeprom.h
  Author: Vicente Cunha
  Date: November 2016
*/

#include <stdint.h>

class Eeprom
{
public:
  
  uint8_t* firstInit_p        = (uint8_t*) 0x0000;
  uint16_t* temperatureZero_p = (uint16_t*) 0x0008;
  float* temperatureGain_p    = (float*) 0x0010;
  uint16_t* barometerZero_p   = (uint16_t*) 0x0018;
  float* barometerGain_p      = (float*) 0x0020;
  uint16_t* flowZero_p        = (uint16_t*) 0x0028;
  float* flowGain_p           = (float*) 0x0030;
  uint16_t* o2zero_p          = (uint16_t*) 0x0038;
  float* o2gain_p             = (float*) 0x0040;
  float* co2zero_p            = (float*) 0x0048;
  float* calCellVolts_p       = (float*) 0x0050;
  float* co2gain_p            = (float*) 0x0058;
  float* veOffset_p           = (float*) 0x0060;

  uint16_t temperatureZero    = 293;
  double temperatureGain      = 5.85;
  uint16_t barometerZero      = 0;
  double barometerGain        = 68.27;
  uint16_t flowZero           = 0;
  double flowGain             = 204.8;
  uint16_t o2zero             = 0;
  double o2gain               = 4.73;
  double co2zero              = 0;
  double calCellVolts         = 0;
  double co2gain              = 0;
  double veOffset             = 0;

  Eeprom();
};
