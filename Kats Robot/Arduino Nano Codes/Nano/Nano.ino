#include "MyUltrasonic.h"   // renamed library
#include "UARTLib.h"        // for UART communication

// --- Motor pins
int enA =9;
int in1 =8;
int in2 =7;
int enB =3;
int in3 =5;
int in4 =4;

// --- Sensors(trig,echo)
MyUltrasonic frontSensor(13,12);
MyUltrasonic leftSensor(11,10);
MyUltrasonic rightSensor(A0,A1);

// --- LEDs
int ledBack=2;
int ledLeft=A2; 
int ledRight=A3;

// UART
UARTLib uart(Serial);
int comms=9600;
// Threshold
const int threshold = 20;

// Motor functions
void stopMotors(){ 
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  }

void moveForward(){
  digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 }

void moveBackward(){
  digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);

Serial.println("Reversing...");

for (int i = 0; i < 3; i++) {
  digitalWrite(ledBack, HIGH);
  delay(200);
  digitalWrite(ledBack, LOW);
  delay(200);
}

}

void turnLeft(){
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);

Serial.println("Turning left...");

 digitalWrite(ledLeft,HIGH);
 }

void turnRight(){ 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,LOW); 
  digitalWrite(in3,LOW); 
  digitalWrite(in4,HIGH);

Serial.println("Turning Right...");

   digitalWrite(ledRight,HIGH);
  }


void setup() {
  Serial.begin(9600);
  uart.begin();

  // Motors
  pinMode(enA, OUTPUT);
   pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
   pinMode(in4, OUTPUT);

  // LEDs
  pinMode(ledBack, OUTPUT); 
  pinMode(ledLeft, OUTPUT); 
  pinMode(ledRight, OUTPUT);

  // Sensors
  frontSensor.begin(); 
  leftSensor.begin(); 
  rightSensor.begin();

   moveForward();
}

void loop() {
  // Update sensors
  frontSensor.update(); 
  leftSensor.update(); 
  rightSensor.update();

//To  get the distance
  long dF = frontSensor.getDistanceCM();
  long dL = leftSensor.getDistanceCM();
  long dR = rightSensor.getDistanceCM();

  // LEDs
  // setLED(ledLeft,dL>0 && dL<threshold);
  // setLED(ledRight,dR>0 && dR<threshold);

  // Obstacle avoidance
  if(dF>0 && dF<threshold){
     stopMotors();
      turnRight();
       delay(400); 
       stopMotors();
       return; 
       }

  if(dL>0 && dL<threshold){
     turnRight();
      delay(400); 
      stopMotors(); 
      return;
       }

  if(dR>0 && dR<threshold){ 
    turnLeft();
     delay(400);
      stopMotors();
       return;
        }

  // UART commands from ESP32 (follow commands)
  if(uart.available()){
    String cmd = uart.readMessage(); cmd.trim();
    if(cmd=="F") moveForward();
    else if(cmd=="B") moveBackward();
    else if(cmd=="L") turnLeft();
    else if(cmd=="R") turnRight();
    else if(cmd=="S") stopMotors();
  }

  // Send sensor data to ESP32
  String sensorData = "F:" + String(dF) + ";L:" + String(dL) + ";R:" + String(dR);
  uart.sendMessage(sensorData);

  delay(50);
}
