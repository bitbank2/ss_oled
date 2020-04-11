//
// oled test program
// Written by Larry Bank
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "ss_oled.h"

SSOLED ssoled; // data structure for OLED object
unsigned char ucBackBuf[1024];

int millis()
{
int iTime;
struct timespec res;

    clock_gettime(CLOCK_MONOTONIC, &res);
    iTime = 1000*res.tv_sec + res.tv_nsec/1000000;

    return iTime;
} /* millis() */

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void SpeedTest(void)
{
int i, x, y;
char szTemp[32];
unsigned long ms;

  oledFill(&ssoled, 0x0, 1);
  oledWriteString(&ssoled, 0,16,0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"Written by Larry Bank", FONT_SMALL, 1, 1);
  oledWriteString(&ssoled, 0,0,3,(char *)"**Demo**", FONT_LARGE, 0, 1);
  usleep(2000000);
  
 // Pixel and line functions won't work without a back buffer
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0,0,0,(char *)"Backbuffer Test", FONT_NORMAL,0,1);
  oledWriteString(&ssoled, 0,0,1,(char *)"3000 Random dots", FONT_NORMAL,0,1);
  usleep(2000000);
  oledFill(&ssoled, 0,1);
  ms = millis();
  for (i=0; i<3000; i++)
  {
    x = random() & (OLED_WIDTH-1);
    y = random() & (OLED_HEIGHT-1);
    oledSetPixel(&ssoled, x, y, 1, 1);
  }
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(&ssoled, 0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"Without backbuffer", FONT_SMALL,0,1);
  usleep(2000000);
  oledFill(&ssoled, 0,1);
  ms = millis();
  for (i=0; i<3000; i++)
  {
    x = random() & (OLED_WIDTH-1);
    y = random() & (OLED_HEIGHT-1);
    oledSetPixel(&ssoled, x, y, 1, 0);
  }
  oledDumpBuffer(&ssoled, NULL);
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(&ssoled, 0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"With backbuffer", FONT_SMALL,0,1);
  usleep(2000000);
  oledFill(&ssoled, 0, 1);
  oledWriteString(&ssoled, 0,0,0,(char *)"Backbuffer Test", FONT_NORMAL,0,1);
  oledWriteString(&ssoled, 0,0,1,(char *)"96 lines", FONT_NORMAL,0,1);
  usleep(2000000);
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
  usleep(2000000);
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
  oledDumpBuffer(&ssoled, NULL);
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(&ssoled, 0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(&ssoled, 0,0,1,(char *)"With backbuffer", FONT_SMALL,0,1);
  usleep(2000000);
  oledFill(&ssoled, 0,1);
  oledWriteString(&ssoled,0,0,0,(char *)"Fill Test", FONT_NORMAL, 0, 1);
  ms = millis();
  for (x=0; x<50; x++)
  {
    oledFill(&ssoled, 0, 1);
    oledFill(&ssoled, 0xff, 1);
  }
  ms = millis() - ms;
  oledWriteString(&ssoled,0,0,0,(char *)"Fill rate", FONT_NORMAL, 0, 1);
  sprintf(szTemp, "%d FPS", (int)(100000 / ms));
  oledWriteString(&ssoled,0,0,1,szTemp, FONT_NORMAL, 0, 1);
  
} /* SpeedTest() */
int main(int argc, char *argv[])
{
int i, iChannel;
int iOLEDAddr = -1; // typical address; it can also be 0x3d
int iOLEDType = OLED_128x64; // Change this for your specific display
int bFlip = 0, bInvert = 0;

	i = -1;
	iChannel = -1;
	while (i != 0 && iChannel < 2) // try I2C channel 0 through 2
	{
		iChannel++;
		i=oledInit(&ssoled, iOLEDType, iOLEDAddr, bFlip, bInvert, 1, iChannel, iOLEDAddr, -1, 400000);
	}
	if (i != OLED_NOT_FOUND)
	{
                oledSetBackBuffer(&ssoled, ucBackBuf);
		SpeedTest();
		printf("Press ENTER to quit\n");
		getchar();
		oledPower(&ssoled, 0);
	}
	else
	{
		printf("Unable to initialize I2C bus 0-2, please check your connections and verify the device address by typing 'i2cdetect -y <channel>\n");
	}
   return 0;
} /* main() */
