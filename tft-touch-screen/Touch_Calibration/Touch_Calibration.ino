#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();

// Touchscreen pin definitions
#define XPT2046_IRQ 35
#define XPT2046_MOSI 33
#define XPT2046_MISO 32
#define XPT2046_CLK 26
#define XPT2046_CS 25

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

// Number of calibration points
#define CALIBRATION_POINTS 5

struct Point {
  int16_t x;
  int16_t y;
};

Point screenPoints[CALIBRATION_POINTS] = {
  { 15, 15 },
  { SCREEN_WIDTH - 15, 15 },
  { SCREEN_WIDTH - 15, SCREEN_HEIGHT - 15 },
  { 15, SCREEN_HEIGHT - 15 },
  { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }
};

Point touchPoints[CALIBRATION_POINTS];

int16_t minX = 32767, maxX = -32768;
int16_t minY = 32767, maxY = -32768;

void setup() {
  Serial.begin(115200);

  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(1);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  Serial.println("Touchscreen Calibration");
  Serial.println("Follow the instructions on the screen.");

  for (int i = 0; i < CALIBRATION_POINTS; i++) {
    tft.fillScreen(TFT_BLACK);

    // Draw a calibration point
    tft.fillCircle(screenPoints[i].x, screenPoints[i].y, 5, TFT_RED);
    tft.setCursor(10, SCREEN_HEIGHT - 30);
    tft.print("Touch the red circle");

    // Wait for touch and record raw data
    while (!touchscreen.tirqTouched() || !touchscreen.touched()) {
      delay(10);
    }

    TS_Point p = touchscreen.getPoint();
    touchPoints[i].x = p.x;
    touchPoints[i].y = p.y;

    // Update min and max values
    if (p.x < minX) minX = p.x;
    if (p.x > maxX) maxX = p.x;
    if (p.y < minY) minY = p.y;
    if (p.y > maxY) maxY = p.y;

    // Debounce and wait for release
    delay(500);
    while (touchscreen.tirqTouched() && touchscreen.touched()) {
      delay(10);
    }
  }

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 10);
  tft.print("Calibration complete!");
  tft.setCursor(10, 40);
  tft.print("Min/Max Values:");

  // Print min/max values on the screen
  tft.setCursor(10, 70);
  tft.printf("MinX: %d", minX);
  tft.setCursor(10, 100);
  tft.printf("MaxX: %d", maxX);
  tft.setCursor(10, 130);
  tft.printf("MinY: %d", minY);
  tft.setCursor(10, 160);
  tft.printf("MaxY: %d", maxY);

  Serial.println("Calibration Results:");
  for (int i = 0; i < CALIBRATION_POINTS; i++) {
    Serial.print("Point ");
    Serial.print(i + 1);
    Serial.print(": Screen (x, y) = (");
    Serial.print(screenPoints[i].x);
    Serial.print(", ");
    Serial.print(screenPoints[i].y);
    Serial.print(") -> Touch (x, y) = (");
    Serial.print(touchPoints[i].x);
    Serial.print(", ");
    Serial.print(touchPoints[i].y);
    Serial.println(")");
  }

  Serial.printf("MinX: %d, MaxX: %d, MinY: %d, MaxY: %d\n", minX, maxX, minY, maxY);
}

void loop() {
  // Calibration is complete. No further action required.
}
