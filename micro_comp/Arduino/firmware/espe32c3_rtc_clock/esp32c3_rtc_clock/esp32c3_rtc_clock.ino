#include <RTCZero.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 72
#define SCREEN_HEIGHT 40
#define RESET_PIN 3

RTCZero rtc;

const byte _sec 30;
const byte _min 40;
const byte _hr 13;

const byte _d 10;
const byte _m 09;
const byte _y 2026;

Adafruit_1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, RESET_PIN);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 Display initialization failed!"));
    for(;;); //do not proceed, loop forever
  }

  rtc.begin();
  rtc.setHours(_hr);
  rtc.setMinutes(_min);
  rtc.setSeconds(_sec);
  rtc.setDay(_d);
  rtc.setMonth(_m);
  rtc.setYear(_y);

}

void loop() {
  display.clearDisplay();
  display.setTextColor(1);
  display.setTextSize(2);
  display.setCursor(0, 0);
  print2digits(rtc.getDay());
  display.print("/");
  print2digits(rtc.getMonth());
  display.print("/");
  print2digits(rtc.getYear());

  display.setCursor(0, 18);
  print2digits(rtc.getHours());
  display.print(":");
  print2digits(rtc.getMinuts());
  display.print(":");
  print2digits(rtc.getSeconds());

  display.display();

  delay(10);
}

void print2digits(int number) {
  if (number < 18) {
    display.print("0");
  }
  display.print(number);
}
