# 3.5" TFT Touch Screen with DOIT ESP32 DEVKIT V1   
### 1. Pin Connection


| Serial number | Label       | 	Pin description                             | ➡️  | ESP32  |
|---------------|-------------|----------------------------------------------|-----|--------|
| 1	            | VCC (VDD)   | 	Power input (3.3v-5v)                       | ➡️  | 3.3V   |
| 2	            | GND	        | I power ground                               | ➡️  | GND    |
| 3	            | CS	         | LCD chip select                              | ➡️  | GPIO15 |
| 4	            | RESET (RST) | 	LCD reset                                   | ➡️  | GPIO4  |
| 5	            | DC	         | LCD bus command/data selection               | ➡️  | GPIO2  |
| 6	            | SDI (MOSI)	 | LCD SPI display bus data input               | ➡️  | GPIO23 |
| 7	            | SCK	        | I LCD SPI display bus clock signal           | ➡️  | GPIO18 |
| 8	            | LED (BL)	   | LCD backlight control (high level lights up) | ➡️  | 3.3V   |
| 9	            | SDO (MISO)	 | LCD SPI display bus data input and output    | ➡️  | GPIO19 |
| 10	           | T CLK	      | Touch panel SPI bus clock signal             | ➡️  | GPIO26 |
| 11	           | T CS	       | Touch panel SPI bus chip select              | ➡️  | GPIO25 |
| 12	           | T DIN	      | Touch panel SPI bus data input               | ➡️  | GPIO33 |
| 13	           | T DO	       | Touch panel SPI bus output                   | ➡️  | GPIO32 |
| 14	           | IRQ (PEN)   | 	Touch panel interrupt IRQ signal            | ➡️  | GPIO35 |

### 2. Library Used
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [XPT2046_Touchscreen](https://github.com/PaulStoffregen/XPT2046_Touchscreen)
### 3. Changes Made in User_Setup.h file of [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library
After adding TFT_eSPI library to your IDE, you will need to make some modifications to User_Setup.h file to make everything work. **In this repository, there is a copy of User_Setup.h with modifications**. The following are some modification made to the file: 
- Defining driver [one to be defined the other ones must be commented out] (line 45-64)
  ```cpp
  // #define ILI9341_DRIVER       // Generic driver for common displays
  ...
  #define ILI9488_DRIVER     // WARNING: Do not connect ILI9488 display SDO to MISO if other devices share the SPI bus (TFT SDO does NOT tristate when CS is high)
  ...
  ```
- Defining the pins that are used to interface with the display here (line 112)
  - Comment out  ESP8266 NodeMCU pins and uncomment ESP32 pins 
  ```cpp
  #define TFT_MISO 19
  #define TFT_MOSI 23
  #define TFT_SCLK 18
  #define TFT_CS   15  // Chip select control pin
  #define TFT_DC    2  // Data Command control pin
  #define TFT_RST   4  // Reset pin (could connect to RST pin)
  //#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST
  ...
  #define TOUCH_CS 21     // Chip select pin (T_CS) of touch screen 
  ...
  ```
- Define the ESP32 SPI port to use (line 374)
  - As we are using Virtual SPI (VSPI) port, we need to uncomment this line
  ```cpp
    #define USE_HSPI_PORT 
  ```
### 4. Calibration
With the Touch_Calibration sketch, the min/max values (`TS_MINX`, `TS_MAXX`, `TS_MINY`, `TS_MAXY`) will be available in the serial monitor for direct use in your touchscreen mapping logic.

In you sketch you will need to replace these values with the one you have got:
```cpp
#define TS_MINX 200
#define TS_MAXX 3700
#define TS_MINY 240
#define TS_MAXY 3800
```
**Note:** This is tested on `ILI9488_DRIVER`. If you have different type, update the `User_Setup.h` file

### 5. On/Off Button Example
The On/Off Button Example is designed to toggle an LED connected to pin 12. However, you might encounter a "flipping" issue, where the touch input does not align with the location of the desired effect on the screen. This issue arises because the raw touchscreen coordinates do not correspond directly to the screen's orientation or dimensions. To resolve this, calibration is required to map the raw touch coordinates accurately to the display area, accounting for any flipping or mismatches.

Here are some key areas you may change in your codes
- Screen dimensions
  ```cpp
  ...
  #define SCREEN_WIDTH 320
  #define SCREEN_HEIGHT 480
  ...
  ```
- Screen rotation
  ```cpp
  touchscreen.setRotation(0);  // Match screen rotation
  ...
  tft.setRotation(0);  // Portrait orientation
  ...
  ```
- Mapping raw touch coordinates to screen coordinates
  ```cpp
  ...
  int touchX = map(p.x, TS_MAXX, TS_MINX, 0, SCREEN_WIDTH);
  int touchY = map(p.y, TS_MINY, TS_MAXY, 0, SCREEN_HEIGHT);
  ...
  ```
