/**
 FARANUX ELECTRONICS - TESTING LIGHT DEPENDENT RESISTOR WITH ARDUINO
**/

int LDR_Pin = A0;  // what pin on the arduino is the LDR output connected to

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(LDR_Pin));
  delay(3000);
}