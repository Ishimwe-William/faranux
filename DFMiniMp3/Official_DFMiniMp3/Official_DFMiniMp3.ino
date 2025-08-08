/*
 * DFPlayer Mini MP3 Module Example
 * Using Official DFRobot Library
 * 
 * Tested and verified by Faranux.com engineering team
 * https://faranux.com
 * 
 * Hardware:
 * - Arduino Uno/Nano
 * - DFPlayer Mini MP3
 * - Speaker (3-4Ω)
 * - 1kΩ resistor between RX pin
 * 
 * Connection:
 * Arduino    DFPlayer Mini    Speaker
 * --------------------------------
 * 5V        ->   VCC
 * D11       ->   RX (1kΩ)
 * D10       ->   TX
 *           ->
 *           ->
 * SPEAKER_R ->   + (Right)
 * GND       ->   GND
 * SPEAKER_L ->   + (Left)
 */

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 11;  // Connects to module's RX
static const uint8_t PIN_MP3_RX = 10;  // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(20);
    // Play the "0001.mp3" in the "mp3" folder on the SD card
    player.playMp3Folder(1);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {

  delay(100);
}