//#include <Print.h>
//#include <SPI.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <Fonts/Org_01.h>

#define lcd_diameter 240
#define monGreen 0x17E2
#define uvPurple 0xE1FC

Adafruit_GC9A01A lcd(10, 9, A0);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Serial Monitor: ONLINE");

  lcd.begin(160000000);
  lcd.setRotation(0);
  lcd.setFont(&Org_01);
  lcd.setTextColor(GC9A01A_GREEN);
  lcd.fillScreen(GC9A01A_BLACK);
  Serial.println("LCD: ONLINE");

  //Serial.println("Testing LCD Display Text");
  //lcd.setCursor(90, 20);
  //lcd.setTextSize(1);
  //lcd.setTextWrap(false);
  //lcd.println("Hello World!");
  
  //lcd.setCursor(80, 40);
  //lcd.setTextSize(2);
  //lcd.println("Initial");

  //lcd.setCursor(85, 70);
  //lcd.setTextSize(3);
  //lcd.println("Font");

  //lcd.setCursor(70, 110);
  //lcd.setTextSize(4);
  //lcd.println("Test!");

  //lcd.drawFastVLine(120, 0, 240, GC9A01A_GREEN);
  //lcd.drawFastHLine(0, 120, 240, GC9A01A_GREEN);
  drawSplash(GC9A01A_WHITE);
  drawSplash(GC9A01A_BLACK);
  drawSplash(uvPurple);
  drawSplash(GC9A01A_BLACK);
  mainMenu(uvPurple);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void mainMenu(uint16_t color){
  // cross animation
  uint8_t _incr = 2;
  uint8_t _dia = lcd_diameter;
  uint8_t _HD = _dia / 2;
  for (uint8_t i = 0; i <= _HD; i += _incr) {
    lcd.drawLine(_HD, (_HD - i), _HD, ((_HD - i) - _incr), color);  // North
    lcd.drawLine((_HD + i), _HD, ((_HD + i) + _incr), _HD, color);  // East
    lcd.drawLine(_HD, (_HD + i), _HD, ((_HD + i) + _incr), color);  // South
    lcd.drawLine((_HD - i), _HD, ((_HD -i) - _incr), _HD, color);  // West
    delay(6);
  }
  // Thicken cross animation
  for (uint8_t i = 0; i <= _HD; i += _incr) {
    lcd.fillRect((_HD - 1), (_HD - i), 3, 2, color); // North
    lcd.fillRect((_HD + i), (_HD + 1), 2, 3, color); // East
    lcd.fillRect((_HD - 1), (_HD + i), 3, 2, color); // South
    lcd.fillRect((_HD - i), (_HD + 1), 2, 3, color); // West
    delay(8);
  }
  // Center circle animation
  for (uint8_t i = 0; i <= 108; i += _incr) {
    lcd.drawRoundRect((_HD - (i / 2)), (_HD - (i / 2)), i, i, (i / 2), color); // Draw circle
    lcd.fillRoundRect((_HD - (i / 2)) + 3, (_HD - (i / 2)) + 3, (i - 6), (i - 6), (i / 2), GC9A01A_BLACK); // Clean lines
    delay(6);
  }
  // Menu text
  lcd.setCursor(77, 125);
  lcd.setTextSize(3);
  lcd.println("START");
  int _x;
  int _y;
  char _menus[3][4] = {
    {"Settings", "Info", "Sensor", "Battery"}, // Menu titles
    {20, 150, 20, 150}, // Starting X value
    {152, 200, 100, 50},  // Starting Y value
  };
  for (byte _t = 0; _t < (sizeof(_menus[]) / sizeof(_menus[0])); _t++) {
    _x = _menus[_t][_t];
    _y = _menus[_t][_t][_t];
    lcd.setTextSize(2);
    for (char &_c : _menus[_t]; _x += 11; _y += 8;) {
      lcd.setCursor(_x, _y);
      lcd.println(_i);
    }
  }
}

void drawSplash(uint16_t color){
  // x animation
  int _incrx = 20;
  int _dia = lcd_diameter;
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