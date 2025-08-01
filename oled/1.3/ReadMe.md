# OLED Display Examples for Arduino and NodeMCU

This repository contains examples for interfacing with different OLED displays using Arduino and NodeMCU boards.

## Supported Displays

- 0.96" OLED Display (SSD1306 128x64)
- 1.3" OLED Display (SH1106 128x64)

## Hardware Requirements

### For Arduino
- Arduino board (UNO, MEGA, etc.)
- OLED Display (0.96" or 1.3")
- Jumper wires

### For NodeMCU
- NodeMCU ESP8266 board
- OLED Display (0.96" or 1.3")
- Jumper wires

## Required Libraries

- For 0.96" Display:
  - Adafruit_GFX
  - Adafruit_SSD1306

- For 1.3" Display:
  - U8glib (Arduino)
  - Adafruit_SH110X (NodeMCU)

## Pin Connections

### 0.96" OLED Display (I2C)
- VCC → 3.3V/5V
- GND → GND
- SCL → A5 (Arduino) / D1 (NodeMCU)
- SDA → A4 (Arduino) / D2 (NodeMCU)

### 1.3" OLED Display (I2C)
- VCC → 3.3V/5V
- GND → GND
- SCL → A5 (Arduino) / D1 (NodeMCU)
- SDA → A4 (Arduino) / D2 (NodeMCU)

## Example Sketches

### 0.96" OLED Examples
1. Basic Text Display ([ssd1306_128x64_i2c.ino](oled/0.96/Code_Arduino_/ssd1306_128x64_i2c/ssd1306_128x64_i2c.ino))
   - Displays simple text
   - I2C address: 0x3C

2. Advanced Graphics ([ssd1306_128x64_i2c.ino](oled/0.96/Code_Arduino_NodeMCU/ssd1306_128x64_i2c/ssd1306_128x64_i2c.ino))
   - Demonstrates various graphics functions:
     - Lines
     - Rectangles
     - Circles
     - Text
     - Bitmaps
     - Animations

### 1.3" OLED Examples
1. Hello World ([HelloWorld_1.3_inch_OLED_and_arduino.ino](oled/1.3/arduino/HelloWorld_1.3_inch_OLED_and_arduino/HelloWorld_1.3_inch_OLED_and_arduino.ino))
   - Basic text display using U8glib
   - Compatible with Arduino

2. Graphics Demo ([1.3_inch_oled_nodemcu.ino](oled/1.3/nodemcu/1.3_inch_oled_nodemcu/1.3_inch_oled_nodemcu.ino))
   - Complete graphics demo for NodeMCU
   - Uses Adafruit_SH110X library
   - Includes animations and various drawing functions

## Display Configuration

### I2C Addresses
- Most displays use 0x3C
- Some displays might use 0x3D
- If screen is blank, try changing the address

### Display Size
```cpp
#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height
```

# 1.3" OLED Display Examples
Source: faranux.com

This repository provides examples for interfacing 1.3" OLED displays (SH1106 128x64) with Arduino and NodeMCU boards. These examples demonstrate both basic and advanced display functionality.

## Hardware Requirements

### For Arduino Setup
- Arduino board (UNO/MEGA)
- 1.3" OLED Display (SH1106 128x64)
- 4x Jumper wires
- USB cable for programming

### For NodeMCU Setup
- NodeMCU ESP8266 board
- 1.3" OLED Display (SH1106 128x64)
- 4x Jumper wires
- Micro USB cable for programming

## Required Libraries

### Arduino
- U8glib ([Download](https://github.com/olikraus/u8glib))

### NodeMCU
- Adafruit_GFX
- Adafruit_SH110X
- Wire (built-in)
- SPI (built-in)

## Wiring Connections

### Arduino (I2C)
```
OLED Display → Arduino
VCC → 3.3V/5V
GND → GND
SCL → A5 (SCL)
SDA → A4 (SDA)
```

### NodeMCU (I2C)
```
OLED Display → NodeMCU
VCC → 3.3V
GND → GND
SCL → D1 (GPIO 5)
SDA → D2 (GPIO 4)
```

## Example Sketches

### 1. Arduino Basic Text Display
[`HelloWorld_1.3_inch_OLED_and_arduino.ino`](arduino/HelloWorld_1.3_inch_OLED_and_arduino/HelloWorld_1.3_inch_OLED_and_arduino.ino)
- Simple text display demo using U8glib
- Features:
  - Basic text rendering
  - Font selection options
  - Screen rotation support
  - Contrast control
- Default I2C Address: 0x3C

### 2. NodeMCU Graphics Demo
[`1.3_inch_oled_nodemcu.ino`](nodemcu/1.3_inch_oled_nodemcu/1.3_inch_oled_nodemcu.ino)
- Comprehensive graphics demonstration
- Features:
  - Pixel drawing
  - Line patterns
  - Rectangle/circle shapes
  - Triangle rendering
  - Text display
  - Bitmap graphics
  - Animation effects
- Uses Adafruit SH110X library
- Default I2C Address: 0x3C

## Display Configuration

### I2C Address Settings
```cpp
// For NodeMCU
#define i2c_Address 0x3c  // Default address (most common)
//#define i2c_Address 0x3d // Alternative address

// For Arduino
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // Default I2C
```

### Display Parameters
```cpp
#define SCREEN_WIDTH 128   // Display width in pixels
#define SCREEN_HEIGHT 64   // Display height in pixels
#define OLED_RESET -1     // Reset pin (or -1 if sharing Arduino reset)
```

## Troubleshooting Guide

### No Display Output
1. Verify I2C address (try both 0x3C and 0x3D)
2. Check power connections (3.3V/5V)
3. Confirm I2C pins are correct
4. Verify library installation
5. Check I2C cable quality

### Display Issues
1. Verify correct display driver selection
2. Check display dimensions
3. Try adjusting contrast
4. Ensure proper power supply
5. Check for loose connections

## Reference Materials
- [`Arduino Wiring Diagram`](arduino/oled_schematic_diagram.png)
- [`NodeMCU Connection Diagram`](nodemcu/ESP8266%20AND%201.3%20INCH%20OLED%20CONNECTION.png)

## Additional Resources
- [U8glib Wiki](https://github.com/olikraus/u8glib/wiki)
- [Adafruit SH110X Guide](https://learn.adafruit.com/adafruit-128x64-oled-featherwing)
- [More tutorials at faranux.com](https://faranux.com)

## License
This project is open-source and uses libraries with their respective licenses.
Source: faranux.com