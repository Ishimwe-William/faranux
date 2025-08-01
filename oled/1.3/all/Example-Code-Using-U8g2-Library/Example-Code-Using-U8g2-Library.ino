#include <Wire.h>
#include <U8g2lib.h>

// SH1106 1.3" OLED I2C
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 24, "Hello from Faranux!");
  u8g2.sendBuffer();
  delay(1000);
}
