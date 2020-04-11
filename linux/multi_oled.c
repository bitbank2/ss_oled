//
// multi oled test program
// Written by Larry Bank
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ss_oled.h"

SSOLED ssoled[2]; // data structure for 2 OLED objects
unsigned char ucBackBuf[1024];

int main(int argc, char *argv[])
{
int i;
int iOLEDAddr = -1; // typical address; it can also be 0x3d
int iOLEDType0 = OLED_128x64; // Change this for your specific display
int iOLEDType1 = OLED_64x32;
int bFlip = 0, bInvert = 0, bWire = 1;

// For hardware I2C on the RPI, the clock rate is fixed and set in the
// /boot/config.txt file, so we pass 0 for the bus speed
		i=oledInit(&ssoled[0], iOLEDType0, iOLEDAddr, bFlip, bInvert, bWire, 1, -1, -1, 0); // initialize 128x64 oled on I2C channel 1
	if (i != OLED_NOT_FOUND)
	{
                char *msgs[] = {(char *)"SSD1306 @ 0x3C", (char *)"SSD1306 @ 0x3D",(char *)"SH1106 @ 0x3C",(char *)"SH1106 @ 0x3D"};
		printf("Successfully opened I2C bus 1\n");
                oledSetBackBuffer(&ssoled[0], ucBackBuf);
		oledFill(&ssoled[0], 0,1); // fill with black
                oledWriteString(&ssoled[0], 0,0,0, msgs[i], FONT_NORMAL,0,1);
		oledWriteString(&ssoled[0], 0,0,1,"SS_OLED Library!",FONT_NORMAL,0,1);
		oledWriteString(&ssoled[0], 0,3,2,"BIG!",FONT_LARGE,0,1);
		oledWriteString(&ssoled[0], 0,0,5,"Small", FONT_SMALL,0,1);
		for (i=0; i<64; i++)
		{
			oledSetPixel(&ssoled[0], i, 16+i, 1, 1);
			oledSetPixel(&ssoled[0], 127-i, 16+i, 1, 1);
		}
                oledInit(&ssoled[1], iOLEDType1, iOLEDAddr, bFlip, bInvert, bWire, 6, -1, -1, 0); // initialize the 64x32 oled on I2C channel 6
		oledFill(&ssoled[1], 0, 1);
		oledWriteString(&ssoled[1], 0,0,0,"OLED on", FONT_NORMAL, 0, 1);
                oledWriteString(&ssoled[1], 0,0,1,"I2C ch 6", FONT_NORMAL, 0, 1);
		printf("Press ENTER to quit\n");
		getchar();
		oledPower(&ssoled[0], 0); // turn off both displays
		oledPower(&ssoled[1], 0);
	}
	else
	{
		printf("Unable to initialize I2C bus 0-2, please check your connections and verify the device address by typing 'i2cdetect -y <channel>\n");
	}
   return 0;
} /* main() */
