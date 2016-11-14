/*
  VO-Cabra: uart.h
  Author: Vicente Cunha
  Date: November 2016
*/

class Uart
{
public:

  // FLAGS

  static volatile bool rxComplete;
  static volatile bool txComplete;
  static volatile bool dataRegisterEmpty;

  // ENUMERATORS

  enum Mode
  {
    ASYNCHRONOUS,
    SYNCHRONOUS,
    MSPIM
  };

  enum ParityMode
  {
    DISABLED,
    EVEN,
    ODD
  };

  enum StopBits
  {
    ONE_BIT,
    TWO_BIT
  };

  enum CharacterSize
  {
    FIVE_BIT,
    SIX_BIT,
    SEVEN_BIT,
    EIGHT_BIT,
    NINVE_BIT
  };

  enum ClockPolarity
  {
    POL0,
    POL1
  };

  enum Baudrate // assuming fosc = 16 MHz, single speed
  {
    BAUD2400    = 416,
    BAUD4800    = 207,
    BAUD9600    = 103,
    BAUD14400   = 68,
    BAUD19200   = 51,
    BAUD28800   = 34,
    BAUD38400   = 25,
    BAUD57600   = 16,
    BAUD76800   = 12,
    BAUD115200  = 8,
    BAUD230400  = 3,
    BAUD250000  = 3,
    BAUD500000  = 1,
    BAUD1000000 = 1
  };

  // GETTERS

  static char getData();
  static bool getFrameError();
  static bool getDataOverrun();
  static bool getParityError();
  static bool getRxDataBit8();

  // SETTERS

  static void setDoubleSpeed(bool);
  static void setMultiprocessorCommunicationMode(bool);
  static void setTxDataBit8(bool);
  static void setMode(Mode);
  static void setParityMode(ParityMode);
  static void setStopBits(StopBits);
  static void setCharacterSize(CharacterSize);
  static void setClockPolarity(ClockPolarity);
  static void setBaudrate(Baudrate);

  // ENABLERS

  static void enableRxCompleteInterrupt(bool);
  static void enableTxCompleteInterrupt(bool);
  static void enableDataRegisterEmptyInterrupt(bool);
  static void enableReceiver(bool);
  static void enableTransmitter(bool);

  // PUBLIC FUNCTIONS

  static void sendData(char);
  static void sendString(char*);
  static char waitData();
  static void init();
};
