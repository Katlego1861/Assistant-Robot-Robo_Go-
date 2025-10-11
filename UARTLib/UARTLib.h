#ifndef UARTLIB_H
#define UARTLIB_H

#include <Arduino.h>

class UARTLib {
  public:
    UARTLib(HardwareSerial &serial, unsigned long baud = 9600);

    void begin();
    void sendMessage(const String &msg);
    bool available();
    String readMessage();
    bool commandReceived(const String &cmd);

  private:
    HardwareSerial &uart;
    unsigned long baudRate;
    String buffer;
};

#endif
