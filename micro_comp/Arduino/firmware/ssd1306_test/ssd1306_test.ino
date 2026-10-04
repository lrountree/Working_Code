//#include <SPI.h>
#include <Adafruit_SSD1306_72x40.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include <RotaryEncoder.h>

#define _oled_W 72
#define _oled_H 40
#define xOffset 30
#define yOffset 12
#define _rst_pin 3
#define _msio 5
#define _mosi 6
#define _sda 8
#define _scl 9
#define potPin 0
#define capPin 10
#define rotPin 9
#define encPin1 7
#define encPin2 8

bool cap_init = HIGH;
bool rot_init = HIGH;
bool enc1_init = HIGH;
bool enc2_init = HIGH;
int potVal = 0;

//Adafruit_SSD1306 oled(_oled_W, _oled_H, &Wire, _rst_pin);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);
//Adafruit_SSD1306_72x40 oled(_msio, _mosi);
//RotaryEncoder encoder(encPin1, encPin2, RotaryEncoder::LatchMode::TWO03);

void setup() {
  Serial.begin(115200);
  pinMode(capPin, INPUT_PULLUP);
  pinMode(rotPin, INPUT);
  pinMode(encPin1, INPUT);
  pinMode(encPin2, INPUT);

  digitalWrite(encPin1, HIGH);
  digitalWrite(encPin2, HIGH);

 // if (!display.display(SSD1306_SWITCHCAPVCC, 0x3C)) {
 //  Serial.println(F("SSD1306 initialization failed!"));
 //   for(;;);
 // }

  u8g2.begin();
  u8g2.setContrast(255);
  u8g2.setBusClock(400000);
  u8g2.setFont(u8g2_font_ncenB10_tr);

  //if (!oled.begin()) {
  //  Serial.println(F("SSD1306 initialization failed!"));
  //  for(;;);
  //}
  //oled.clearDisplay();
  //oled.display();
  //delay(1000);
  //oled.clearDisplay();
  //oled.setTextColor(1);
  //oled.setTextSize(1);
  //oled.setCursor(0, 0);
  //Serial.println("printing hellow world");
  //oled.println("Hello World!");
//  oled.fillCircle(30, 12, 5, 1);
  //for (int _x = 1; _x <= 4; _x++) {
  //  oled.fillScreen(0);
  //  delay(1000);
  //  oled.fillScreen(1);
 // }
 u8g2.clearBuffer();
 u8g2.setCursor(60, 50);
 u8g2.printf("x");
 u8g2.sendBuffer();
 delay(2000);
 u8g2.clearBuffer();
 u8g2.drawFrame(28, 24, 72, 40);
 u8g2.setCursor(45, 48);
 u8g2.printf("%dx%d", _oled_W, _oled_H);
 u8g2.sendBuffer();
 delay(2000);
}

void loop() {
//  display.clearDisplay();
//  display.setTextColor(1);
//  display.setTextSize(2);
//  display.setCursor(0, 0);
//  display.println("Hello World!");

  bool cap_state = digitalRead(capPin);
  bool rot_state = digitalRead(rotPin);
  bool enc1_state = digitalRead(encPin1);
  bool enc2_state = digitalRead(encPin2);
  int potVal = analogRead(potPin);

  u8g2.clearBuffer();
  u8g2.drawFrame(28, 24, 72, 40);
  u8g2.setCursor(45, 48);
  u8g2.print(potVal/40);
  u8g2.sendBuffer();

  if (cap_state != cap_init) {
    deBounce(capPin, cap_init, 0);
  } else if (rot_state != rot_init) {
    deBounce(rotPin, rot_init, 0);
  }

  if (cap_state == HIGH) {
    Serial.println("capacitive (cap) button pushed!");
  } else if (rot_state == LOW) {
    Serial.println("Rotary Encoder button pushed!");
  } else if (enc1_state != enc1_init) {
    Serial.println(enc1_state);
  } else if (enc2_state != enc2_init) {
    Serial.println(enc2_state);
  }

//  static int pos = 0;
//  encoder.tick();

  //int newPos = encoder.getPosition();
  //if (pos != newPos) {
  //  Serial.print("Position: ");
  //  Serial.print(newPos);
  //  Serial.print("Direction: ");
  //  Serial.println((int)(encoder.getDirection()));
  //  pos = newPos;
 // }

  cap_init = cap_state;
  rot_init = rot_state;
  enc1_init = enc1_state;
  enc2_init = enc2_state;
}

void deBounce(int pin_ID, bool last_state, int db_time) {
  bool new_state = digitalRead(pin_ID);
  if (new_state != last_state) {
    delay(10);
    db_time += 10;
  } else {
    return;
  }
  if (db_time > 40) {
    return;
  } else {
    deBounce(pin_ID, last_state, db_time);
  }
}