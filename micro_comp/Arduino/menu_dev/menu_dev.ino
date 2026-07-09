//#include <Print.h>
//#include <SPI.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <Fonts/Org_01.h>

#define lcd_diameter 240
#define monGreen 0x17E2
#define uvPurple 0xE1FC
#define _red GC9A01A_RED
#define _pink GC9A01A_PINK
#define _black GC9A01A_BLACK
#define _white GC9A01A_WHITE
#define _orange GC9A01A_ORANGE
#define _yellow GC9A01A_YELLOW
#define _blue GC9A01A_BLUE
#define _cyan GC9A01A_CYAN

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
  //drawSplash(uvPurple, 0);
  //drawSplash(GC9A01A_WHITE, 1);
  //drawSplash(GC9A01A_BLACK, 0);
  //drawSplash(GC9A01A_BLACK, 1);
  //drawSplash(uvPurple, 0);
  //drawSplash(monGreen, 1);
  //drawSplash(GC9A01A_BLACK, 1);
  //drawSplash(GC9A01A_BLACK, 0);
  //mainMenu(uvPurple);

  /* this block identifies screen limits
  lcd.drawPixel(35, 35, GC9A01A_WHITE);
  lcd.drawPixel(35, 204, GC9A01A_WHITE);
  lcd.drawPixel(204, 35, GC9A01A_WHITE);
  lcd.drawPixel(204, 204, GC9A01A_WHITE);
  lcd.drawPixel(119, 239, GC9A01A_GREEN);
  lcd.drawPixel(239, 119, GC9A01A_GREEN);
  lcd.fillRoundRect(118, 118, 4, 4, 2, uvPurple);
  lcd.drawPixel(119, 0, GC9A01A_YELLOW);
  lcd.drawPixel(0, 119, GC9A01A_YELLOW);
  lcd.drawPixel(10, 73, GC9A01A_RED);
  lcd.drawPixel(73, 10, GC9A01A_BLUE);
  lcd.drawPixel(10, 167, GC9A01A_BLUE);
  lcd.drawPixel(73, 229, GC9A01A_ORANGE);
  lcd.drawPixel(167, 229, GC9A01A_BLUE);
  lcd.drawPixel(229, 167, GC9A01A_ORANGE);
  lcd.drawPixel(229, 73, GC9A01A_BLUE);
  lcd.drawPixel(167, 10, GC9A01A_RED);*/

    // Main Cross
  lcd.drawLine(119, 119, 0, 119, uvPurple);
  lcd.drawLine(119, 119, 119, 0, uvPurple);
  lcd.drawLine(120, 119, 239, 119, uvPurple);
  lcd.drawLine(119, 120, 119, 239, uvPurple);

  // Qudrant One
  lcd.drawLine(119, 119, 0, 98, _pink);
  lcd.drawLine(119, 119, 0, 74, monGreen);
  lcd.drawLine(119, 119, 0, 42, _blue);
  lcd.drawLine(119, 119, 0, 0, _orange);
  lcd.drawLine(119, 119, 42, 0, _cyan);
  lcd.drawLine(119, 119, 74, 0, _red);
  lcd.drawLine(119, 119, 98, 0, _yellow);

  // Quadrant Two
  lcd.drawLine(119, 120, 98, 239, _pink);
  lcd.drawLine(119, 120, 74, 239, monGreen);
  lcd.drawLine(119, 120, 42, 239, _blue);
  lcd.drawLine(119, 120, 0, 239, _orange);
  lcd.drawLine(119, 120, 239, 42, _cyan);
  lcd.drawLine(119, 120, 0, 164, _red);
  lcd.drawLine(119, 120, 239, 98, _yellow);

  // Quadrant Three
  lcd.drawLine(120, 120, 239, 141, _pink);
  lcd.drawLine(120, 120, 239, 164, monGreen);
  lcd.drawLine(120, 120, 239, 239, _orange);
  lcd.drawLine(120, 120, 164, 239, _red);

  // Quadrant Four
  lcd.drawLine(120, 119, 164, 0, monGreen);
  lcd.drawLine(120, 119, 239, 0, _orange);
  lcd.drawLine(120, 119, 239, 74, _red);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void mainMenu(uint16_t color){
  // cross animation
  // diameter = 240 actual 239
  // radius = 120 actual 119
  // half radius = 0 - 59, 60 -119
  // increment = 2
  uint8_t _incr = 2;
  for (uint8_t i = 0; i <= 119; i += _incr) {
    lcd.drawLine(119, (119 - i), 119, ((119 - i) - _incr), color);  // North
    lcd.drawLine((120 + i), 119, ((120 + i) + _incr), 119, color);  // East
    lcd.drawLine(119, (120 + i), 119, ((120 + i) + _incr), color);  // South
    lcd.drawLine((119 - i), 119, ((119 -i) - _incr), 119, color);  // West
    delay(4);
  }
  // Thicken cross animation
  for (uint8_t i = 0; i <= 119; i += _incr) {
    lcd.fillRect((119 - 1), (119 - i), 3, 2, color); // North
    lcd.fillRect((120 + i), (120 + 1), 2, 3, color); // East
    lcd.fillRect((120 - 1), (120 + i), 3, 2, color); // South
    lcd.fillRect((119 - i), (119 + 1), 2, 3, color); // West
    delay(4);
  }
  // Center circle animation
  for (uint8_t i = 0; i <= 108; i += _incr) {
    lcd.drawRoundRect((119 - (i / 2)), (119 - (i / 2)), i, i, (i / 2), color); // Draw circle
    lcd.fillRoundRect((119 - (i / 2)) + 3, (119 - (i / 2)) + 3, (i - 6), (i - 6), (i / 2), GC9A01A_BLACK); // Clean lines
  }
  // Menu text
  Serial.begin(115200);  // remove when done testing
  while(!Serial);  // remove when done testing
  Serial.println("Drawing main menu");
  lcd.setCursor(77, 125);
  lcd.setTextSize(3);
  lcd.println("START");
  const char* _menu_t[] = {"CONFIG", "HELP", "BATTERY", "SENSOR"}; // Menu titles
  int _menu_xy[][8] = {
    //{15, 25, 35, 45, 60, 70, 80, 90}, // Settings X values
    {13, 21, 33, 35, 45, 55},
    //{165, 180, 190, 200, 205, 215, 225, 230}, // Settings Y values
    {167, 180, 177, 195, 200, 210}, 
    {168, 182, 190, 200}, // Help X
    {210, 203, 188, 185}, // Help Y
    {150, 161, 170, 182, 188, 200, 210}, // Bat X
    {30, 28, 43, 40, 60, 58, 75}, // Bat Y
    {20, 25, 40, 45, 60, 65}, // Sensor X
    {75, 60, 55, 40, 35, 20}  // Sensor Y
  };
  lcd.setTextSize(2);
  Serial.println("Begin title generation logic...");
  for (int _t = 0; _t < sizeof(_menu_t) / sizeof(_menu_t[0]); _t++) {
    //Serial.print("value of _t: ");
    //Serial.println(_t);
    for (int _c = 0; _c <= strlen(_menu_t[_t]); _c++) {
      //Serial.print("value of _c: ");
      //Serial.println(_c);
      lcd.setCursor(int(_menu_xy[_t*2][_c]), int(_menu_xy[(_t*2)+1][_c]));
      //Serial.print("Value for X: ");
      //Serial.println(int(_menu_xy[_t*2][_c]));
      //Serial.print("Value for Y: ");
      //Serial.println(int(_menu_xy[(_t*2)+1][_c]));
      lcd.println(_menu_t[_t][_c]);
    }
  }
}

void drawSplash(uint16_t color, uint16_t color_b) { // color_b = 0 to skip it, 1 to blend
  // x animation
  // increment: 20
  // lcd diameter: 240
  // radius: 120
  int _incr = 10;
  int _add_b = 0;
  if (color_b) {
    _add_b += 5;
  }
  for (int i = 0; i <= 119; i += (_incr + _add_b)) {
    lcd.drawLine((119 - i), 239, (119 + i), 0, color);
    delay(6);
    lcd.drawLine(0, (119 - i), 239, (119 +i), color);
    delay(5);
    lcd.drawLine(0, (239 - i), 239, i, color);
    delay(5);
    lcd.drawLine(i, 0, (239 - i), 239, color);
    delay(5);
  }
}

void shineLight(uint8_t _quad, uint16_t color_a, uint16_t color_b){
  if (_quad == 1){

  }
  //for ()
}