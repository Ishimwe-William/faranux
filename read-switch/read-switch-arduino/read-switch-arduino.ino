/*
 * Reed Switch Interface with Arduino
 * Source: faranux.com
 * Author: Faranux Team
 * Date: July 31, 2025
 * Description: This sketch reads the state of a reed switch and displays it using LED and Serial monitor
 */

// Define pin connections
const int REED_PIN = 2;  // Digital pin connected to the reed switch
const int LED_PIN = 13;  // Built-in LED pin on most Arduino boards

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(9600);
    
    // Configure reed switch pin with internal pull-up resistor
    // When switch is open, pin will read HIGH
    // When switch is closed (magnet present), pin will read LOW
    pinMode(REED_PIN, INPUT_PULLUP);
    
    // Set LED pin as output to indicate switch state
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // Read the current state of the reed switch
    // proximity will be LOW when magnet is present (switch closed)
    // proximity will be HIGH when magnet is away (switch open)
    int proximity = digitalRead(REED_PIN);
    
    // Check the switch state and respond accordingly
    if (proximity == LOW) {
        // Magnet is present, switch is closed
        Serial.println("Switch closed");
        digitalWrite(LED_PIN, HIGH);  // Turn the LED on to indicate closed state
    }
    else {
        // No magnet present, switch is open
        Serial.println("Switch opened");
        digitalWrite(LED_PIN, LOW);   // Turn the LED off to indicate open state
    }
}
