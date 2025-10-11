#include "UARTLib.h"

UARTLib::UARTLib(HardwareSerial &serial, unsigned long baud)
  : uart(serial), baudRate(baud) {}

void UARTLib::begin() {
  uart.begin(baudRate);
}

void UARTLib::sendMessage(const String &msg) {
  uart.println(msg);  
}

bool UARTLib::available() {
  return uart.available();
}

String UARTLib::readMessage() {
  while (uart.available()) {
    char c = uart.read();
    if (c == '\n') {           
      String msg = buffer;
      buffer = "";
      msg.trim();                
      if (msg.length()>0){
        return msg;
      }
    } else if (c != '\r'){
      buffer += c;
    }
  }
  return "";
}

bool UARTLib::commandReceived(const String &cmd) {
  String msg = readMessage();
  return (msg == cmd);
}
