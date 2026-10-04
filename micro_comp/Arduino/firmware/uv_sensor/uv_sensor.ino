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
#include <Print.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

// Variables
bool pb1LastState = HIGH;                    //  Push Button 1 last pin state
bool pb2LastState = HIGH;                    //  Push Button 2 last pin state

// Set LCD pins
Adafruit_GC9A01A lcd(lcdCS, lcdDC, lcdRST);
// Set Button pins
uvs uvs();

// Setup Function
void setup() {
  // Start serial monitor
  Serial.begin(115200);                      //  Start serial monitor on baud 115200
  while(!Serial);                            //  Wait for monitor to come online
  Serial.println("Serial Monitor: ONLINE");

  // Initialize push buttons
  uvs.begin();
  Serial.println("Push Buttons: ONLINE");

  // Start wire (I2C) service
  Wire.begin();                              //  Initiate I2C connection via Wire
  Wire.setClock(400000);                     //  Set clock frequency
  Wire.setWireTimeout(25000, true);          //  Set timeout for Wire
  Serial.println("I2C Wire: ONLINE"); 
  
  // Initialize LCD (SPI)
  lcd.begin(spiFreq);
  lcd.setRotation(0);
  lcd.fillScreen(BLACK);
  Serial.println("LCD: ONLINE");

  // Configure Sensor User Settings
  int modeSetting = EEPROM.read(ltrMode);
  int statusSetting = EEPROM.read(ltrModeState);
  int resSetting = EEPROM.read(ltrResolution);
  int measSetting = EEPROM.read(ltrMeasRate);
  int gainSetting = EEPROM.read(ltrGainRange);
  int modestatusSetting = modeSetting + statusSetting;
  int resmeasSetting = resSetting + measSetting;
  writeRegister(ltrMainControl, modestatusSetting);
  writeRegister(ltrResMeas, resmeasSetting);
  writeRegister(ltrGain, gainSetting);
  Serial.println("Sensor User Settings Configuration: COMPLETE");

  // Run Opening Graphic
  drawSplash(WHITE);
  drawSplash(BLACK);
  drawSplash(uvPurple);
  drawCross(uvPurple);
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

// Write result reporting
void processResult(int writeResult) {
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
    uint8_t printResult;
    Wire.requestFrom(deviceAddress, 1);
    if (Wire.available()) {
      Serial.println("Register Write: SUCCESS");
      Serial.print(printResult, BIN);
      Serial.print(" written to ");
      Serial.println(registerAddress, BIN);
    }
  }
}

void drawCross(uint16_t color){
  // cross animation
  int _incr = 2;
  int _HD = lcdDiameter / 2;
  for (int i = 0; i <= _HD ; i += _incr) {
    int sub_hd = _HD - i;
    int add_hd = _HD + i;
    int sub_inc_hd = sub_hd - _incr;
    int add_inc_hd = add_hd + _incr;
    lcd.drawLine(_HD, sub_hd, _HD, sub_inc_hd, color);  // North
    lcd.drawLine(add_hd, _HD, add_inc_hd, _HD, color);  // East
    lcd.drawLine(_HD, add_hd, _HD, add_inc_hd, color);  // South
    lcd.drawLine(sub_hd, _HD, sub_inc_hd, _HD, color);  // West
    delay(8);
  }
}

void drawSplash(uint16_t color){
  // x animation
  int _incrx = 20;
  int _dia = lcdDiameter;
  int _HD = _dia / 2;
  for (int i = _incrx; i < _HD; i += _incrx) {
    int sub_hd = _HD - i;
    int add_hd = _HD + i;
    lcd.drawLine(sub_hd, _dia, add_hd, 0, color);
    lcd.drawLine(0, sub_hd, _dia, add_hd, color);
    delay(20);
  }
  for (int i = _incrx; i < _HD; i += _incrx) {
    int sub_d = _dia - i;
    lcd.drawLine(0, sub_d, _dia, i, color);
    lcd.drawLine(i, 0, sub_d, _dia, color);
    delay(20);
  }
}

