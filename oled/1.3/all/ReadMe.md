# 1.3" OLED Display Examples for Arduino and NodeMCU
By Faranux Electronics Team

This repository contains examples for interfacing with 1.3" OLED displays (SH1106 128x64) using Arduino and NodeMCU boards. Three different approaches are provided using popular display libraries:

## Library Options

1. **U8g2 Library Example**
   - Simple and lightweight
   - Hardware I2C support
   - Basic text rendering
   - See [Example-Code-Using-U8g2-Library.ino](Example-Code-Using-U8g2-Library/Example-Code-Using-U8g2-Library.ino)

2. **Adafruit SH110X Library**
   - Rich graphics features
   - Compatible with Adafruit GFX
   - Easy to use API
   - See [Example-Code-Using-Adafruit_SH110X-Library.ino](Example-Code-Using-Adafruit_SH110X-Library/Example-Code-Using-Adafruit_SH110X-Library.ino)

3. **U8glib (Legacy)**
   - Original U8g library
   - Basic graphics support
   - See [HelloWorld_1.3_inch_OLED_and_arduino.ino](arduino/HelloWorld_1.3_inch_OLED_and_arduino/HelloWorld_1.3_inch_OLED_and_arduino.ino)

## Hardware Connections

### Arduino
```
OLED → Arduino
VCC → 3.3V/5V
GND → GND
SCL → A5
SDA → A4
```

### NodeMCU
```
OLED → NodeMCU
VCC → 3.3V
GND → GND
SCL → D1
SDA → D2
```

## Display Configuration

### I2C Address
```cpp
#define I2C_ADDRESS 0x3C  // Most common
//#define I2C_ADDRESS 0x3D // Alternative
```

### Display Parameters
```cpp
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin not used
```

## Example Features

- Text display
- Graphics primitives
- Animations
- Bitmap display
- Different fonts
- Screen rotation
- Contrast control

## Reference Materials

- [Arduino Wiring Diagram](arduino/oled_schematic_diagram.png)
- [NodeMCU Connection Diagram](nodemcu/ESP8266%20AND%201.3%20INCH%20OLED%20CONNECTION.png)

## Required Libraries

- U8g2lib
- Adafruit_GFX
- Adafruit_SH110X
- Wire (built-in)

## Troubleshooting

If display shows nothing:
1. Verify I2C address (try both 0x3C and 0x3D)
2. Check power connections
3. Verify I2C pins
4. Confirm library installation

## License
Open source - See individual library licenses for details.

Source: [faranux.com](https://faranux.com)