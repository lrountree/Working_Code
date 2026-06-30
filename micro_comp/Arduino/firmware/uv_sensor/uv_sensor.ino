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

// Required Libraries
#include <Arduino.h>
#include <Print.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

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
// EEPROM Addresses
#define  ltrMode         10                 //  ALS(0) or UVS(1) mode, bit 3
#define  ltrModeState    11                 //  Sensor activity standby(0) or active(1), bit 1
#define  ltrResolution   12                 //  Sensor resolution, bits 4-6
#define  ltrMeasRate     13                 //  Sensor Measurement rate, bits 0-2
#define  ltrGainRange    14                 //  Sensor Gain Range, bits 0-2
// Push Buttons
#define  pbOne           6                  //  Power, Navigation, Menu
#define  pbTwo           7                  //  Start, Stop, Select
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
#define lcdWidth         240                //  LCD Width in pixels
#define lcdHeight        240                //  LCD Height in pixels
#define spiFreq          160000000          //  LCD SPI Clock Frequency
#define lcdPurple        GC9A01A_PURPLE
#define lcdGreen         GC9A01A_GREEN
#define lcdBlack         GC9A01A_BLACK
#define lcdWhite         GC9A01A_WHITE

// Variables
bool pb1LastState = HIGH;                    //  Push Button 1 last pin state
bool pb2LastState = HIGH;                    //  Push Button 2 last pin state

// Type Definitions for Sensor Settings
typedef enum {
  als_mode = 0,                             //  Enable ALS sensor, default setting
  uvs_mode = 8                              //  Enable UVS sensor
} sensorMode;

typedef enum {
  sensor_standby = 0,                       //  Put sensor in standby, default setting
  sensor_active = 2                         //  Activate sensor
} sensorStatus;

typedef enum {
  Res_20 = 0,                               //  20 Bit Resolution, 400ms conversion time
  Res_19 = 16,                              //  19 Bit Resolution, 200ms conversion time
  Res_18 = 32,                              //  18 Bit Resolution, 100ms conversion time, default setting
  Res_17 = 48,                              //  17 Bit Resolution, 50ms conversion time
  Res_16 = 64,                              //  16 Bit Resolution, 25ms conversion time
  Res_13 = 80                               //  13 Bit Resolution, 12.5ms conversion time
} sensorResolution;                         //  Higher resolution means higher light sensativity, but also higher noise sensativity and slower speeds

typedef enum {
  Meas_25 = 0,                              //  25ms, etc. Higher speeds can measure faster wavelengths but take longer to run
  Meas_50,
  Meas_100,                                 //  Default setting
  Meas_200,
  Meas_500,
  Meas_1000,
  Meas_2000
} sensorMeasureRate;

typedef enum {
  Gain_1 = 0,                               //  Gain Range, higher range means more electron production, so more accurate readings, and slower speeds
  Gain_3,                                   //  Default setting
  Gain_6,
  Gain_9,
  Gain_18
} sensorGain;

// - EEPROM -
// Total memory registers: 0-1000
// Sensor address range: 10-100
// Display address range: 101-200

// Setup Function
void setup() {
  // Start serial monitor
  Serial.begin(115200);                      //  Start serial monitor on baud 115200
  while(!Serial);                            //  Wait for monitor to come online
  Serial.println("Serial Monitor: ONLINE");

  // Initialize push buttons
  pinMode(pbOne, INPUT_PULLUP);                     
  pinMode(pbTwo, INPUT_PULLUP);
  Serial.println("Push Buttons: INITIALIZED");

  // Start wire (I2C) service
  Wire.begin();                              //  Initiate I2C connection via Wire
  Wire.setClock(400000);                     //  Set clock frequency
  Wire.setWireTimeout(25000, true);          //  Set timeout for Wire
  Serial.println("Wire Config: COMPLETE"); 
  
  // Initialize LCD (SPI)
  Adafruit_GC9A01A lcd(lcdCS, lcdDC, lcdRST);
  lcd.begin(spiFreq);
  lcd.setRotation(0);
  lcd.fillScreen(lcdBlack);
  Serial.println("LCD: INITIALIZED");

  // Configure User Settings
  byte modeSetting = EEPROM.read(ltrMode);
  byte statusSetting = EEPROM.read(ltrModeState);
  byte resSetting = EEPROM.read(ltrResolution);
  byte measSetting = EEPROM.read(ltrMeasRate);
  byte gainSetting = EEPROM.read(ltrGainRate);
  byte modestatusSetting = modeSetting + statusSetting
  byte resmeasSetting = resSetting + measSetting;
  writeRegister(ltrMainControl, modestatusSetting);
  writeRegister(ltrResMeas, resmeasSetting);
  writeRegister(ltrGain, gainSetting);
  Serial.println("User Settings: CONFIGURED");

  // Run Opening Graphic

}
// Loop Function
void loop() {
  bool buttonPush_1 = digitalRead(pbOne);
  bool buttonPush_2 = digitalRead(pbTwo);
  delay(10);
  if (buttonPush_1 != pb1LastState && buttonPush_2 != pb2LastState) {
    delay(10);
    return;
  }
  if (buttonPush_1 != pb1LastState || buttonPush_2 != pb2LastState) {
    if (buttonPush_1 != pb1LastState) {
      deBounce(pbOne, pb1LastState, 0);
      if (buttonPush_1 == LOW) {
        Serial.println("Button One PUSHED");
      }
    } else if (buttonPush_2 != pb2LastState) {
      deBounce(pbTwo, pb2LastState, 0);
      if (buttonPush_2 == LOW) {
        Serial.println("Button Two PUSHED");
      }
    }
  }
  
  pb1LastState = buttonPush_1;
  pb2LastState = buttonPush_2;
}

// - Specific Functions -

void deBounce(int pbID, bool pbLast, int dbTime) {
  bool pbPush = digitalRead(pbID);
  if (pbPush != pbLast) {
    delay(10);
    dbTime += 10;
  } else {
    return;
  }
  if (dbTime > 50) {
    return;
  } else {
    deBounce(pbID, pbLast, dbTime);
  }
}

// Read I2C Register Address
byte readRegister (byte registerAddress,
    int deviceAddress = ltrAddress) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, 1);
  if (Wire.available()) {
    return Wire.read();
  }
}

// Write Data to I2C Register Address
void writeRegister (byte registerAddress,
    byte inputData,
    int deviceAddress =  ltrAddress) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.write(inputData);
  int writeResult = Wire.endTransmission();
  
  // Write result reporting
  if (writeResult > 0) {
    Serial.println("I2C Write: FAILED");
    Serial.print("Error Code: ");
    Serial.print(writeResult);
  }

  if (writeResult == 1) {
    Serial.println(" - data too long to fit in transmit buffer");
  } else if (writeResult == 2) {
    Serial.println(" - recieved NACK on transmit of address");
  } else if (writeResult == 3) {
    Serial.println(" - recieved NACK on transmit of data");
  } else if (writeResult == 4) {
    Serial.println(" - unknown error");
  } else if (writeResult == 5) {
    Serial.println(" - timeout");
  // Confirm write on success
  } else {
    byte printResult;
    Wire.requestFrom(deviceAddress, 1);
    if (Wire.available()) {
      Serial.println("Register Write: SUCCESS");
      Serial.print(printResult, BIN);
      Serial.print(" written to ");
      Serial.println(registerAddress, BIN);
    }
  }
}

