//
// Small Simple OLED library demo
//
// Demonstrates how to initialize and use a few functions of the ss_oled library
// If your MCU has enough RAM, enable the backbuffer to see a demonstration
// of the speed difference between drawing directly on the display versus
// deferred rendering, followed by a "dump" of the memory to the display
//
#include <ss_oled.h>

// if your system doesn't have enough RAM for a back buffer, comment out
// this line (e.g. ATtiny85)
#define USE_BACKBUFFER

#ifdef USE_BACKBUFFER
static uint8_t ucBackBuffer[1024];
#else
static uint8_t *ucBackBuffer = NULL;
#endif

// Use -1 for the Wire library default pins
// or specify the pin numbers to use with the Wire library or bit banging on any GPIO pins
// These are the pin numbers for the M5Stack Atom default I2C
#define SDA_PIN 21
#define SCL_PIN 22
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
#define USE_HW_I2C 0

// Change these if you're using a different OLED display
#define MY_OLED OLED_128x64
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
//#define MY_OLED OLED_64x32
//#define OLED_WIDTH 64
//#define OLED_HEIGHT 32

SSOLED ssoled;

void setup() {
int rc;
// The I2C SDA/SCL pins set to -1 means to use the default Wire library
// If pins were specified, they would be bit-banged in software
// This isn't inferior to hw I2C and in fact allows you to go faster on certain CPUs
// The reset pin is optional and I've only seen it needed on larger OLEDs (2.4")
//    that can be configured as either SPI or I2C
//
// oledInit(SSOLED *, type, oled_addr, rotate180, invert, bWire, SDA_PIN, SCL_PIN, RESET_PIN, speed)

rc = oledInit(&ssoled, MY_OLED, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 400000L); // use standard I2C bus at 400Khz
  if (rc != OLED_NOT_FOUND)
  {
    char *msgs[] = {(char *)"SSD1306 @ 0x3C", (char *)"SSD1306 @ 0x3D",(char *)"SH1106 @ 0x3C",(char *)"SH1106 @ 0x3D",(char *)"SH1107 @ 0x3C",(char *)"SH1107 @ 0x3D"};
    oledFill(&ssoled, 0, 1);
    oledWriteString(&ssoled, 0,0,0,msgs[rc], FONT_NORMAL, 0, 1);
    oledSetBackBuffer(&ssoled, ucBackBuffer);
    delay(2000);
  }
} /* setup() */

void loop() {
  // put your main code here, to run repeatedly:
int i, x, y;
char szTemp[32];
unsigned long ms;

  oledFill(&ssoled, 0x0, 1);
  oledWriteString(&ssoled, 0,16,0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"Written by Larry Bank", FONT_SMALL, 1, 1);
  oledWriteString(&ssoled, 0,0,3,(char *)"**Demo**", FONT_LARGE, 0, 1);
  delay(2000);
  
 // Pixel and line functions won't work without a back buffer
#ifdef USE_BACKBUFFER
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0,0,0,(char *)"Backbuffer Test", FONT_NORMAL,0,1);
  oledWriteString(&ssoled, 0,0,1,(char *)"3000 Random dots", FONT_NORMAL,0,1);
  delay(2000);
  oledFill(&ssoled, 0,1);
  ms = millis();
  for (i=0; i<3000; i++)
  {
    x = random(OLED_WIDTH);
    y = random(OLED_HEIGHT);
    oledSetPixel(&ssoled, x, y, 1, 1);
  }
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(&ssoled, 0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"Without backbuffer", FONT_SMALL,0,1);
  delay(2000);
  oledFill(&ssoled, 0,1);
  ms = millis();
  for (i=0; i<3000; i++)
  {
    x = random(OLED_WIDTH);
    y = random(OLED_HEIGHT);
    oledSetPixel(&ssoled, x, y, 1, 0);
  }
  oledDumpBuffer(&ssoled, NULL);
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(&ssoled, 0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"With backbuffer", FONT_SMALL,0,1);
  delay(2000);
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0,0,0,(char *)"Backbuffer Test", FONT_NORMAL,0,1);
  oledWriteString(&ssoled, 0,0,1,(char *)"96 lines", FONT_NORMAL,0,1);
  delay(2000);
  ms = millis();
  for (x=0; x<OLED_WIDTH-1; x+=2)
  {
    oledDrawLine(&ssoled, x, 0, OLED_WIDTH-x, OLED_HEIGHT-1, 1);
  }
  for (y=0; y<OLED_HEIGHT-1; y+=2)
  {
    oledDrawLine(&ssoled, OLED_WIDTH-1,y, 0,OLED_HEIGHT-1-y, 1);
  }
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(&ssoled, 0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"Without backbuffer", FONT_SMALL,0,1);
  delay(2000);
  oledFill(&ssoled, 0,1);
  ms = millis();
  for (x=0; x<OLED_WIDTH-1; x+=2)
  {
    oledDrawLine(&ssoled, x, 0, OLED_WIDTH-1-x, OLED_HEIGHT-1, 0);
  }
  for (y=0; y<OLED_HEIGHT-1; y+=2)
  {
    oledDrawLine(&ssoled, OLED_WIDTH-1,y, 0,OLED_HEIGHT-1-y, 0);
  }
  oledDumpBuffer(&ssoled, ucBackBuffer);
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(&ssoled, 0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"With backbuffer", FONT_SMALL,0,1);
  delay(2000);
#endif
} /* loop() */
