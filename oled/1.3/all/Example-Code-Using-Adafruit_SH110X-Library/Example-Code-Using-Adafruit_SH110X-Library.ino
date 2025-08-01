#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1     // Reset pin not used
#define I2C_ADDRESS   0x3C   // Most SH1106 modules use 0x3C

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  delay(100); // Small delay for power-up
  display.begin(I2C_ADDRESS, true);  // Start display

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(3, 2);
  display.println("Faranux SH1106 OLED");
  display.display();  // Push buffer to screen
}

void loop() {
  // You can add animations here
}
