#include <Arduino.h>
#include <Print.h>
#include <Wire.h>

#define SDA_PIN 2
#define SCL_PIN 3
uint8_t WireRequest = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Test Serial Print");

  Wire.begin();
  //Serial.println("Failed to initiate I2C pins!");
  //Serial.println("Connected to I2C Pins.");
}

void loop() {
  if (WireRequest == 0) {
    Wire.requestFrom(0x53, 6); //6 byte request
    while (Wire.available()) {
      char WireRequest = Wire.read();
      Serial.println(WireRequest);
    }
  }
}
