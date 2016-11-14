/*
  VO-Cabra: display.h
  Author: Vicente Cunha
  Date: November 2016
*/

#define LINE_LENGTH 21

class Display
{
public:
  char line1[LINE_LENGTH];
  char line2[LINE_LENGTH];
  char line3[LINE_LENGTH];
  char line4[LINE_LENGTH];

  void send();

  Display();
};
