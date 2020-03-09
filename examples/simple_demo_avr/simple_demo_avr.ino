//
// Small Simple OLED library demo for AVR platform,
// without line drawing function (saving of 1K RAM)
//
#include <ss_oled.h>

SSOLED ssoled;
#define SDA_PIN -1
#define SCL_PIN -1
// no reset pin needed
#define RESET_PIN -1
// let ss_oled find the address of our display
#define OLED_ADDR -1
#define FLIP180 0
#define INVERT 0
// Use the default Wire library
#define USE_HW_I2C 1
void setup()
{
    int rc;
    rc = oledInit(&ssoled, OLED_128x64, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 400000L);       // Standard HW I2C bus at 400Khz

    if (rc != OLED_NOT_FOUND)
    {
        char *msgs[] =
        {
          (char *)"SSD1306 @ 0x3C",
          (char *)"SSD1306 @ 0x3D",
          (char *)"SH1106 @ 0x3C",
          (char *)"SH1106 @ 0x3D"
        };

        oledFill(&ssoled, 0, 1);
        oledWriteString(&ssoled, 0, 0, 0, (char *)"OLED found:", FONT_NORMAL, 0, 1);
        oledWriteString(&ssoled, 0, 10, 2, msgs[rc], FONT_NORMAL, 0, 1);
        delay(3000);
    }
}

void loop()
{
    int i, x, y;

    oledFill(&ssoled, 0, 1);
    oledWriteString(&ssoled, 0, 16, 0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
    oledWriteString(&ssoled, 0, 0, 1,(char *)"Written by Larry Bank", FONT_SMALL, 1, 1);
    oledWriteString(&ssoled, 0, 0, 3,(char *)"**Demo**", FONT_STRETCHED, 0, 1);
    oledWriteString(&ssoled, 0, 9, 6,(char *)"for AVR", FONT_STRETCHED, 0, 1);

    delay(2000);
    oledFill(&ssoled, 0, 1);

    for (i = 0; i < 1000; i++)
    {
        x = random(128);
        y = random(64);
        oledSetPixel(&ssoled, x, y, 1, 1);
    }

    delay(2000);
}
