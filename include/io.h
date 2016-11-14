/*
  VO-Cabra: io.h
  Author: Vicente Cunha
  Date: November 2016
*/

class Io
{
public:

  // ENUMERATORS

  enum Port
  {
    PORT_B,
    PORT_C,
    PORT_D
  };

  enum Direction
  {
    INPUT,
    OUTPUT
  };

  // GETTERS

  static bool getPin(Port, int pin);

  // SETTERS

  static void setDirection(Port, int pin, Direction);
  static void setPin(Port, int pin, bool);

  // ENABLERS

  static void enablePullUp(bool);
};
