//
// Small Simple OLED library demo
//
#include <ss_oled.h>

void setup() {
  // put your setup code here, to run once:
oledInit(0x3c, OLED_128x64, 0, 0, -1, -1,400000L); // use standard I2C bus at 400Khz
//oledInit(0x3c, OLED_128x64, 0, 0, 0xb0, 0xb2, 400000L); // for ATtiny85, use P0 as SDA and P2 as SCL
}

void loop() {
  // put your main code here, to run repeatedly:
int i, x, y;
char szTemp[32];

oledFill(0x0);
  oledWriteString(16,0,"ss_oled Demo", FONT_NORMAL, 0);
  oledWriteString(0,1,"Written by Larry Bank", FONT_SMALL, 1);
  oledWriteString(0,3,"**Demo**", FONT_LARGE, 0);
  delay(2000);
  oledFill(0);
  for (i=0; i<3000; i++)
  {
    x = random(128);
    y = random(64);
    oledSetPixel(x, y, 1);
  }
  delay(2000);
  oledFill(0);
  for (x=0; x<127; x+=2)
  {
    oledDrawLine(x, 0, 127-x, 63);
  }
  for (y=0; y<63; y+=2)
  {
    oledDrawLine(127,y, 0,63-y);
  }
  delay(3000);
} /* main() */
