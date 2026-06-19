/* Author: Lucas Rountree
*  Date: 06_2026
*  MCU: ATMEGA32U4-MU
*  Board: Pro Micro
*  Depends: Adafruit GFX, BUSIO, and GC9A01A libraries
*  Permission: Free to use, free of charge.
*/

//#include "pro_micro_32u4.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

// Push Button
const uint8_t PBP_ = 7;
uint8_t PBP_STATE = 0;
uint8_t PBP_LastState = LOW;
uint32_t DebounceLast = 0;
uint32_t DebounceDelay = 50; //in milliseconds

// LTR390 ALS+UV Sensor
const uint8_t UV_SDA 2
const uint8_t UV_SCL 3
const uint8_t UV_INT 4

// 1.28 round LCD TFT display GC9A01A
const uint8_t RST_PIN = A0;
const uint8_t CS_PIN = 10;
const uint8_t DC_PIN = 9;
const uint8_t SDA_PIN = 16;
const uint8_t SCL_PIN = 15;

const uint8_t LCD_WIDTH = 240;
const uint8_t LCD_HEIGHT = 240;

const unsigned long SPI_FREQ = 160000000;

SPISettings Pro_Micro_Settings(SPI_FREQ, MSBFIRST, SPI_MODE1);

Adafruit_GC9A01A tft(CS_PIN, DC_PIN, RST_PIN);

void setup() {
  delay(200);
  Serial.begin(115200);

  Serial.println("Button Init");
  pinMode(PBP_, INPUT);

  Serial.println("Initializing GCA9A01A LCD Device");

  tft.begin(SPI_FREQ);

  Serial.println("Clearing screen");
  tft.setRotation(0);
  tft.fillScreen(GC9A01A_BLACK);
  Serial.println("Drawing purple pixel box");
  tft.drawPixel(120, 120, GC9A01A_PURPLE);
  tft.drawPixel(116, 116, GC9A01A_PURPLE);
  tft.drawPixel(124, 124, GC9A01A_PURPLE);
  tft.drawPixel(124, 116, GC9A01A_PURPLE);
  tft.drawPixel(116, 124, GC9A01A_PURPLE);
  tft.drawFastVLine(112, 112, 16, GC9A01A_PURPLE);
  tft.drawFastVLine(128, 112, 16, GC9A01A_PURPLE);
  tft.drawFastHLine(112, 112, 16, GC9A01A_PURPLE);
  tft.drawFastHLine(112, 128, 16, GC9A01A_PURPLE);
  tft.drawRect(35, 35, 169, 169, GC9A01A_PURPLE);
  tft.drawCircle(120, 120, 119, GC9A01A_PURPLE);
}

void loop() {
  uint8_t PBPReading = digitalRead(PBP_);

  if (PBPReading != PBP_LastState) {
    DebounceLast = millis();
  }
  
  if ((millis() - DebounceLast) > DebounceDelay) {
    if (PBPReading != PBP_STATE) {
      PBP_STATE = PBPReading;
      if (PBP_STATE == HIGH) {
        Serial.println("Button Pushed!");
      }
    }
  }

  PBP_LastState = PBPReading;
  //delay(200);
  
}