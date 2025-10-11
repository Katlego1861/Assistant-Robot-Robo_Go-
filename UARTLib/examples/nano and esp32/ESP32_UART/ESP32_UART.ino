#include <Arduino.h>
#include "UARTLib.h"

// ESP32 UART2 pins
#define RX_PIN 16  // receives from Nano TX (through voltage divider)
#define TX_PIN 17  // sends to Nano RX

// Create UARTLib object using Serial2
UARTLib uart(Serial2, 9600);

void setup() {
  Serial.begin(115200);                        // USB debug
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  uart.begin();

  uart.sendMessage("ESP32: UART Initialized");
  Serial.println("ESP32 ready to talk to Nano!");
}

void loop() {
  // Receive messages from Nano
  if (uart.available()) {
    String msg = uart.readMessage();
    if (msg.length() > 0) {
      Serial.print("From Nano: ");
      Serial.println(msg);

      // Respond to Nano
      if (msg == "HELLO") {
        uart.sendMessage("ESP32: Hi Nano!");
      }
    }
  }

  // Send periodic ping
  uart.sendMessage("ESP32: Ping");
  delay(1000);
}
