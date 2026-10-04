#include <Wire.h>
#include "uv_sensor.h"

uvs::uvs(pbOne, pbTwo) {
  _pbone = pbOne;
  _pbtwo = pbTwo;
}

// Instantiate Source File and Initiate Buttons
void uvs::begin() {
  pinMode(_pinone, INPUT_PULLUP);
  pinMode(_pintwo, INPUT_PULLUP);
}

// Button De-Bounce Function
void uvs::deBounce(int pbID, bool pbLast, int dbTime = 0) {
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
    uvs.deBounce(pbID, pbLast, dbTime);
  }
}

// Read from I2C Register Address
uint16_t uvs::readRegister(int registerAddress, int deviceAddress = ltrAddress) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, 1);
  if (Wire.available()) {
    return Wire.read();
  } else {
    return 0;
  }
}

// Write to I2C Register Address
int uvs::writeRegister(int registerAddress, int inputData, int deviceAddress = ltrAddress) {
  Write.beginTransmission(deviceAddress);
  Write.write(registerAddress);
  Write.write(inputdata);
  int writeResult = Wire.endTransmission();
  return writeResult; 
}

// Menu Transition Animation
void uvs::drawCross(uint16_t color) {
  for (int _i = 0; _i <= (lcdDiameter / 2); _i+= 2) {
    
}

uvs::drawSplash(uint16_t color) {
  _color = color;
}

