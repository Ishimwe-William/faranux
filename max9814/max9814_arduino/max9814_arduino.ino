/*
 * MAX9814 Microphone Amplifier with LED Sound Visualization
 * Source: faranux.com
 * Author: Faranux Team
 * Date: July 31, 2025
 * 
 * Description: 
 * This sketch uses the MAX9814 microphone amplifier module to detect sound levels
 * and visualize them using an LED. Supports both Serial Monitor and Serial Plotter
 * for data visualization. The LED brightness changes proportionally to the 
 * detected sound intensity.
 * 
 * Hardware Connections:
 * - MAX9814 OUT pin -> Arduino A0
 * - MAX9814 VDD -> Arduino 5V
 * - MAX9814 GND -> Arduino GND
 * - MAX9814 GAIN -> Leave floating for 60dB (or GND for 40dB, VDD for 50dB)
 * - LED positive -> Arduino pin 9 (PWM capable)
 * - LED negative -> GND (via 220-330Ω resistor)
*/

// Define hardware pins
const int ledPin = 9;      // PWM capable pin for LED
const int micPin = A0;     // Analog input from MAX9814
const int sampleDelay = 10; // Delay between readings (ms)

// Define audio processing constants
const int minSound = 0;    // Minimum sound level
const int maxSound = 1023; // Maximum sound level (10-bit ADC)
const int minBright = 0;   // Minimum LED brightness
const int maxBright = 255; // Maximum LED brightness (8-bit PWM)

// Variables for signal processing
int rawValue = 0;          // Raw analog reading
int mappedValue = 0;       // Mapped LED brightness value
const int numReadings = 5; // Number of readings to average
int readings[5];           // Array to store readings
int readIndex = 0;         // Current reading index
int total = 0;             // Running total of readings

void setup() {
  // Initialize serial communication for debugging/plotting
  Serial.begin(9600);
  
  // Configure LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Initialize readings array
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  
  // Initial LED state
  analogWrite(ledPin, minBright);
  
  // Print column headers for Serial Plotter
  Serial.println("Raw,Mapped,Average");
}

void loop() {
  // Read the analog value from MAX9814
  rawValue = analogRead(micPin);
  
  // Update running average
  total = total - readings[readIndex];
  readings[readIndex] = rawValue;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  int average = total / numReadings;
  
  // Map the averaged value to LED brightness
  mappedValue = map(average, minSound, maxSound, minBright, maxBright);
  mappedValue = constrain(mappedValue, minBright, maxBright);
  
  // Set LED brightness
  analogWrite(ledPin, mappedValue);
  
  // Output data for Serial Plotter (comma-separated values)
  Serial.print(rawValue);    // Raw signal
  Serial.print(",");
  Serial.print(mappedValue); // Mapped LED value
  Serial.print(",");
  Serial.println(average);   // Moving average
  
  delay(sampleDelay);
}
