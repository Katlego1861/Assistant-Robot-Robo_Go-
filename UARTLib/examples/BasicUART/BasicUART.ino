#include <UARTLib.h>

// Correct instantiation
UARTLib uart(Serial1, 9600);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // UART to Nano
  uart.begin();

  uart.sendMessage("UART Initialized");
}

void loop() {
  if (uart.available()) {
    String msg = uart.readMessage();
    if (msg.length() > 0) {
      Serial.print("Received: ");
      Serial.println(msg);

      if (msg == "HELLO") {
        uart.sendMessage("Hi there!");
      } else if (msg == "FORWARD") {
        uart.sendMessage("Moving forward...");
      }
    }
  }
}
