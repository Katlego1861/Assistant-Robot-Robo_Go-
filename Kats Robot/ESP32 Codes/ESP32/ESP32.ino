#include <BluetoothSerial.h>

BluetoothSerial SerialBT;     
#define RXD2 16   // ESP32 pin connected to Nano TX
#define TXD2 17   // ESP32 pin connected to Nano RX

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // Use Serial2 for UART

  SerialBT.begin("Kats Robot");  // Bluetooth name
  Serial.println("✅ Bluetooth ready, pair with 'Kat Robot'");
}

void loop() {
  // --- Receive commands from phone app and send to Nano
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    Serial2.write(cmd);
    Serial.print("Sent to Nano: ");
    Serial.println(cmd);
  }

  // --- Receive sensor data from Nano and send to phone
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    SerialBT.println(data);
    Serial.print("From Nano: ");
    Serial.println(data);
  }
}
