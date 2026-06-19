/* Modded to work with Pro Micro 32U4 by Lucas Rountree, all credit to DIYables etc
 * Changes: Added custom spi settings variable to spi transaction function and specific 32u4 variables and values
 */

#include "DIYables_TFT_Round_Modded.h"
#include <Arduino.h>
#include <SPI.h>

// Command codes:
#define COL_ADDR_SET        0x2A
#define ROW_ADDR_SET        0x2B
#define MEM_WR              0x2C
#define COLOR_MODE          0x3A
#define COLOR_MODE__12_BIT  0x03
#define COLOR_MODE__16_BIT  0x05
#define COLOR_MODE__18_BIT  0x06
#define MEM_WR_CONT         0x3C

DIYables_TFT_GC9A01_Round::DIYables_TFT_GC9A01_Round(uint8_t resPin, uint8_t dcPin, uint8_t csPin)
    : Adafruit_GFX(240, 240), _res(resPin), _dc(dcPin), _cs(csPin), _rotation(0) {} // Default rotation 0

inline void DIYables_TFT_GC9A01_Round::setReset(uint8_t val) {
    digitalWrite(_res, val);
}

inline void DIYables_TFT_GC9A01_Round::setDataCommand(uint8_t val) {
    digitalWrite(_dc, val);
}

inline void DIYables_TFT_GC9A01_Round::setChipSelect(uint8_t val) {
    digitalWrite(_cs, val);
}

inline void DIYables_TFT_GC9A01_Round::delayMs(uint16_t ms) {
    delay(ms);
}

void DIYables_TFT_GC9A01_Round::spiTx(uint8_t *data, size_t len) {
    SPI.transfer(data, len);
}

// Open a raw SPI transaction — must be paired with spiEnd()
void DIYables_TFT_GC9A01_Round::spiBegin() {
    SPI.beginTransaction(SPISettings(160000000, MSBFIRST, SPI_MODE1));
    setChipSelect(0);
}

// Close a raw SPI transaction — must be paired with spiBegin()
void DIYables_TFT_GC9A01_Round::spiEnd() {
    setChipSelect(1);
    SPI.endTransaction();
}

// Raw command send — must be called within spiBegin()/spiEnd()
void DIYables_TFT_GC9A01_Round::writeCommand(uint8_t cmd) {
    setDataCommand(0);
    SPI.transfer(cmd);
    setDataCommand(1);
}

// Raw data send — must be called within spiBegin()/spiEnd()
void DIYables_TFT_GC9A01_Round::writeData(uint8_t *data, size_t len) {
    // DC is already HIGH (data mode)
    SPI.transfer(data, len);
}

// Set column+row window and issue 0x2C — must be within spiBegin()/spiEnd()
void DIYables_TFT_GC9A01_Round::setAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    uint8_t buf[4];
    writeCommand(0x2A);
    buf[0] = x0 >> 8; buf[1] = x0 & 0xFF;
    buf[2] = x1 >> 8; buf[3] = x1 & 0xFF;
    writeData(buf, 4);
    writeCommand(0x2B);
    buf[0] = y0 >> 8; buf[1] = y0 & 0xFF;
    buf[2] = y1 >> 8; buf[3] = y1 & 0xFF;
    writeData(buf, 4);
    writeCommand(0x2C);
}

// Fill count pixels with the same color — must be within spiBegin()/spiEnd()
void DIYables_TFT_GC9A01_Round::fillColor(uint16_t color, uint32_t count) {
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;
    while (count--) {
        SPI.transfer(hi);
        SPI.transfer(lo);
    }
}

// Send RGB565 RAM pixel data — must be within spiBegin()/spiEnd()
void DIYables_TFT_GC9A01_Round::pushColorData(uint16_t *data, uint32_t len) {
    while (len--) {
        uint16_t c = *data++;
        SPI.transfer(c >> 8);
        SPI.transfer(c & 0xFF);
    }
}

// Send RGB565 PROGMEM pixel data — must be within spiBegin()/spiEnd()
void DIYables_TFT_GC9A01_Round::pushColorDataPGM(const uint16_t *data, uint32_t len) {
    while (len--) {
        uint16_t c = pgm_read_word(data++);
        SPI.transfer(c >> 8);
        SPI.transfer(c & 0xFF);
    }
}

bool DIYables_TFT_GC9A01_Round::isPixelInsideCircle(int x, int y) {
  int centerX = 120;
  int centerY = 120;
  int radius = 120;

  // Calculate squared distance from the center
  int dx = x - centerX;
  int dy = y - centerY;
  int distanceSquared = dx * dx + dy * dy;

  // Compare squared distance with squared radius
  return distanceSquared <= (radius * radius);
}


inline void DIYables_TFT_GC9A01_Round::writeByte(uint8_t val) {
    SPI.transfer(val);
}

void DIYables_TFT_GC9A01_Round::begin() {
	pinMode(_res, OUTPUT);
    pinMode(_dc, OUTPUT);
    pinMode(_cs, OUTPUT);
    SPI.begin();

    setChipSelect(1);
    delayMs(5);
    setReset(0);
    delayMs(10);
    setReset(1);
    delayMs(120);

    // Apply GFX rotation state before drawing
    Adafruit_GFX::setRotation(_rotation);

    /* Initial Sequence — wrapped in a single SPI transaction */
    spiBegin();
    
    writeCommand(0xEF);
    
    writeCommand(0xEB);
    writeByte(0x14);
    
    writeCommand(0xFE);
    writeCommand(0xEF);
    
    writeCommand(0xEB);
    writeByte(0x14);
    
    writeCommand(0x84);
    writeByte(0x40);
    
    writeCommand(0x85);
    writeByte(0xFF);
    
    writeCommand(0x86);
    writeByte(0xFF);
    
    writeCommand(0x87);
    writeByte(0xFF);
    
    writeCommand(0x88);
    writeByte(0x0A);
    
    writeCommand(0x89);
    writeByte(0x21);
    
    writeCommand(0x8A);
    writeByte(0x00);
    
    writeCommand(0x8B);
    writeByte(0x80);
    
    writeCommand(0x8C);
    writeByte(0x01);
    
    writeCommand(0x8D);
    writeByte(0x01);
    
    writeCommand(0x8E);
    writeByte(0xFF);
    
    writeCommand(0x8F);
    writeByte(0xFF);
    
    writeCommand(0xB6);
    writeByte(0x00);
    writeByte(0x00);
    
    // Inline MADCTL for rotation (avoids nested spiBegin/spiEnd)
    writeCommand(0x36);
    switch (_rotation & 0x03) {
        case 0: writeByte(0x48); break;
        case 1: writeByte(0xE8); break;
        case 2: writeByte(0x88); break;
        case 3: writeByte(0x28); break;
    }
    
    writeCommand(COLOR_MODE);
    writeByte(COLOR_MODE__16_BIT); // <-- Change to 16-bit color mode
    
    writeCommand(0x90);
    writeByte(0x08);
    writeByte(0x08);
    writeByte(0x08);
    writeByte(0x08);
    
    writeCommand(0xBD);
    writeByte(0x06);
    
    writeCommand(0xBC);
    writeByte(0x00);
    
    writeCommand(0xFF);
    writeByte(0x60);
    writeByte(0x01);
    writeByte(0x04);
    
    writeCommand(0xC3);
    writeByte(0x13);
    writeCommand(0xC4);
    writeByte(0x13);
    
    writeCommand(0xC9);
    writeByte(0x22);
    
    writeCommand(0xBE);
    writeByte(0x11);
    
    writeCommand(0xE1);
    writeByte(0x10);
    writeByte(0x0E);
    
    writeCommand(0xDF);
    writeByte(0x21);
    writeByte(0x0c);
    writeByte(0x02);
    
    writeCommand(0xF0);
    writeByte(0x45);
    writeByte(0x09);
    writeByte(0x08);
    writeByte(0x08);
    writeByte(0x26);
    writeByte(0x2A);
    
    writeCommand(0xF1);
    writeByte(0x43);
    writeByte(0x70);
    writeByte(0x72);
    writeByte(0x36);
    writeByte(0x37);
    writeByte(0x6F);
    
    writeCommand(0xF2);
    writeByte(0x45);
    writeByte(0x09);
    writeByte(0x08);
    writeByte(0x08);
    writeByte(0x26);
    writeByte(0x2A);
    
    writeCommand(0xF3);
    writeByte(0x43);
    writeByte(0x70);
    writeByte(0x72);
    writeByte(0x36);
    writeByte(0x37);
    writeByte(0x6F);
    
    writeCommand(0xED);
    writeByte(0x1B);
    writeByte(0x0B);
    
    writeCommand(0xAE);
    writeByte(0x77);
    
    writeCommand(0xCD);
    writeByte(0x63);
    
    writeCommand(0x70);
    writeByte(0x07);
    writeByte(0x07);
    writeByte(0x04);
    writeByte(0x0E);
    writeByte(0x0F);
    writeByte(0x09);
    writeByte(0x07);
    writeByte(0x08);
    writeByte(0x03);
    
    writeCommand(0xE8);
    writeByte(0x34);
    
    writeCommand(0x62);
    writeByte(0x18);
    writeByte(0x0D);
    writeByte(0x71);
    writeByte(0xED);
    writeByte(0x70);
    writeByte(0x70);
    writeByte(0x18);
    writeByte(0x0F);
    writeByte(0x71);
    writeByte(0xEF);
    writeByte(0x70);
    writeByte(0x70);
    
    writeCommand(0x63);
    writeByte(0x18);
    writeByte(0x11);
    writeByte(0x71);
    writeByte(0xF1);
    writeByte(0x70);
    writeByte(0x70);
    writeByte(0x18);
    writeByte(0x13);
    writeByte(0x71);
    writeByte(0xF3);
    writeByte(0x70);
    writeByte(0x70);
    
    writeCommand(0x64);
    writeByte(0x28);
    writeByte(0x29);
    writeByte(0xF1);
    writeByte(0x01);
    writeByte(0xF1);
    writeByte(0x00);
    writeByte(0x07);
    
    writeCommand(0x66);
    writeByte(0x3C);
    writeByte(0x00);
    writeByte(0xCD);
    writeByte(0x67);
    writeByte(0x45);
    writeByte(0x45);
    writeByte(0x10);
    writeByte(0x00);
    writeByte(0x00);
    writeByte(0x00);
    
    writeCommand(0x67);
    writeByte(0x00);
    writeByte(0x3C);
    writeByte(0x00);
    writeByte(0x00);
    writeByte(0x00);
    writeByte(0x01);
    writeByte(0x54);
    writeByte(0x10);
    writeByte(0x32);
    writeByte(0x98);
    
    writeCommand(0x74);
    writeByte(0x10);
    writeByte(0x85);
    writeByte(0x80);
    writeByte(0x00);
    writeByte(0x00);
    writeByte(0x4E);
    writeByte(0x00);
    
    writeCommand(0x98);
    writeByte(0x3e);
    writeByte(0x07);
    
    writeCommand(0x35);
    writeCommand(0x21);
    
    writeCommand(0x11);
    delayMs(120);
    writeCommand(0x29);
    delayMs(20);
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::setFrame(const Frame& frame) {
    uint8_t data[4];
    spiBegin();

    writeCommand(0x2A);
    data[0] = (frame.start.X >> 8) & 0xFF;
    data[1] = frame.start.X & 0xFF;
    data[2] = (frame.end.X >> 8) & 0xFF;
    data[3] = frame.end.X & 0xFF;
    writeData(data, sizeof(data));

    writeCommand(0x2B);
    data[0] = (frame.start.Y >> 8) & 0xFF;
    data[1] = frame.start.Y & 0xFF;
    data[2] = (frame.end.Y >> 8) & 0xFF;
    data[3] = frame.end.Y & 0xFF;
    writeData(data, sizeof(data));
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::write(uint8_t *data, size_t len) {
    spiBegin();
    writeCommand(0x2C);
    // Send data byte-by-byte to avoid modifying caller's buffer
    for (size_t i = 0; i < len; i++) SPI.transfer(data[i]);
    spiEnd();
}

// Begin a continuous pixel-streaming write (call after setFrame)
void DIYables_TFT_GC9A01_Round::beginWrite() {
    spiBegin();
    writeCommand(0x2C);
    setDataCommand(1); // keep DC high for subsequent data
}

// Send pixel data during a continuous write
void DIYables_TFT_GC9A01_Round::writeContinue(uint8_t *data, size_t len) {
    spiTx(data, len);
}

// End a continuous write (call after all pixels sent)
void DIYables_TFT_GC9A01_Round::endWrite() {
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (!isPixelInsideCircle(x, y)) return;
    spiBegin();
    setAddrWindow(x, y, x, y);
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
    spiEnd();
}

uint16_t DIYables_TFT_GC9A01_Round::colorRGB(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void DIYables_TFT_GC9A01_Round::fillScreen(uint16_t color) {
    spiBegin();
    setAddrWindow(0, 0, width() - 1, height() - 1);
    fillColor(color, (uint32_t)width() * height());
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (x >= width() || y >= height() || w <= 0 || h <= 0) return;
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x + w > width())  w = width()  - x;
    if (y + h > height()) h = height() - y;
    spiBegin();
    setAddrWindow(x, y, x + w - 1, y + h - 1);
    fillColor(color, (uint32_t)w * h);
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    fillRect(x, y, w, 1, color);
}

void DIYables_TFT_GC9A01_Round::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    fillRect(x, y, 1, h, color);
}

void DIYables_TFT_GC9A01_Round::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h) {
    if (x >= width() || y >= height() || (x + w) <= 0 || (y + h) <= 0) return;
    spiBegin();
    setAddrWindow(x, y, x + w - 1, y + h - 1);
    pushColorDataPGM(bitmap, (uint32_t)w * h);
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h) {
    if (x >= width() || y >= height() || (x + w) <= 0 || (y + h) <= 0) return;
    spiBegin();
    setAddrWindow(x, y, x + w - 1, y + h - 1);
    pushColorData(bitmap, (uint32_t)w * h);
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::setRotation(uint8_t r) {
    Adafruit_GFX::setRotation(r);
    _rotation = r & 0x03;
    spiBegin();
    writeCommand(0x36);
    switch (_rotation) {
        case 0: writeByte(0x48); break;
        case 1: writeByte(0xE8); break;
        case 2: writeByte(0x88); break;
        case 3: writeByte(0x28); break;
        default: writeByte(0x48); break;
    }
    spiEnd();
}

void DIYables_TFT_GC9A01_Round::invertDisplay(bool i) {
    spiBegin();
    writeCommand(i ? 0x21 : 0x20);
    spiEnd();
}
