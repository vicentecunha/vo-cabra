/*
  VO-Cabra: eeprom.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "eeprom.h"
#include <avr/eeprom.h>

#define EEPROM_MAGIC_NUMBER 0xAA

//====================//
//=== CONSTRUCTORS ===//
//====================//

Eeprom::Eeprom()
{
  if (eeprom_read_byte(firstInit_p) == EEPROM_MAGIC_NUMBER) {
    temperatureZero = eeprom_read_word(temperatureZero_p);
    temperatureGain = (double) eeprom_read_float(temperatureGain_p);
    barometerZero   = eeprom_read_word(barometerZero_p);
    barometerGain   = (double) eeprom_read_float(barometerGain_p);
    flowZero        = eeprom_read_word(flowZero_p);
    flowGain        = (double) eeprom_read_float(flowGain_p);
    o2zero          = eeprom_read_word(o2zero_p);
    o2gain          = (double) eeprom_read_float(o2gain_p);
    co2zero         = (double) eeprom_read_float(co2zero_p);
    calCellVolts    = (double) eeprom_read_float(calCellVolts_p);
    co2gain         = (double) eeprom_read_float(co2gain_p);
    veOffset        = (double) eeprom_read_float(veOffset_p);
  } else {
    eeprom_write_byte (firstInit_p,       EEPROM_MAGIC_NUMBER);
    eeprom_write_word (temperatureZero_p, temperatureZero);
    eeprom_write_float(temperatureGain_p, (float) temperatureGain);
    eeprom_write_word (barometerZero_p,   barometerZero);
    eeprom_write_float(barometerGain_p,   (float) barometerGain);
    eeprom_write_word (flowZero_p,        flowZero);
    eeprom_write_float(flowGain_p,        (float) flowGain);
    eeprom_write_word (o2zero_p,          o2zero);
    eeprom_write_float(o2gain_p,          (float) o2gain);
    eeprom_write_float(co2zero_p,         (float) co2zero);
    eeprom_write_float(calCellVolts_p,    (float) calCellVolts);
    eeprom_write_float(co2gain_p,         (float) co2gain);
    eeprom_write_float(veOffset_p,        (float) veOffset);
  }
}
