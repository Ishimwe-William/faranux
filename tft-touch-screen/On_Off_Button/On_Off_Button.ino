#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();  // TFT display object

// Touchscreen pin definitions
#define XPT2046_IRQ 35
#define XPT2046_MOSI 33
#define XPT2046_MISO 32
#define XPT2046_CLK 26
#define XPT2046_CS 25

// Initialize SPI for touchscreen
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

// Screen dimensions
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

// Switch LED pin
#define LED_PIN 12

// Touch calibration values
#define TS_MINX 267
#define TS_MAXX 3768
#define TS_MINY 363
#define TS_MAXY 3708

// Button properties
#define FRAME_X 100
#define FRAME_Y 64
#define FRAME_W 120
#define FRAME_H 50

#define RED_COLOR TFT_RED
#define GREEN_COLOR TFT_GREEN
#define DISABLED_COLOR TFT_DARKGREY
#define FRAME_COLOR TFT_BLACK
#define TEXT_COLOR TFT_WHITE
#define TEXT_SIZE 2

// Debounce delay
#define DEBOUNCE_DELAY 200

bool switchState = false;  // Current state of the switch (false = OFF, true = ON)

//------------------------------------------------------------------------------------------
// Helper functions

bool isWithinBounds(uint16_t x, uint16_t y, uint16_t bx, uint16_t by, uint16_t bw, uint16_t bh) {
  return (x > bx && x < (bx + bw) && y > by && y < (by + bh));
}

void drawButton(bool isOn) {
  // Draw the red (OFF) button
  tft.fillRect(FRAME_X, FRAME_Y, FRAME_W / 2, FRAME_H, isOn ? DISABLED_COLOR : RED_COLOR);
  tft.setTextColor(TEXT_COLOR);
  tft.setTextSize(TEXT_SIZE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("OFF", FRAME_X + FRAME_W / 4, FRAME_Y + FRAME_H / 2);

  // Draw the green (ON) button
  tft.fillRect(FRAME_X + FRAME_W / 2, FRAME_Y, FRAME_W / 2, FRAME_H, isOn ? GREEN_COLOR : DISABLED_COLOR);
  tft.drawString("ON", FRAME_X + 3 * FRAME_W / 4, FRAME_Y + FRAME_H / 2);

  // Draw the frame around buttons
  tft.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, FRAME_COLOR);
}

void updateLED() {
  digitalWrite(LED_PIN, switchState);
}

//------------------------------------------------------------------------------------------
// Setup

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Initialize touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(1);

  // Initialize TFT screen
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLUE);

  // Draw initial button state
  drawButton(switchState);
  updateLED();
}

//------------------------------------------------------------------------------------------
// Main loop

void loop() {
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();

    // Map raw touch coordinates to screen coordinates
    int touchX = map(p.x, TS_MINX, TS_MAXX, 0, SCREEN_WIDTH);
    int touchY = map(p.y, TS_MAXY, TS_MINY, 0, SCREEN_HEIGHT);

    // Debugging raw and mapped touch data
    Serial.printf("Raw X: %d, Raw Y: %d, Mapped X: %d, Mapped Y: %d\n", p.x, p.y, touchX, touchY);

    if (switchState) {  // Currently ON
      if (isWithinBounds(touchX, touchY, FRAME_X, FRAME_Y, FRAME_W / 2, FRAME_H)) {
        Serial.println("Red button clicked! Turning OFF...");
        switchState = false;
        drawButton(switchState);
        updateLED();
      }
    } else {  // Currently OFF
      if (isWithinBounds(touchX, touchY, FRAME_X + FRAME_W / 2, FRAME_Y, FRAME_W / 2, FRAME_H)) {
        Serial.println("Green button clicked! Turning ON...");
        switchState = true;
        drawButton(switchState);
        updateLED();
      }
    }

    delay(DEBOUNCE_DELAY);  // Debounce delay
  }
}
