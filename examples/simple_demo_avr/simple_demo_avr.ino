//
// Small Simple OLED library demo for AVR platform,
// without line drawing function (saving of 1K RAM)
//
#include <ss_oled.h>

void setup()
{
    int rc;
    rc = oledInit(OLED_128x64, 0, 0, -1, -1, 400000L);       // Standard HW I2C bus at 400Khz

    if (rc != OLED_NOT_FOUND)
    {
        char *msgs[] =
        {
          "SSD1306 @ 0x3C",
          "SSD1306 @ 0x3D",
          "SH1106 @ 0x3C",
          "SH1106 @ 0x3D"
        };

        oledFill(0, 1);
        oledWriteString(0, 0, 0, (char *)"OLED found:", FONT_NORMAL, 0, 1);
        oledWriteString(0, 10, 2, msgs[rc], FONT_NORMAL, 0, 1);
        delay(3000);
    }
}

void loop()
{
    int i, x, y;

    oledFill(0, 1);
    oledWriteString(0, 16, 0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
    oledWriteString(0, 0, 1,(char *)"Written by Larry Bank", FONT_SMALL, 1, 1);
    oledWriteString(0, 0, 3,(char *)"**Demo**", FONT_STRETCHED, 0, 1);
    oledWriteString(0, 9, 6,(char *)"for AVR", FONT_STRETCHED, 0, 1);

    delay(2000);
    oledFill(0, 1);

    for (i = 0; i < 1000; i++)
    {
        x = random(128);
        y = random(64);
        oledSetPixel(x, y, 1, 1);
    }

    delay(2000);
}
