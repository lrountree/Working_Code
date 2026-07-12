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
#define _fuchsia GC9A01A_MAGENTA
#define _brown GC9A01A_GREENYELLOW

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
  lcd.drawLine(120, 119, 240, 119, uvPurple);
  lcd.drawLine(119, 120, 119, 240, uvPurple);

  // Qudrant One
  lcd.drawLine(119, 119, 0, 104, _white);
  lcd.drawLine(119, 119, 0, 89, monGreen);
  lcd.drawLine(119, 119, 0, 74, _white);
  lcd.drawLine(119, 119, 0, 59, _blue);
  lcd.drawLine(119, 119, 0, 44, _white);
  lcd.drawLine(119, 119, 0, 29, _red);
  lcd.drawLine(119, 119, 0, 14, _white);
  lcd.drawLine(119, 119, 0, 0, _orange);
  lcd.drawLine(119, 119, 14, 0, _white);
  lcd.drawLine(119, 119, 29, 0, _cyan);
  lcd.drawLine(119, 119, 44, 0, _white);
  lcd.drawLine(119, 119, 59, 0, _pink);
  lcd.drawLine(119, 119, 74, 0, _white);
  lcd.drawLine(119, 119, 89, 0, _yellow);
  lcd.drawLine(119, 119, 104, 0, _white);

  // Quadrant Two
  lcd.drawLine(119, 120, 134, 1, _white);
  lcd.drawLine(119, 120, 149, 1, monGreen);
  lcd.drawLine(119, 120, 164, 1, _white);
  lcd.drawLine(119, 120, 179, 1, _blue);
  lcd.drawLine(119, 120, 194, 1, _white);
  lcd.drawLine(119, 120, 209, 1, _red);
  lcd.drawLine(119, 120, 224, 1, _white);
  lcd.drawLine(119, 120, 239, 1, _orange);
  lcd.drawLine(119, 120, 239, 15, _white);
  lcd.drawLine(119, 120, 239, 30, _cyan);
  lcd.drawLine(119, 120, 239, 45, _white);
  lcd.drawLine(119, 120, 239, 60, _pink);
  lcd.drawLine(119, 120, 239, 75, _white);
  lcd.drawLine(119, 120, 239, 90, _yellow);
  lcd.drawLine(119, 120, 239, 105, _white);

  // Quadrant Three
  lcd.drawLine(120, 120, 240, 135, _white);
  lcd.drawLine(120, 120, 240, 150, monGreen);
  lcd.drawLine(120, 120, 240, 165, _white);
  lcd.drawLine(120, 120, 240, 180, _blue);
  lcd.drawLine(120, 120, 240, 195, _white);
  lcd.drawLine(120, 120, 240, 210, _red);
  lcd.drawLine(120, 120, 240, 225, _white);
  lcd.drawLine(120, 120, 240, 240, _orange);
  lcd.drawLine(120, 120, 225, 240, _white);
  lcd.drawLine(120, 120, 210, 240, _cyan);
  lcd.drawLine(120, 120, 195, 240, _white);
  lcd.drawLine(120, 120, 180, 240, _pink);
  lcd.drawLine(120, 120, 165, 240, _white);
  lcd.drawLine(120, 120, 150, 240, _yellow);
  lcd.drawLine(120, 120, 135, 240, _white);

  // Quadrant Four
  lcd.drawLine(120, 119, 105, 238, _white);
  lcd.drawLine(120, 119, 90, 239, monGreen);
  lcd.drawLine(120, 119, 75, 239, _white);
  lcd.drawLine(120, 119, 60, 239, _blue);
  lcd.drawLine(120, 119, 45, 239, _white);
  lcd.drawLine(120, 119, 30, 239, _red);
  lcd.drawLine(120, 119, 15, 239, _white);
  lcd.drawLine(120, 119, 1, 239, _orange);
  lcd.drawLine(120, 119, 1, 224, _white);
  lcd.drawLine(120, 119, 1, 209, _cyan);
  lcd.drawLine(120, 119, 1, 194, _white);
  lcd.drawLine(120, 119, 1, 179, _pink);
  lcd.drawLine(120, 119, 1, 164, _white);
  lcd.drawLine(120, 119, 1, 149, _yellow);
  lcd.drawLine(120, 119, 1, 134, _white);
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