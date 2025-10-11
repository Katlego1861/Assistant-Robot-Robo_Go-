# ROBO_GO

ROBO_GO is a smart robot designed to combine autonomous obstacle avoidance with manual Bluetooth control.  
It serves as a flexible platform for learning robotics, embedded systems, and wireless communication using the ESP32 and Arduino Nano BLE 33 Sense.

---

## Features

- Dual-mode control: autonomous and Bluetooth manual mode  
- Obstacle detection using three ultrasonic sensors (front, left, right)  
- Wireless Bluetooth communication between ESP32 and Nano BLE  
- LED indicators for navigation and alerts  
- Buzzer feedback for warnings or mode switching  
- Battery powered using four 18650 Li-ion cells  

---

## Hardware Components

| Component | Description |
|------------|-------------|
| ESP32 | Main controller handling Bluetooth and decision logic |
| Arduino Nano BLE 33 Sense | Handles motor control and sensor data |
| L298N Motor Driver | Controls two DC motors for motion |
| 2x 12V DC geared motors (with encoders) | Provides robot movement |
| 3x Ultrasonic sensors (HC-SR04) | Front, left, and right obstacle detection |
| LEDs and Buzzer | Visual and audio indicators |
| 4x 18650 Li-ion batteries | Power supply |
| Battery holder and wiring | Power distribution |

---

## Wiring Overview

Main connections:

- ESP32 to Arduino Nano BLE 33 via UART communication  
- Nano BLE 33 to L298N Motor Driver for motor control  
- Ultrasonic sensors connected to the Nano BLE 33 (trigger and echo pins)  
- Bluetooth control handled by the ESP32’s built-in Bluetooth module  
- Power supplied by 4x 18650 batteries through a DC-DC step-down converter

Important:  
Always connect the battery negative directly to the common ground.  
Do not route high current through the switch to the converter; use the switch on the positive line only.

---

## Software Structure

**ESP32 Code**  
- Handles Bluetooth commands (forward, backward, left, right, stop)  
- Communicates with the Nano BLE 33 via UART  
- Sends and receives mode and control signals  

**Nano BLE 33 Code**  
- Reads ultrasonic sensors  
- Controls motor driver through pins enA, enB, in1–in4  
- Executes obstacle avoidance when in autonomous mode  

---

## How It Works

1. **Manual Mode**  
   - Controlled via a Bluetooth terminal app on a smartphone.  
   - Commands are sent to the ESP32, which relays movement instructions to the Nano BLE 33.

2. **Autonomous Mode**  
   - The Nano BLE 33 reads data from ultrasonic sensors.  
   - If an obstacle is detected, the robot decides to turn left or right to avoid it.

3. **Mode Switching**  
   - Bluetooth commands toggle between manual and automatic navigation.

---

## Bluetooth Commands

| Command | Action |
|----------|--------|
| F | Move Forward |
| B | Move Backward |
| L | Turn Left |
| R | Turn Right |
| S | Stop |
| A | Switch to Autonomous Mode |
| M | Switch to Manual Mode |

---

## Setup Instructions

1. Upload the respective sketches:  
   - ESP32_ROBO_GO.ino to the ESP32  
   - Nano_ROBO_GO.ino to the Arduino Nano BLE 33 Sense  

2. Pair the ESP32 to your phone using Bluetooth.  
3. Open a Bluetooth terminal app and send commands.  
4. Power the robot using the 18650 battery pack.  
5. Observe ROBO_GO drive and avoid obstacles.

---


## Images and Videos



---

## Author

**Katlego Legari**  



