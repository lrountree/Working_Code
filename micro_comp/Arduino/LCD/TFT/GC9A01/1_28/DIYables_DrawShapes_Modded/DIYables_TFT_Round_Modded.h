/* Modded to work with Pro Micro 32U4 by Lucas Rountree, all credit to DIYables etc
 * Changes: Added custom spi settings variable and specific 32u4 variables
 */

#ifndef DIYables_TFT_Round_Modded_H
#define DIYables_TFT_Round_Modded_H

#include <stdint.h>
#include <stddef.h>
#include <Adafruit_GFX.h>

extern uint8_t PIN_RST;
extern uint8_t PIN_CS;
extern uint8_t PIN_DC;

class DIYables_TFT_GC9A01_Round : public Adafruit_GFX {
  public:
    struct Point {
        uint16_t X, Y;
    };

    struct Frame {
        Point start, end;
    };

    DIYables_TFT_GC9A01_Round(uint8_t resPin, uint8_t dcPin, uint8_t csPin);

    void begin();
    void setFrame(const Frame& frame);
    void write(uint8_t *data, size_t len);
    void writeContinue(uint8_t *data, size_t len);
    void beginWrite();
    void endWrite();

    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void fillScreen(uint16_t color) override;
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
    void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
    void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
    void setRotation(uint8_t r) override; 
    void invertDisplay(bool i) override;

    static uint16_t colorRGB(uint8_t r, uint8_t g, uint8_t b);

  private:
    uint8_t _res, _dc, _cs;
    uint8_t _rotation;

    inline void setReset(uint8_t val);
    inline void setDataCommand(uint8_t val);
    inline void setChipSelect(uint8_t val);
    inline void delayMs(uint16_t ms);
    void spiTx(uint8_t *data, size_t len);

    void spiBegin();
    void spiEnd();
    void setAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void fillColor(uint16_t color, uint32_t count);
    void pushColorData(uint16_t *data, uint32_t len);
    void pushColorDataPGM(const uint16_t *data, uint32_t len);

    void writeCommand(uint8_t cmd);
    void writeData(uint8_t *data, size_t len);
    bool isPixelInsideCircle(int x, int y);
    inline void writeByte(uint8_t val);
};

// Short alias
using DIYables_TFT = DIYables_TFT_GC9A01_Round;

#endif // DIYables_TFT_Round_Modded_H
