//
// Small Simple OLED library multi-display demo
//
// Demonstrates how to initialize and use multiple displays
//
#include <ss_oled.h>

// Use -1 for the Wire library default pins
// or specify the pin numbers to use with the Wire library or bit banging on any GPIO pins
// These are reversed because I did straight-through wiring for my SSD1306
// and it has the 4-pin header as GND,VCC,SCL,SDA, but the GROVE connector is
// GND,VCC,SDA,SCL
#define GROVE_SDA_PIN 32
#define GROVE_SCL_PIN 26
// Set this to -1 to disable or the GPIO pin number connected to the reset
// line of your display if it requires an external reset
#define RESET_PIN -1
// let ss_oled figure out the display address
#define OLED_ADDR -1
// don't rotate the display
#define FLIP180 0
// don't invert the display
#define INVERT 0
// Bit-Bang the I2C bus
#define USE_HW_I2C 1

// Change this if you're using different OLED displays
#define MY_OLED OLED_128x64
uint8_t ucBackBuffer[1024];

// The SSOLED structure. Each structure is about 56 bytes
// There is no limit to the number of simultaneous displays which can be controlled by ss_oled 
SSOLED ssoled;

void setup() {
char *msgs[] = {(char *)"SSD1306 @ 0x3C", (char *)"SSD1306 @ 0x3D",(char *)"SH1106 @ 0x3C",(char *)"SH1106 @ 0x3D"};
int rc;
// The I2C SDA/SCL pins set to -1 means to use the default Wire library
// If pins were specified, they would be bit-banged in software
// This isn't inferior to hw I2C and in fact allows you to go faster on certain CPUs
// The reset pin is optional and I've only seen it needed on larger OLEDs (2.4")
//    that can be configured as either SPI or I2C
//
// oledInit(SSOLED *, type, oled_addr, rotate180, invert, bWire, SDA_PIN, SCL_PIN, RESET_PIN, speed)

rc = oledInit(&ssoled, MY_OLED, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, GROVE_SDA_PIN, GROVE_SCL_PIN, RESET_PIN, 800000L); // use standard I2C bus at 400Khz
  if (rc != OLED_NOT_FOUND)
  {
    oledFill(&ssoled, 0, 1);
    oledWriteString(&ssoled, 0,0,0,msgs[rc], FONT_NORMAL, 0, 1);
    delay(2000);
  }
  else
  {
    while (1) {};
  }
  oledSetBackBuffer(&ssoled, ucBackBuffer);
} /* setup() */

#define DRAW_ELLIPSES
#define DRAW_RECTS

void loop() {
  int i, x, y, x2, y2, r1, r2;
  uint8_t ucColor;

#ifdef DRAW_ELLIPSES
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0, 0, 0, (char *)"Ellipses", FONT_NORMAL, 0, 1);
  delay(2000);
  oledFill(&ssoled, 0, 1);
  for (i=0; i<100; i++)
  {
    x = random(128);
    y = random(64);
    r1 = random(64);
    r2 = random(32);
    oledEllipse(&ssoled, x, y, r1, r2, 1, 0);
    oledDumpBuffer(&ssoled, NULL);    
  }
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0, 0, 0, (char *)"Filled Ellipses", FONT_NORMAL, 0, 1);
  delay(2000);
  oledFill(&ssoled, 0, 1);
  for (i=0; i<100; i++)
  {
    x = random(128);
    y = random(64);
    r1 = random(64);
    r2 = random(32);
    ucColor = random(2);
    oledEllipse(&ssoled, x, y, r1, r2, ucColor, 1);
    oledDumpBuffer(&ssoled, NULL);
  }
#endif // DRAW_ELLIPSES

#ifdef DRAW_RECTS
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0, 0, 0, (char *)"Rectangles", FONT_NORMAL, 0, 1);
  delay(2000);
  oledFill(&ssoled, 0, 1);
  for (i=0; i<100; i++)
  {
    x = random(128);
    y = random(64);
    x2 = random(128);
    y2 = random(64);
    oledRectangle(&ssoled, x, y, x2, y2, 1, 0);
    oledDumpBuffer(&ssoled, NULL);
  }
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0, 0, 0, (char *)"Filled Rects", FONT_NORMAL, 0, 1);
  delay(2000);
  oledFill(&ssoled, 0, 1);
  for (i=0; i<100; i++)
  {
    x = random(128);
    y = random(64);
    x2 = random(128);
    y2 = random(64);
    ucColor = random(2);
    oledRectangle(&ssoled, x, y, x2, y2, ucColor, 1);
    oledDumpBuffer(&ssoled, NULL);
  }
#endif // DRAW_RECTS

  delay(4000);
} /* loop() */
