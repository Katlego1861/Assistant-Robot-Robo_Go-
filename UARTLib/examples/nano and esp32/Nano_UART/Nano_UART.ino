#include <Arduino.h>
#include "UARTLib.h"

// Use hardware Serial (D0 = RX, D1 = TX)
UARTLib uart(Serial, 9600);

void setup() {
  Serial.begin(9600);  // Hardware UART to ESP32
  uart.begin();

  uart.sendMessage("Nano: UART Initialized");
}

void loop() {
  // Receive messages from ESP32
  if (uart.available()) {
    String msg = uart.readMessage();
    if (msg.length() > 0) {
      // Cannot use Serial Monitor on Nano when using hardware Serial
      // You can see messages on ESP32 Serial Monitor instead
      if (msg == "ESP32: Ping") {
        uart.sendMessage("Nano: Pong");
      }
    }
  }

  // Send periodic hello
  uart.sendMessage("HELLO");
  delay(1000);
}
