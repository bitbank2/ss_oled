#include <ss_oled.h>

// Arduino Pro Mini
// Pin 8 (0xb0 = PORTB, bit 0)
// Pin 9 (0xb1 = PORTB, bit 1)
#define SDA_PIN 0xb0
#define SCL_PIN 0xb1
#define RESET_PIN -1
int rc;
SSOLED oled;
void setup() {
uint8_t uc[8];
    
  rc = oledInit(&oled, OLED_128x64, 0x3c, 0, 0, 0, SDA_PIN, SCL_PIN, RESET_PIN, 1000000L);
  if (rc != OLED_NOT_FOUND)
  { 
    oledFill(&oled, 0,1);
    oledSetContrast(&oled, 127);
    oledWriteString(&oled, 0,0,0,(char *)"**************** ", FONT_8x8, 0, 1);
    oledWriteString(&oled, 0,4,1,(char *)"BitBank SS_OLED", FONT_8x8, 0, 1);
    oledWriteString(&oled, 0,8,2,(char *)"running on the", FONT_8x8, 0, 1);
    oledWriteString(&oled, 0,8,3,(char *)"SSD1306 128x64", FONT_8x8, 0, 1);
    oledWriteString(&oled, 0,4,4,(char *)"monochrome OLED", FONT_8x8, 0, 1);
    oledWriteString(&oled, 0,24,5,(char *)"Written By", FONT_8x8, 0, 1);
    oledWriteString(&oled, 0,24,6,(char *)"Larry Bank", FONT_8x8, 0, 1);
    oledWriteString(&oled, 0,0,7,(char *)"**************** ", FONT_8x8, 0, 1);
    delay(4000);
  }
}

void loop() {
int i, j;
char szTemp[32];

  oledFill(&oled, 0,1);
  oledWriteString(&oled, 0,0,0,(char *)"Now with 5 font sizes", FONT_6x8, 0, 1);
  oledWriteString(&oled, 0,0,1,(char *)"6x8 8x8 16x16", FONT_8x8, 0, 1);
  oledWriteString(&oled, 0,0,2,(char *)"16x32 and a new", FONT_8x8, 0, 1);
  oledWriteString(&oled, 0,0,3,(char *)"Stretched", FONT_12x16, 0, 1);
  oledWriteString(&oled, 0,0,5,(char *)"from 6x8", FONT_12x16, 0, 1);
  delay(10000);
  
  oledFill(&oled, 0, 1);
  oledSetTextWrap(&oled, 1);
  oledWriteString(&oled, 0,-1,-1,"This is a test of text wrap", FONT_6x8, 0, 1);
  delay(3000);
  oledFill(&oled, 0,1);
//  oledSetTextWrap(0);
  oledWriteString(&oled, 0,-1,-1,"This ", FONT_16x16, 0, 1);
  oledWriteString(&oled, 0,-1,-1,"is a ", FONT_16x16, 0, 1);
  oledWriteString(&oled, 0,-1,-1,"test of text wrap", FONT_16x16, 0, 1);
  delay(3000);
  oledFill(&oled, 0,1);
  oledSetCursor(&oled, 40,4);
  oledWriteString(&oled, 0,-1,-1,"Middle", FONT_6x8,0,1);
  delay(3000);
  if (rc >= OLED_SH1106_3C)          // We can set pixels on the SH1106 without a back buffer
  {
    int x, y;
    for (i=0; i<2500; i++)
    {
      x = random(128);
      y = random(64);
       oledSetPixel(&oled, x, y, 1, 1);
    }
    delay(2000);
  }
#ifndef __AVR__

  for (i=0; i<8; i++)
  {
    sprintf(szTemp, "Line %d", i);
    oledWriteString(&oled, 0,0,i,szTemp, FONT_8x8, 0, 0);
    oledWriteString(&oled, 0,64,i,szTemp, FONT_8x8, 0, 0);
  } // for i
  j = 0; // missing line
  while (1)
  {
    for (i=0; i<8; i++) // smooth scroll 8 lines
    {
//void oledScrollBuffer(int iStartCol, int iEndCol, int iStartRow, int iEndRow, int bUp);
      oledScrollBuffer(&oled, 0,63,0,7,1);
      oledScrollBuffer(&oled, 64,127,0,7,0);
      oledDumpBuffer(&oled, NULL);
//void oledDrawGFX(uint8_t *pSrc, int iSrcCol, int iSrcRow, int iDestCol, int iDestRow, int iWidth, int iHeight, int iSrcPitch);
//      oledDrawGFX(NULL, 0, 0, 0, 0, 64, 7, 0); // left half
//      oledDrawGFX(NULL, 64, 1, 64, 0, 64, 7, 0); // right half 
      delay(40);
    }
    // fill in the missing line which scrolls off
    sprintf(szTemp, "Line %d", j & 7);
    oledWriteString(&oled, 0,0,7,szTemp, FONT_NORMAL, 0, 0);
    sprintf(szTemp, "Line %d", 7-(j & 7));
    oledWriteString(&oled, 0,64,0,szTemp, FONT_NORMAL, 0, 0);
    j++;
  }
#else
  for (i=0; i<256; i++)
  {
    oledWriteString(&oled, i, 0,0,(char *)"This is a scrolling text demo showing how a long string can be displayed ", FONT_NORMAL, 0, 1);
  }
#endif // __AVR__
} // loop
