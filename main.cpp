/*
  VO-Cabra: main.cpp
  Author: Vicente Cunha
  Date: November 2016
*/

#include "adc.h"
#include "display.h"
#include "pneumo.h"
#include "sensors.h"
#include "timer1.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
//#define F_CPU 16000000UL
//#include <util/delay.h>

//===============//
//=== GLOBALS ===//
//===============//

Display myDisplay;
double flowOffset = 0;
double oxygenGain = 0;

//===============//
//=== AUTOCAL ===//
//===============//

#define AUTOCAL_READINGS 4096
#define OXYGEN_IN_AIR 20.95

void autocal()
{
  double flowTotal = 0;
  double oxygTotal = 0;
  double flowAvg = 0;
  double flowStd = 0;
  double oxygAvg = 0;
  double oxygStd = 0;

  strncpy(myDisplay.line1, "                    ", LINE_LENGTH);
  strncpy(myDisplay.line2, "    PLEASE WAIT     ", LINE_LENGTH);
  strncpy(myDisplay.line3, "  AUTOCALIBRATING   ", LINE_LENGTH);
  strncpy(myDisplay.line4, "                    ", LINE_LENGTH);
  myDisplay.send();

  // CALCULATE AVERAGES

  Pneumo::openValve();
  Pneumo::startPump();
  for (int i = 0; i < AUTOCAL_READINGS; i++)
  {
    flowTotal += Sensors::readFlow();
    oxygTotal += Sensors::readOxygen();
  }
  flowAvg = flowTotal/AUTOCAL_READINGS;
  oxygAvg = oxygTotal/AUTOCAL_READINGS;

  // CALCULATE STANDARD DEVIATIONS

  flowTotal = 0;
  oxygTotal = 0;
  for (int i = 0; i < AUTOCAL_READINGS; i++)
  {
    flowTotal += pow(Sensors::readFlow() - flowAvg, 2);
    oxygTotal += pow(Sensors::readOxygen() - oxygAvg, 2);
  }
  flowStd = sqrt(flowTotal/AUTOCAL_READINGS);
  oxygStd = sqrt(oxygTotal/AUTOCAL_READINGS);
  Pneumo::stopPump();
  Pneumo::closeValve();

  flowOffset = ceil(flowAvg + 3*flowStd);
  oxygenGain = OXYGEN_IN_AIR/oxygAvg;

  snprintf(myDisplay.line1, LINE_LENGTH, "flowOffset = %.2f      ", flowOffset);
  snprintf(myDisplay.line2, LINE_LENGTH, "flowAvg = %.2f            ", flowAvg);
  snprintf(myDisplay.line3, LINE_LENGTH, "flowStd = %.2f            ", flowStd);
  strncpy(myDisplay.line4, " ANY KEY TO COTINUE ", LINE_LENGTH);
  myDisplay.send();
  Uart::getData();

  snprintf(myDisplay.line1, LINE_LENGTH, "oxygenGain = %.2f      ", oxygenGain);
  snprintf(myDisplay.line2, LINE_LENGTH, "oxygAvg = %.2f            ", oxygAvg);
  snprintf(myDisplay.line3, LINE_LENGTH, "oxygStd = %.2f            ", oxygStd);
  strncpy(myDisplay.line4, " ANY KEY TO COTINUE ", LINE_LENGTH);
  myDisplay.send();
  Uart::getData();
}

//==================//
//=== TEST SETUP ===//
//==================//

void testSetup()
{

}

//==================//
//=== START TEST ===//
//==================//

void startTest()
{
  double flow = 0;
  double flowTotal = 0;

  strncpy(myDisplay.line1, "                    ", LINE_LENGTH);
  strncpy(myDisplay.line2, "    TEST STARTED    ", LINE_LENGTH);
  strncpy(myDisplay.line3, "                    ", LINE_LENGTH);
  strncpy(myDisplay.line4, "                    ", LINE_LENGTH);
  myDisplay.send();

  Timer0::setPeriod_s(1e-3);
  Timer0::ovfCounter = 0;
  Timer0::start();
  while (Timer0::ovfCounter < 10e3)
  {
    flow = Sensors::readFlow();
    flowTotal += flow;
  }
  Timer0::stop();

  snprintf(myDisplay.line3, LINE_LENGTH, "flowTotal = %d          ", flowTotal);
  strncpy(myDisplay.line4, " ANY KEY TO COTINUE ", LINE_LENGTH);
  myDisplay.send();
  Uart::getData();
}

//=================//
//=== MAIN MENU ===//
//=================//

void mainMenu()
{
  strncpy(myDisplay.line1, "VO-CABRA MAIN MENU  ", LINE_LENGTH);
  strncpy(myDisplay.line2, " A = AUTOCAL        ", LINE_LENGTH);
  strncpy(myDisplay.line3, " B = TEST SETUP     ", LINE_LENGTH);
  strncpy(myDisplay.line4, " C = START TEST     ", LINE_LENGTH);
  myDisplay.send();

  char data = Uart::getData();
  if (data == 'A' || data == 'a') autocal();
  else if (data == 'B' || data == 'b') testSetup();
  else if (data == 'C' || data == 'c') startTest();
}

//============//
//=== MAIN ===//
//============//

int main()
{
  Adc::init();
  Pneumo::init();
  Timer0::init();
  Timer1::init();
  Uart::init();
  sei();

  autocal();
  while (true) mainMenu();
  return 0;
}
