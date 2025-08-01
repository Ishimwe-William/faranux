/*******************************************************************************
 * Laser Security System
 * ---------------------
 * Author: Faranux Team
 * Date: 2025-08-01
 * 
 * Description:
 * This sketch implements a laser-based security system that detects interruptions
 * in a laser beam path and triggers both visual (LED) and audible (buzzer) alerts.
 * The system status is also reported via Serial Monitor.
 * 
 * Hardware Setup:
 * - Arduino Uno Rev3
 * - Laser Transmitter (Tx) → Pin 2
 * - Laser Receiver (Rx) → Pin 3
 * - LED (with 180Ω resistor) → Pin 12
 * - 5V Active Buzzer → Pin 5
 * 
 * Serial Monitor Configuration:
 * - Baud Rate: 9600
 * - Line Ending: Newline
 ******************************************************************************/

#define LASER_TX 2    // Laser transmitter pin
#define LASER_RX 3    // Laser receiver pin
#define LED_PIN 12    // LED indicator pin
#define BUZZER_PIN 5  // Buzzer alarm pin

// System states
#define BEAM_CONNECTED 1
#define BEAM_BROKEN 0

// Delay between serial updates (ms)
const unsigned long SERIAL_UPDATE_INTERVAL = 500;
unsigned long lastSerialUpdate = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Laser Security System Initializing..."));
  
  pinMode(LASER_TX, OUTPUT);
  pinMode(LASER_RX, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LASER_TX, HIGH);  // Turn on laser transmitter
  
  Serial.println(F("System Armed and Ready!"));
}

void loop() {
  bool beamStatus = digitalRead(LASER_RX);
  unsigned long currentMillis = millis();

  // Update system state based on sensor reading
  if (beamStatus == BEAM_BROKEN) {
    digitalWrite(LED_PIN, LOW);     // Turn off LED
    digitalWrite(BUZZER_PIN, HIGH); // Activate buzzer
  } else {
    digitalWrite(LED_PIN, HIGH);    // Turn on LED
    digitalWrite(BUZZER_PIN, LOW);  // Deactivate buzzer
  }

  // Update Serial Monitor at specified intervals
  if (currentMillis - lastSerialUpdate >= SERIAL_UPDATE_INTERVAL) {
    lastSerialUpdate = currentMillis;
    Serial.print(F("Status: "));
    Serial.println(beamStatus == BEAM_BROKEN ? F("ALERT! Beam interrupted!") : F("Secure - Beam connected"));
  }
}