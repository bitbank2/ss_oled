ss_oled (Small Simple OLED library)<br>
Project started 1/15/2017<br>
Copyright (c) 2017-2019 BitBank Software, Inc.<br>
Written by Larry Bank<br>
bitbank@pobox.com<br>
<br>
![ss_oled](/demo.jpg?raw=true "ss_oled")
<br>
The purpose of this code is to easily control SH1106/SSD1306 OLED
displays using a minimum of FLASH and RAM. The displays can be connected to
the traditional I2C bus or you can use any 2 GPIO pins to define a virtual
I2C bus. On AVR microcontrollers, there is an optimized option to speed up
access to the GPIO pins to allow speeds which match or exceed normal I2C
speeds. The pins are numbered with the Port letter as the first digit followed
by the bit number. For example, To use bit 0 of Port B, you would reference
pin number 0xb0. Includes the unique feature that the init function automatically
detects the display address (0x3C or 0x3D) and the controller type (SSD1306 or
SH1106).<br>

Features:<br>
---------<br>
- Automatically detects the display address and type (I2C only)
- Supports 96x16, 64x32, 128x32, 128x64 and 132x64 (SH1106) display sizes<br>
- Drive displays from I2C, SPI or any 2 GPIO pins (virtual I2C)
- 3 sizes of fixed fonts (6x8, 8x8, 16x16/16x32)<br>
- a function to load a Windows BMP file<br>
- Pixel drawing on SH1106 without needing backing RAM<br>
- Optimized Bresenham line drawing<br>
- Optional backing RAM for drawing pixels for systems with enough RAM<br>
- Light enough to run on an ATtiny85<br> 
<br>
This code depends on the BitBang_I2C library. You can download it here:<br>
<br>
https://github.com/bitbank2/BitBang_I2C
<br>

If you find this code useful, please consider buying me a cup of coffee

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=SR4F44J2UR8S4)

