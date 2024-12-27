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

### 2. Changes Made in User_Setup

### 3. Calibration
With the Touch_Calibration sketch, the min/max values (`TS_MINX`, `TS_MAXX`, `TS_MINY`, `TS_MAXY`) will be available in the serial monitor for direct use in your touchscreen mapping logic.

**Note:** This is tested on `ILI9488_DRIVER`. If you have different type, update the `User_Setup.h` file

