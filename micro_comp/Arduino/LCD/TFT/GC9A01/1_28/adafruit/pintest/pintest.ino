#include <stdio.h>
#include <Adafruit_SPIDevice.h>

#define SPIDEVICE_CS 10
Adafruit_SPIDevice spi_dev =
    Adafruit_SPIDevice(SPIDEVICE_CS, 16000000, SPI_BITORDER_MSBFIRST, SPI_MODE1);
// Adafruit_SPIDevice spi_dev = Adafruit_SPIDevice(SPIDEVICE_CS, 13, 12, 11,
// 100000, SPI_BITORDER_MSBFIRST, SPI_MODE1);

void setup() {
  while (!Serial) {
    delay(10);
  }
  Serial.begin(115200);
  Serial.println("SPI device mode test");
  Serial.print("CS Pin: ");
  Serial.println(SPIDEVICE_CS);
  
  if (!spi_dev.begin()) {
    Serial.println("Could not initialize SPI device");
    while (1)
      ;
  }
}

void loop() {
  Serial.println("\n\nTransfer test");
  for (uint16_t x = 0; x <= 0xFF; x++) {
    uint8_t i = x;
    Serial.print("0x");
    Serial.print(i, HEX);
    spi_dev.read(&i, 1, i);
    Serial.print("/");
    Serial.print(i, HEX);
    Serial.print(", ");
    delay(25);
  }
}
