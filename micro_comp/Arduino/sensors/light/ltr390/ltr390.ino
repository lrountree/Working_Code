/*
 * Sketch to get sensor readings from the LTR390 with an ATMega32u4
 * Written by Lucas
 * Depends on the following external libraries: Adafruit_BusIO, Adafruit_LTR390
 */

#include <Adafruit_LTR390.h>
#include <Print.h>
#include <Arduino.h>
#include <Wire.h>

//uint16_t InMode = 0;
//uint16_t InRes = 0;

uint8_t ltrAddress = 0x53;

Adafruit_LTR390 LTR = Adafruit_LTR390(); // instantiate I2C to LTR390 using adafruit driver and Wire.h

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (! LTR.begin() ) {
    Serial.println("Failed to connect to sensor LTR390 via I2C, check pins");
    exit(1);
  }
  Serial.println("I2C connection to sensor successful.");

  Serial.println("Part Number ID: ");
  Wire.requestFrom(83, 3, true);
  while (Wire.available()) {
    int readPart = Wire.read();
    Serial.println(readPart);
  }

  LTR.setMode(LTR390_MODE_UVS);
  Serial.print("Sensor Mode: ");
  if (LTR.getMode() == 0) {
    Serial.println("ALS");
  } else {
    Serial.println("UVS");
  }

  LTR.setGain(LTR390_GAIN_18);
  Serial.print("Sensor Gain: ");
  Serial.println(LTR.getGain());

  LTR.setResolution(LTR390_RESOLUTION_20BIT);
  Serial.print("Sensor Resolution: ");
  Serial.println(LTR.getResolution());
  Wire.requestFrom(83, 3, true);
  while (Wire.available()) {
    int readRes = Wire.read();
    Serial.println(readRes);
  }

  LTR.setThresholds(100, 1000);
  LTR.configInterrupt(true, LTR390_MODE_UVS);
}

void loop() {
  int loopCount = 0;
  while loopCount < 5
  PUT ARRAY HERE
    if (LTR.newDataAvailable()) {
      Serial.print("FREQ: [");
      Serial.print(LTR.readUVS());
      Serial.print("] | ");
    }
    delay(100);
}
