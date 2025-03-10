/***
  Faranux.com
  -----------
  User Manual: https://files.seeedstudio.com/wiki/Soil_Moisture_Temperature_EC_Sensor/SoilMoisture_Temperature_ECSensorUserManual-S-Temp&VWC&EC-02.pdf
  
  Soil_Moisture_Temperature_EC_Sensor Connection to MAX485 TTL To RS485 Module
  ----------------------------------------------------------------------------
  DI                  ARDUINO D3
  DE                  ARDUINO D7
  RE                  ARDUINO D8
  RO                  ARDUINO D2

  GND                 ARDUINO GND & SENSOR BLACK WIRE
  A                   SENSOR YELLOW WIRE
  B                   SENSOR WHITE WIRE
  VCC                 ARDUINO VCC

  SENSOR RED WIRE     EXTERNAL +POWER [12V RECOMMENDED]
  SENSOR BLACK WIRE   EXTERNAL -POWER [GND]
  SENSOR GREEN WIRE   -

***/
#include <ModbusMaster.h> /*** https://github.com/4-20ma/ModbusMaster ***/
#include <SoftwareSerial.h>

#define MAX485_DE 7
#define MAX485_RE 8

ModbusMaster node;
SoftwareSerial Serial1(2,3);

void preTransmission() {
  digitalWrite(MAX485_RE, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission() {
  digitalWrite(MAX485_RE, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup() {
  pinMode(MAX485_RE, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  postTransmission(); // Init to receive mode

  Serial.begin(9600);  // Monitor
  Serial1.begin(9600); // RS485 via SoftwareSerial or Serial1 if you use Mega

  node.begin(1, Serial1); // 1 = MODBUS slave ID (default)
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  
  Serial.println("Soil Sensor Modbus Reader");
  Serial.println("------------------------");
}

void loop() {
  uint8_t result;
  
  // Read temperature, VWC, EC, Salinity, TDS, Epsilon (6 registers)
  result = node.readHoldingRegisters(0x00, 6);

  if (result == node.ku8MBSuccess) {
    // Print raw values first for debugging
    Serial.println("Raw Register Values:");
    for (int i = 0; i < 6; i++) {
      Serial.print("Register ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(node.getResponseBuffer(i));
    }
    
    Serial.println("\nConverted Values:");
    
    // Temperature (Register 0): -4000 to 8000 corresponds to -40.00 to 80.00°C
    float temperature = node.getResponseBuffer(0) / 100.0;
    Serial.print("Soil Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    // VWC (Register 1): 0-10000 corresponds to 0-100%
    float vwc = node.getResponseBuffer(1) / 100.0;
    Serial.print("Soil Moisture (VWC): ");
    Serial.print(vwc);
    Serial.println(" %");
    
    // EC (Register 2): 0-20000 corresponds to 0-2000μs/cm (0-2 mS/cm)
    float ec = node.getResponseBuffer(2) / 10.0; // Convert to μS/cm
    Serial.print("Soil EC: ");
    Serial.print(ec);
    Serial.println(" μS/cm");
    
    // Salinity (Register 3): 0-20000 corresponds to 0-2000mg/L
    float salinity = node.getResponseBuffer(3) / 10.0;
    Serial.print("Soil Salinity: ");
    Serial.print(salinity);
    Serial.println(" mg/L");
    
    // TDS (Register 4): 0-20000 corresponds to 0-2000mg/L
    float tds = node.getResponseBuffer(4) / 10.0;
    Serial.print("Soil TDS: ");
    Serial.print(tds);
    Serial.println(" mg/L");
    
    // Epsilon (Register 5): 0-8200 corresponds to 0.00-82.00
    float epsilon = node.getResponseBuffer(5) / 100.0;
    Serial.print("Soil Epsilon: ");
    Serial.print(epsilon);
    Serial.println("");
  } else {
    Serial.print("Modbus read failed. Error code: ");
    Serial.println(result);
  }
  
  Serial.println("------------------------");
  delay(2000);
}