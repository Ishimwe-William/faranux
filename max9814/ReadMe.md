# MAX9814 Microphone Module with Arduino

## Overview
This project demonstrates how to use the MAX9814 microphone amplifier module with an Arduino to create a sound-reactive LED. The LED's brightness changes in response to detected sound levels, creating a simple audio visualization effect.

## Features
- Real-time sound level detection
- Automatic gain control (AGC) through MAX9814
- LED brightness visualization
- Serial monitoring for debugging

## Hardware Requirements
- Arduino board (Uno, Nano, or compatible)
- MAX9814 microphone amplifier module
- LED (built-in or external)
- Current-limiting resistor (220-330Ω for external LED)
- Breadboard and jumper wires

## Connections
1. MAX9814 to Arduino:
   - OUT → A0
   - VDD → 5V
   - GND → GND
   - GAIN pin settings:
     * Ground (GND) = 40dB gain
     * VDD (5V) = 50dB gain
     * Floating = 60dB gain (default)
2. LED:
   - Connect to a PWM-capable pin (suggested pins: 3, 5, 6, 9, 10, or 11)
   - Remember to use a current-limiting resistor (220-330Ω)
   - Example: LED positive → pin 9, LED negative → GND via resistor

## Installation
1. Clone this repository or download the source code
2. Open `max9814_arduino.ino` in the Arduino IDE
3. Upload the sketch to your Arduino board

## Usage
1. Power up your Arduino
2. The LED will respond to sound:
   - Louder sounds = Brighter LED
   - Quieter sounds = Dimmer LED
3. Visualization options:
   - Serial Monitor (9600 baud): View raw sensor values
   - Serial Plotter (9600 baud): View real-time graphs of:
     * Raw signal (blue)
     * Mapped LED brightness (red)
     * Moving average (green)

## Circuit Diagram
Refer to the schematics folder for detailed connection diagrams:
- `max9814_breadboard.svg` - Breadboard layout
- `max9814.svg` - Schematic diagram

## Technical Details
- Sampling rate: ~100Hz (approximate, due to 10ms delay)
- ADC Resolution: 10-bit (0-1023)
- LED PWM Resolution: 8-bit (0-255)
- Operating voltage: 5V

## License
This project is open-source and available under the MIT License.

## Credits
Developed by Faranux Team (faranux.com)
Last updated: July 31, 2025