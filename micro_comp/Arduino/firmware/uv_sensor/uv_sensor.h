/* Author: Lucas Rountree
 * Date: 06_2026
 * Purpose: Device to measure uv light intensity and estimate wavelength. 
 *          Display data on round LCD display with custom interface.
 *          Store configuration settings in EEEPROM.
 * MCU: ATMEGA32U4-MU
 * Board: Pro Micro
 * Display: GC9A01A 2_8_inch 240x240 round display (SPI)
 * Sensor: LTR390 ALS+UVS Sensor (I2C)
 * Depends: Adafruit_GFX, Adafruit_BUSIO, Adafruit_GC9A01A
 * Permission: Go Nuts
 */

#include "Arduino.h"

// Register Addresses
#define  ltrAddress      0b01010011         //  0x53  main peripheral address
#define  ltrMainControl  0b00000000         //  0x00  main operational mode control
#define  ltrPartID       0b00000110         //  0x06  part and revision identification
#define  ltrMainStatus   0b00000111         //  0x07  interrupt and data status
#define  ltrResMeas      0b00000100         //  0x04  resolution and measure rate configuration
#define  ltrGain         0b00000101         //  0x05  gain rate configuration
#define  ltrIntrConf     0b00011001         //  0x19  interrupt configuration
#define  ltrIntrPrst     0b00011010         //  0x1A  interrupt persist configuration
#define  ltrAlsData0     0b00001101         //  0x0D  als data lower byte 
#define  ltrAlsData1     0b00001110         //  0x0E  als data middle byte
#define  ltrAlsData2     0b00001111         //  0x0F  als data higher byte
#define  ltrUvsData0     0b00010000         //  0x10  uvs data lower byte
#define  ltrUvsData1     0b00010001         //  0x11  uvs data middle byte
#define  ltrUvsData2     0b00010010         //  0x12  uvs data higher byte
#define  ltrThreshUp0    0b00100001         //  0x21  upper interrupt threshold byte
#define  ltrThreshUp1    0b00100010         //  0x22  upper interrupt threshold byte
#define  ltrThreshUp2    0b00100011         //  0x23  upper interrupt threshold byte
#define  ltrThreshLow0   0b00100100         //  0x24  lower interrupt threshold byte
#define  ltrThreshLow1   0b00100101         //  0x25  lower interrupt threshold byte
#define  ltrThreshLow2   0b00100110         //  0x26  lower interrupt threshold byte
// - EEPROM -
// Total memory registers: 0-1000
// Sensor address range: 10-100
// Display address range: 101-200
// EEPROM Addresses
#define  ltrMode         10                 //  ALS(0) or UVS(1) mode, bit 3
#define  ltrModeState    11                 //  Sensor activity standby(0) or active(1), bit 1
#define  ltrResolution   12                 //  Sensor resolution, bits 4-6
#define  ltrMeasRate     13                 //  Sensor Measurement rate, bits 0-2
#define  ltrGainRange    14                 //  Sensor Gain Range, bits 0-2
// Push Buttons
#define  pbOne           7                  //  Power, Select, Exit
#define  pbTwo           6                  //  Navigation, Start, Stop
// Sensor
#define uvSDA            2                  //  I2C data pin
#define uvSCL            3                  //  I2C clock pin
#define uvINT            4                  //  I2C interrupt pin
// Display
#define lcdRST           A0                 //  LCD Reset pin
#define lcdCS            10                 //  LCD Chip Select pin
#define lcdDC            9                  //  LCD Data/Command pin
#define lcdSDA           16                 //  LCD Serial Data pin (PICO/MOSI)
#define lcdSCL           15                 //  LCD Clock pin
#define lcdDiameter      240                //  LCD is round, so width and height are the same
#define halfDia          120                //  Half LCD Diameter
#define hdMin            119                //  Half LCD Diameter, minus one
#define spiFreq          160000000          //  LCD SPI Clock Frequency
#define monGreen         0x17E2
#define uvPurple         0xE1FC
#define BLACK            GC9A01A_BLACK
#define WHITE            GC9A01A_WHITE

// Type Definitions for Sensor Settings
typedef enum {
  als_mode = 0,                             //  Enable ALS sensor, default setting
  uvs_mode = 8                              //  Enable UVS sensor
} sensorMode;

typedef enum {
  sensor_standby = 0,                       //  Put sensor in standby, default setting
  sensor_active = 2                         //  Activate sensor
} sensorStatus;

// Sensor Resolution
typedef enum {
  Res_20 = 0,                               //  20 Bit Resolution, 400ms conversion time
  Res_19 = 16,                              //  19 Bit Resolution, 200ms conversion time
  Res_18 = 32,                              //  18 Bit Resolution, 100ms conversion time, default setting
  Res_17 = 48,                              //  17 Bit Resolution, 50ms conversion time
  Res_16 = 64,                              //  16 Bit Resolution, 25ms conversion time
  Res_13 = 80                               //  13 Bit Resolution, 12.5ms conversion time
} sensorResolution;                         //  Higher resolution means higher light sensativity, but also higher noise sensativity and slower speeds

// Sensor Masurement Rate
typedef enum {
  Meas_25 = 0,                              //  25ms, etc. Higher speeds can measure faster wavelengths but take longer to run
  Meas_50,
  Meas_100,                                 //  Default setting
  Meas_200,
  Meas_500,
  Meas_1000,
  Meas_2000
} sensorMeasureRate;

// Sensor Gain
typedef enum {
  Gain_1 = 0,                               //  Gain Range, higher range means more electron production, so more accurate readings, and slower speeds
  Gain_3,                                   //  Default setting
  Gain_6,
  Gain_9,
  Gain_18
} sensorGain;

class uvs {
  public:
    uvs(pbOne, pbTwo);
    void deBounce(int pbID, bool pbLast, int dbTime);
    void readRegister(int registerAddress, int deviceAddress);
    void writeRegister(int registerAddress, int inputData, int deviceAddress);
    void drawCross(uint16_t color);
    void drawSplash(uint16_t color);
  private:
    int _pbone;
    int _pbtwo;
};
