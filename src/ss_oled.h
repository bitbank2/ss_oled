#define FONT_NORMAL 0
#define FONT_LARGE 1
#define FONT_SMALL 2

// OLED type for init function
enum {
  OLED_128x32 = 1,
  OLED_128x64,
  OLED_132x64,
  OLED_64x32,
  OLED_96x16,
  OLED_72x40
};

// Return value from oledInit()
enum {
  OLED_NOT_FOUND = -1, // no display found
  OLED_SSD1306_3C,  // SSD1306 found at 0x3C
  OLED_SSD1306_3D,  // SSD1306 found at 0x3D
  OLED_SH1106_3C,   // SH1106 found at 0x3C
  OLED_SH1106_3D,   // SH1106 found at 0x3D
};
//
// Initializes the OLED controller into "page mode" on I2C
// If SDAPin and SCLPin are not -1, then bit bang I2C on those pins
// Otherwise use the Wire library
//
int oledInit(int iType, int bFlip, int bInvert, int iSDAPin, int iSCLPin, int32_t iSpeed);
//
// Initialize an SPI version of the display
//
void oledSPIInit(int iType, int iDC, int iCS, int iReset, int bFlip, int bInvert, int32_t iSpeed);

//
// Sends a command to turn off the OLED display
//
void oledShutdown();
//
// Sets the brightness (0=off, 255=brightest)
//
void oledSetContrast(unsigned char ucContrast);
//
// Load a 128x64 1-bpp Windows bitmap
// Pass the pointer to the beginning of the BMP file
// First pass version assumes a full screen bitmap
//
int oledLoadBMP(byte *pBMP);
//
// Power up/down the display
// useful for low power situations
//
void oledPower(byte bOn);
//
// Draw a string of normal (8x8), small (6x8) or large (16x32) characters
// At the given col+row
//
int oledWriteString(int x, int y, char *szMsg, int iSize, int bInvert);
//
// Fill the frame buffer with a byte pattern
// e.g. all off (0x00) or all on (0xff)
//
void oledFill(unsigned char ucData);
//
// Set (or clear) an individual pixel
// The local copy of the frame buffer is used to avoid
// reading data from the display controller
// (which isn't possible in most configurations)
// This function needs the USE_BACKBUFFER macro to be defined
// otherwise, new pixels will erase old pixels within the same byte
//
int oledSetPixel(int x, int y, unsigned char ucColor);
//
// Dump an entire custom buffer to the display
// useful for custom animation effects
//
void oledDumpBuffer(uint8_t *pBuffer);
//
// Draw a line between 2 points
//
void oledDrawLine(int x1, int y1, int x2, int y2);
//
// Get the buffer pointer for direct manipulation of the pixels
//
uint8_t * oledGetBuffer(void);

