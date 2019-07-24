//
// Small Simple OLED library demo
//
#include <ss_oled.h>

void setup() {
int rc;
  // put your setup code here, to run once:
rc = oledInit(OLED_128x64, 0, 0, -1, -1,400000L); // use standard I2C bus at 400Khz
//rc = oledInit(OLED_128x64, 0, 0, 0xb0, 0xb2, 400000L); // for ATtiny85, use P0 as SDA and P2 as SCL
  if (rc != OLED_NOT_FOUND)
  {
    char *msgs[] = {"SSD1306 @ 0x3C", "SSD1306 @ 0x3D","SH1106 @ 0x3C","SH1106 @ 0x3D"};
    oledFill(0, 1);
    oledWriteString(0,0,0,msgs[rc], FONT_NORMAL, 0, 1);
    delay(2000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
int i, x, y;
char szTemp[32];

  oledFill(0x0, 1);
  oledWriteString(0,16,0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
  oledWriteString(0,0,1,(char *)"Written by Larry Bank", FONT_SMALL, 1, 1);
  oledWriteString(0,0,3,(char *)"**Demo**", FONT_LARGE, 0, 1);
  delay(2000);
  oledFill(0, 1);
  for (i=0; i<3000; i++)
  {
    x = random(128);
    y = random(64);
    oledSetPixel(x, y, 1, 1);
  }
  delay(2000);
//
// By default, the line drawing function is disabled on AVR since it requires a backing buffer (1K RAM)
// Which is usually a large % on most of the AVRs (Arduino UNO only has 2K RAM total)
// To enable this functionality, define USE_BACKBUFFER at the beginning of ss_oled.cpp
//
#ifndef __AVR__
  oledFill(0, 1);
  for (x=0; x<127; x+=2)
  {
    oledDrawLine(x, 0, 127-x, 63, 1);
  }
  for (y=0; y<63; y+=2)
  {
    oledDrawLine(127,y, 0,63-y, 1);
  }
  delay(2000);
#endif // !__AVR__
} /* main() */
