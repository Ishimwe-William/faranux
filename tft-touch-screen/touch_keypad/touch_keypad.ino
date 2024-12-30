#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

// Initialize TFT display
TFT_eSPI tft = TFT_eSPI();

// Touchscreen pin definitions
#define XPT2046_IRQ 35   // Touch interrupt pin
#define XPT2046_MOSI 33  // Touch data input
#define XPT2046_MISO 32  // Touch data output
#define XPT2046_CLK 26   // Touch clock
#define XPT2046_CS 25    // Touch chip select

// TFT pins
// #define TFT_MISO 19
// #define TFT_MOSI 23
// #define TFT_SCLK 18
// #define TFT_CS   15  // Chip select control pin
// #define TFT_DC    2  // Data Command control pin
// #define TFT_RST   4  // Reset pin (could connect to RST pin) [ Set TFT_RST to -1 if display RESET is connected to ESP32 board RST]

// Initialize SPI for touchscreen on VSPI bus
SPIClass touchscreenSPI = SPIClass(VSPI);  //[Virtual] SPI 3 bus normally attached to pins 5 [CS], 18 [SCLK], 19 [MISO/SDO] and 23 [MOSI/SDI], but can be matrixed to any pins
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

#define LED_PIN 12

// Touch calibration values - adjust these based on your screen
#define TS_MINX 200
#define TS_MAXX 3700
#define TS_MINY 240
#define TS_MAXY 3800

// Keypad layout configuration
#define KEY_X 60          // Adjust to center keys horizontally
#define KEY_Y 150         // Adjust to position keys vertically
#define KEY_W 62          // Key width
#define KEY_H 30          // Key height
#define KEY_SPACING_X 18  // Horizontal space between keys
#define KEY_SPACING_Y 20  // Vertical space between keys
#define KEY_TEXTSIZE 1    // Size of text on keys

// Font definitions for different button types
#define LABEL1_FONT &FreeSansOblique12pt7b  // For command buttons (New, Del, Send)
#define LABEL2_FONT &FreeSansBold12pt7b     // For number buttons

// Display area configuration for number display
#define DISP_X 1
#define DISP_Y 10
#define DISP_W 238
#define DISP_H 50
#define DISP_TSIZE 3
#define DISP_TCOLOR TFT_CYAN

// Number buffer configuration
#define NUM_LEN 12                    // Maximum length of number input
char numberBuffer[NUM_LEN + 1] = "";  // +1 for null terminator
uint8_t numberIndex = 0;

// Status line position
#define STATUS_X 120  // Center position for status text
#define STATUS_Y 65   // Y position for status text

// Debug mode for calibration
#define DEBUG_TOUCH true

// Keypad button definitions
char keyLabel[15][5] = { "New", "Del", "Send", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "0", "#" };
uint16_t keyColor[15] = {
  TFT_RED, TFT_DARKGREY, TFT_DARKGREEN,  // Command buttons colors
  TFT_BLUE, TFT_BLUE, TFT_BLUE,          // Number buttons colors (1-3)
  TFT_BLUE, TFT_BLUE, TFT_BLUE,          // Number buttons colors (4-6)
  TFT_BLUE, TFT_BLUE, TFT_BLUE,          // Number buttons colors (7-9)
  TFT_BLUE, TFT_BLUE, TFT_BLUE           // Special characters (., 0, #)
};

// Button objects for the TFT library
TFT_eSPI_Button key[15];

// Structure to store button positions and dimensions for touch detection
struct ButtonArea {
  int x;              // Left edge of button
  int y;              // Top edge of button
  int width;          // Button width
  int height;         // Button height
  const char* label;  // Button label for debugging
} buttonAreas[15];

// Check if a touch point falls within a button's area
bool isWithinButton(int touchX, int touchY, const ButtonArea& button) {
  // Adjust X coordinate to compensate for touch offset
  int adjustedX = touchX - KEY_SPACING_X;
  return (adjustedX >= button.x && adjustedX <= (button.x + button.width) && touchY >= button.y && touchY <= (button.y + button.height));
}

// Draw the complete keypad and initialize button areas
void drawKeypad() {
  for (uint8_t row = 0; row < 5; row++) {
    for (uint8_t col = 0; col < 3; col++) {
      uint8_t b = col + row * 3;  // Calculate button index

      // Set appropriate font based on button type
      if (b < 3) tft.setFreeFont(LABEL1_FONT);
      else tft.setFreeFont(LABEL2_FONT);

      // Calculate button position
      int x = KEY_X + col * (KEY_W + KEY_SPACING_X);
      int y = KEY_Y + row * (KEY_H + KEY_SPACING_Y);

      // Store button area for touch detection
      buttonAreas[b] = {
        x - KEY_W / 2,  // x position (left edge)
        y - KEY_H / 2,  // y position (top edge)
        KEY_W,          // width
        KEY_H,          // height
        keyLabel[b]     // store label for debugging
      };

      // Initialize and draw the button
      key[b].initButton(&tft, x, y, KEY_W, KEY_H,
                        TFT_WHITE, keyColor[b], TFT_WHITE,
                        keyLabel[b], KEY_TEXTSIZE);
      key[b].drawButton();
    }
  }
}

// Process a key press event
void processKeyPress(uint8_t keyIndex) {
  // Visual feedback - show button pressed
  key[keyIndex].drawButton(true);

  // Handle different key actions
  if (keyIndex >= 3) {
    // Number keys and special characters
    if (numberIndex < NUM_LEN) {
      numberBuffer[numberIndex] = keyLabel[keyIndex][0];
      numberIndex++;
      numberBuffer[numberIndex] = 0;  // Null terminate
    }
    status("");
  } else if (keyIndex == 1) {
    // Delete key - remove last character
    if (numberIndex > 0) {
      numberIndex--;
      numberBuffer[numberIndex] = 0;
    }
    status("");
  } else if (keyIndex == 2) {
    // Send key - check the input and control the LED
    if (strcmp(numberBuffer, "123") == 0) {
      status("LED ON");
      digitalWrite(LED_PIN, HIGH);  // Turn on the LED
    } else if (strcmp(numberBuffer, "321") == 0) {
      status("LED OFF");
      digitalWrite(LED_PIN, LOW);  // Turn off the LED
    } else {
      status("Sent value to serial port");
    }
    Serial.println(numberBuffer);
  } else if (keyIndex == 0) {
    // New key - clear input
    status("Value cleared");
    numberIndex = 0;
    numberBuffer[numberIndex] = 0;
  }

  // Update the display with new content
  updateDisplay();

  delay(200);  // Debounce delay

  // Restore button appearance
  key[keyIndex].drawButton();
}


// Update the number display area
void updateDisplay() {
  tft.setTextDatum(TL_DATUM);        // Text alignment
  tft.setFreeFont(&FreeSans18pt7b);  // Set display font
  tft.setTextColor(DISP_TCOLOR);     // Set text color

  // Draw the current number
  int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);

  // Clear the rest of the display area
  tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1,
               DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);
}

// Display status message
void status(const char* msg) {
  tft.setTextPadding(240);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
  tft.setTextFont(0);
  tft.setTextDatum(TC_DATUM);
  tft.setTextSize(1);
  tft.drawString(msg, STATUS_X, STATUS_Y);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Ensure LED is off at the start


  // Initialize touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(0);  // Match screen rotation

  // Initialize display
  tft.init();
  tft.setRotation(0);  // Portrait orientation

  // Setup initial display
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_DARKGREY);
  tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

  // Draw the keypad
  drawKeypad();

  if (DEBUG_TOUCH) {
    Serial.println("Touch calibration: Touch the screen to see raw values");
  }
}

void loop() {
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get touch point
    TS_Point p = touchscreen.getPoint();

    if (DEBUG_TOUCH) {
      Serial.print("Raw X: ");
      Serial.print(p.x);
      Serial.print(" Y: ");
      Serial.print(p.y);
    }

    // Map raw touch coordinates to screen coordinates
    int touchX = map(p.x, TS_MAXX, TS_MINX, 0, SCREEN_WIDTH);
    int touchY = map(p.y, TS_MINY, TS_MAXY, 0, SCREEN_HEIGHT);

    if (DEBUG_TOUCH) {
      Serial.print(" | Mapped X: ");
      Serial.print(touchX);
      Serial.print(" Y: ");
      Serial.println(touchY);
    }

    // Check which button was pressed
    for (int i = 0; i < 15; i++) {
      if (isWithinButton(touchX, touchY, buttonAreas[i])) {
        if (DEBUG_TOUCH) {
          Serial.print("Button pressed: ");
          Serial.println(buttonAreas[i].label);
        }
        processKeyPress(i);
        break;
      }
    }

    delay(50);  // Debounce delay for touch input
  }
}