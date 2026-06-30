// Required libraries
#include <Arduino.h>
#include <Wire.h>
#include <Print.h>
#include <EEPROM.h>

// Register addresses
#define  ltrAddress      0b01010011  //0x53  main peripheral address
#define  ltrMainControl  0b00000000  //0x00  main operational mode control
#define  ltrPartID       0b00000110  //0x06  part and revision identification
#define  ltrMainStatus   0b00000111  //0x07  interrupt and data status
#define  ltrResMeas      0b00000100  //0x04  resolution and measure rate configuration
#define  ltrGain         0b00000101  //0x05  gain rate configuration
#define  ltrIntrConf     0b00011001  //0x19  interrupt configuration
#define  ltrIntrPrst     0b00011010  //0x1A  interrupt persist configuration
#define  ltrAlsData0     0b00001101  //0x0D  als data lower byte 
#define  ltrAlsData1     0b00001110  //0x0E  als data middle byte
#define  ltrAlsData2     0b00001111  //0x0F  als data higher byte
#define  ltrUvsData0     0b00010000  //0x10  uvs data lower byte
#define  ltrUvsData1     0b00010001  //0x11  uvs data middle byte
#define  ltrUvsData2     0b00010010  //0x12  uvs data higher byte
#define  ltrThreshUp0    0b00100001  //0x21  upper interrupt threshold byte
#define  ltrThreshUp1    0b00100010  //0x22  upper interrupt threshold byte
#define  ltrThreshUp2    0b00100011  //0x23  upper interrupt threshold byte
#define  ltrThreshLow0   0b00100100  //0x24  lower interrupt threshold byte
#define  ltrThreshLow1   0b00100101  //0x25  lower interrupt threshold byte
#define  ltrThreshLow2   0b00100110  //0x26  lower interrupt threshold byte

// - EEPROM -
// Total memory registers: 0-1000
// Sensor address range: 10-100
// Display address range: 101-200


int readRegister(byte registerAddress, 
    int mainAddress = ltrAddress) {         // I2C Device Register Address, number of bytes to read, I2C peripheral address
  Wire.beginTransmission(mainAddress);      // initiate device comms
  delay(50);
  Wire.write(registerAddress);              // set memory pointer at register address
  Wire.endTransmission();                   // execute command
  delay(50);
  Wire.requestFrom(mainAddress, 1);         // request one byte from write stream
  if (Wire.available()) {
    return Wire.read();                     // return requested byte
  }
}

int writeRegister(byte registerAddress, 
    byte inputByteData, 
    int mainAddress = ltrAddress) {      // I2C Device register address, byte to write, I2C peripheral address
  int writeResult;
  Wire.beginTransmission(mainAddress);   // Initiate transmission from controller
  delay(50);
  Wire.write(registerAddress);           // Move pointer to register address
  delay(50);
  Wire.write(inputByteData);             // write byte data to memory register
  delay(50);
  writeResult = Wire.endTransmission();  // returns 0 on success
  delay(50);
  
  // check if write failed  
  if (writeResult > 0) {
    Serial.println("I2C Write: FAILED");
    Serial.print("Error Code: ");
    Serial.print(writeResult);
  }

  // output error info
  if (writeResult == 1) {
    Serial.println(" - data too long to fit in transmit buffer.");
  } else if (writeResult == 2) {
    Serial.println(" - received NACK on transmit of address.");
  } else if (writeResult == 3) {
    Serial.println(" - received NACK on transmit of data.");
  } else if (writeResult == 4) {
    Serial.println(" - unknown error.");
  } else if (writeResult == 5) {
    Serial.println(" - timeout.");

  // output write info on success
  } else {
    Serial.print("Wrote Byte To: ");
    Serial.println(registerAddress);
    delay(100);
  }
  
  return writeResult;

}

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Serial Monitor: ONLINE");

  Wire.begin();
  Wire.setClock(400000);
  Wire.setWireTimeout(25000, true);
  Serial.println("Wire Config: COMPLETE");
  delay(100);

  int writeResult;
  writeResult = writeRegister(byte(ltrResMeas), byte(0b00000100), ltrAddress);
  int readOut;
  readOut = readRegister(ltrResMeas);
  Serial.print("New Register Data: ");
  Serial.println(readOut);

  Serial.println("All done!");

  byte cellData = 170;
  Serial.println("Begin EEPROM read/write test.");
  int totalCells = EEPROM.length();
  delay(10);
  Serial.print("Total EEPROM Cells: ");
  Serial.println(totalCells);
  Serial.print("Read data at address 0: ");
  byte eepromRead = EEPROM.read(int(0));
  delay(10);
  Serial.println(eepromRead);
  Serial.println("Compare data at address 0: ");
  byte compareData = EEPROM[0];
  delay(10);
  if (compareData == byte(cellData)) {
    Serial.println("Comparison: TRUE");
    Serial.print("Address 0: ");
    Serial.println(compareData);
    Serial.print("byte value: ");
    Serial.println(byte(cellData));
  }
    else {
      Serial.println("Comparison: FALSE");
      Serial.print("Address 0: ");
      Serial.println(compareData);
      Serial.print("byte value: ");
      Serial.println(byte(cellData));
      Serial.print("Updating Address 0 Value to: ");
      Serial.println(cellData);
      EEPROM.update(int(0), cellData);
      delay(10);
  }
  //Serial.println("Attempting EEPROM write");
  //EEPROM.write(int(0), byte(15));
  //delay(10);
  //Serial.println("Write COMPLETE");
  Serial.println("Reading current cell data...");
  byte eepromCheck = EEPROM.read(int(0));
  Serial.print("Value: ");
  Serial.println(eepromCheck);
}

void loop() { /* Empty Loop */ }
