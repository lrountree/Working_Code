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
  //lcd.drawLine(119, 119, 0, 119, uvPurple);
  //lcd.drawLine(119, 119, 119, 0, uvPurple);
  //lcd.drawLine(120, 119, 240, 119, uvPurple);
  //lcd.drawLine(119, 120, 119, 240, uvPurple);

  // Qudrant One
  //lcd.drawLine(119, 119, 0, 104, _white);
  //lcd.drawLine(119, 119, 0, 89, monGreen);
  //lcd.drawLine(119, 119, 0, 74, _white);
  //lcd.drawLine(119, 119, 0, 59, _blue);
  //lcd.drawLine(119, 119, 0, 44, _white);
  //lcd.drawLine(119, 119, 0, 29, _red);
  //lcd.drawLine(119, 119, 0, 14, _white);
  //lcd.drawLine(119, 119, 0, 0, _orange);
  //lcd.drawLine(119, 119, 14, 0, _white);
  //lcd.drawLine(119, 119, 29, 0, _cyan);
  //lcd.drawLine(119, 119, 44, 0, _white);
  //lcd.drawLine(119, 119, 59, 0, _pink);
  //lcd.drawLine(119, 119, 74, 0, _white);
  //lcd.drawLine(119, 119, 89, 0, _yellow);
  //lcd.drawLine(119, 119, 104, 0, _white);

  // Quadrant Two
  //lcd.drawLine(119, 120, 134, 1, _white);
  //lcd.drawLine(119, 120, 149, 1, monGreen);
  //lcd.drawLine(119, 120, 164, 1, _white);
  //lcd.drawLine(119, 120, 179, 1, _blue);
  //lcd.drawLine(119, 120, 194, 1, _white);
  //lcd.drawLine(119, 120, 209, 1, _red);
  //lcd.drawLine(119, 120, 224, 1, _white);
  //lcd.drawLine(119, 120, 239, 1, _orange);
  //lcd.drawLine(119, 120, 239, 15, _white);
  //lcd.drawLine(119, 120, 239, 30, _cyan);
  //lcd.drawLine(119, 120, 239, 45, _white);
  //lcd.drawLine(119, 120, 239, 60, _pink);
  //lcd.drawLine(119, 120, 239, 75, _white);
  //lcd.drawLine(119, 120, 239, 90, _yellow);
  //lcd.drawLine(119, 120, 239, 105, _white);

  // Quadrant Three
  //lcd.drawLine(120, 120, 240, 135, _white);
  //lcd.drawLine(120, 120, 240, 150, monGreen);
  //lcd.drawLine(120, 120, 240, 165, _white);
  //lcd.drawLine(120, 120, 240, 180, _blue);
  //lcd.drawLine(120, 120, 240, 195, _white);
  //lcd.drawLine(120, 120, 240, 210, _red);
  //lcd.drawLine(120, 120, 240, 225, _white);
  //lcd.drawLine(120, 120, 240, 240, _orange);
  //lcd.drawLine(120, 120, 225, 240, _white);
  //lcd.drawLine(120, 120, 210, 240, _cyan);
  //lcd.drawLine(120, 120, 195, 240, _white);
  //lcd.drawLine(120, 120, 180, 240, _pink);
  //lcd.drawLine(120, 120, 165, 240, _white);
  //lcd.drawLine(120, 120, 150, 240, _yellow);
  //lcd.drawLine(120, 120, 135, 240, _white);

  // Quadrant Four
  //lcd.drawLine(120, 119, 105, 238, _white);
  //lcd.drawLine(120, 119, 90, 239, monGreen);
  //lcd.drawLine(120, 119, 75, 239, _white);
  //lcd.drawLine(120, 119, 60, 239, _blue);
  //lcd.drawLine(120, 119, 45, 239, _white);
  //lcd.drawLine(120, 119, 30, 239, _red);
  //lcd.drawLine(120, 119, 15, 239, _white);
  //lcd.drawLine(120, 119, 1, 239, _orange);
  //lcd.drawLine(120, 119, 1, 224, _white);
  //lcd.drawLine(120, 119, 1, 209, _cyan);
  //lcd.drawLine(120, 119, 1, 194, _white);
  //lcd.drawLine(120, 119, 1, 179, _pink);
  //lcd.drawLine(120, 119, 1, 164, _white);
  //lcd.drawLine(120, 119, 1, 149, _yellow);
  //lcd.drawLine(120, 119, 1, 134, _white);
  //int _test1 = 1;
  //if (!_test1) {
  //  Serial.println("FALSE");
  //} else {
  //  Serial.println("TRUE");
 //}
  // Opening graphic
  lcd.drawLine(119, 119, 0, 119, uvPurple);
  shineLight(1, uvPurple, false);
  lcd.drawLine(119, 119, 119, 0, uvPurple);
  shineLight(2, uvPurple, false);
  lcd.drawLine(120, 119, 240, 119, uvPurple);
  shineLight(3, uvPurple, false);
  lcd.drawLine(119, 120, 119, 240, uvPurple);
  shineLight(4, uvPurple, false);
  shineLight(1, monGreen, true);
  shineLight(2, monGreen, true);
  shineLight(3, monGreen, true);
  shineLight(4, monGreen, true);
  drawCross(_black, "thin");
  for (int _i = 1; _i <= 4; _i++) {
    shineLight(_i, _black, false);
    shineLight(_i, _black, true);
  }
  // draw main menu
  mainMenu("init", 0, uvPurple);
  mainMenu("full", 2, monGreen);
  // start with start selected
  mainMenu("start", 2, _black);
  mainMenu("start", 3, monGreen);
  delay(1000);
  // start scan
  scanMenu(monGreen);
  //delay(4000);
  //lcd.fillScreen(_black);
  //drawCross(uvPurple, "thin");
  //drawCross(uvPurple, "thick");
  //drawShape(uvPurple, "circle");
  //mainMenu("full", 2, monGreen);
  //mainMenu("start", 2, _black);
  //mainMenu("start", 3, monGreen);
  // select  config
  //mainMenu("start", 3, _black);
  //mainMenu("start", 2, monGreen);
  //delay(1000);
  //mainMenu("start", 2, _black);
  //for (uint8_t _i = 1; _i <= 4; _i++) {
  //  lcd.drawCircleHelper(119, 119, (50 + _i), 0x8, _black);
  //  lcd.drawCircleHelper(120, 120, (50 + _i), 0x8, _black);
  //}
  //mainMenu("config", 2, _black);
  //shineLight(4, uvPurple, false);
  //shineLight(4, uvPurple, true);
  //mainMenu("config", 3, monGreen);
  //delay(1000);
}

void loop() {
  // void
}

void drawCross(uint16_t _color, const char* _cross) {
  uint8_t _incr = 2;
  // Draw menu cross
  if (_cross == "thin") {
    for (uint8_t i = 0; i <= 120; i += _incr) {
      lcd.drawLine(119, (119 - i), 119, ((119 - i) - _incr), _color);  // North
      lcd.drawLine((120 + i), 119, ((120 + i) + _incr), 119, _color);  // East
      lcd.drawLine(119, (120 + i), 119, ((120 + i) + _incr), _color);  // South
      lcd.drawLine((119 - i), 119, ((119 -i) - _incr), 119, _color);  // West
      delay(10);
    }
  } else if (_cross == "thick") {
    for (uint8_t i = 0; i <= 120; i += _incr) {
      lcd.fillRect(118, (119 - i), 3, 2, _color); // North
      lcd.fillRect((120 + i), 118, 2, 3, _color); // East
      lcd.fillRect(118, (120 + i), 3, 2, _color); // South
      lcd.fillRect((119 - i), 118, 2, 3, _color); // West
      delay(10);
    }
  } else if (_cross == "reduce") {
      lcd.drawRect(0, 118, 120, 3, _color);
      lcd.drawRect(118, 0, 3, 120, _color);
      lcd.drawRect(119, 118, 121, 3, _color);
      lcd.drawRect(118, 119, 3, 121, _color);
  } else if (_cross == "vert") {
    for (uint8_t i = 0; i <= 7; i++) {
      lcd.drawLine(119, 119, 0, (119 - (i * 15)), _color);
      lcd.drawLine(120, 119, 240, (119 + (i * 15)), _color);
      lcd.drawLine(119, 119, 0, (119 - (i * 15)), _black);
      lcd.drawLine(120, 119, 240, (119 + (i * 15)), _black);
      delay(5);
    }
    for (uint8_t i = 0; i <= 7; i++) {
      lcd.drawLine(119, 119, (0 + (i * 15)), 0, _color);
      lcd.drawLine(120, 120, (240 - (i * 15)), 240, _color);
      lcd.drawLine(119, 119, (0 + (i * 15)), 0, _black);
      lcd.drawLine(120, 120, (240 - (i * 15)), 240, _black);
      delay(5);
    }
  } else if (_cross == "horz") {
    for (uint8_t i = 0; i <= 7; i++) {
      lcd.drawLine(119, 119, (119 + (i * 15)), 0, _color);
      lcd.drawLine(119, 120, (119 - (i * 15)), 240, _color);
      lcd.drawLine(119, 119, (119 + (i * 15)), 0, _black);
      lcd.drawLine(119, 120, (119 - (i * 15)), 240, _black);
      delay(5);
    }
    for (uint8_t i = 0; i <= 7; i++) {
      lcd.drawLine(120, 119, 240, (0 + (i * 15)), _color);
      lcd.drawLine(119, 120, 0, (240 - (i * 15)), _color);
      lcd.drawLine(120, 119, 240, (0 + (i * 15)), _black);
      lcd.drawLine(119, 120, 0, (240 - (i * 15)), _black);
      delay(5);
    }
  }
}

void drawShape(uint16_t _color, const char* _shape) {
  // Draw center circle
  if (_shape == "circle") {
    for (uint8_t i = 0; i <= 108; i += 2) {
      lcd.drawRoundRect((119 - (i / 2)), (119 - (i / 2)), i, i, (i / 2), _color); // Draw circle
      lcd.fillRoundRect((119 - (i / 2)) + 3, (119 - (i / 2)) + 3, (i - 6), (i - 6), (i / 2), _black); // Clean lines
    }
  } else if (_shape == "start") {
    for (uint8_t i = 0; i <= 108; i += 4) {
      lcd.drawRoundRect((119 - (i / 2)), (119 - (i / 2)), i, i, (i / 2), _color);
    }
  } else if (_shape == "shrink") {
    for (uint8_t i = 108; i > 2; i -= 2) {
      lcd.drawRoundRect((119 - (i / 2)), (119 - (i / 2)), i, i, (i / 2), _color);
      lcd.fillRect((119 - (i / 2)), 118, 2, 3, uvPurple);
      lcd.fillRect(118, (119 - (i / 2)), 3, 2, uvPurple);
      lcd.fillRect(((120 + (i / 2)) - 2), 118, 2, 3, uvPurple);
      lcd.fillRect(118, ((120 + (i / 2)) + 2), 3, 2, uvPurple);
    }
  }
}

void mainMenu(const char* _title, uint8_t _size, uint16_t _color) {
  // Menu text
  const char* _menu_t[] = {"CONFIG", "HELP", "BATTERY", "SENSOR"}; // Menu titles
  int _menu_xy[][10] = {
    {22, 32, 42, 52, 62, 72}, // Config X values
    {170, 182, 192, 202, 208, 214}, // Config Y values
    {175, 187, 197, 205}, // Help X
    {210, 200, 190, 180}, // Help Y
    {150, 161, 170, 182, 188, 200, 210}, // Bat X
    {30, 28, 43, 40, 60, 58, 75}, // Bat Y
    {20, 27, 40, 45, 58, 68}, // Sensor X
    {75, 58, 55, 40, 33, 20}  // Sensor Y
  };
  if (_title == "init") {
    drawCross(_color, "thin");
    drawCross(_color, "thick");
    drawShape(_color, "circle");
  } else if (_title == "full") {
    lcd.setTextColor(_color);
    lcd.setTextSize(_size);
    lcd.setCursor(92, 121);
    lcd.println("START");
    for (int _t = 0; _t < sizeof(_menu_t) / sizeof(_menu_t[0]); _t++) {
      for (int _c = 0; _c <= strlen(_menu_t[_t]); _c++) {
        lcd.setCursor(int(_menu_xy[_t*2][_c]), int(_menu_xy[(_t*2)+1][_c]));
        lcd.println(_menu_t[_t][_c]);
      }
    }
  } else if (_title == "start") {
    if (_size == 2) {
      lcd.setCursor(92, 121);
    } else if (_size == 3) {
      lcd.setCursor(77, 125);
    }
    lcd.setTextSize(_size);
    lcd.setTextColor(_color);
    lcd.println("START");
  } else if (_title == "config") {
    lcd.setTextSize(_size);
    lcd.setTextColor(_color);
    for (int _c = 0; _c <= strlen(_menu_t[0]); _c++) {
      lcd.setCursor(int(_menu_xy[0][_c]), int(_menu_xy[1][_c]));
      lcd.println(_menu_t[0][_c]);
    }
  } else if (_title == "help") {
    lcd.setTextSize(_size);
    lcd.setTextColor(_color);
    for (int _c = 0; _c <= strlen(_menu_t[1]); _c++) {
      lcd.setCursor(int(_menu_xy[2][_c]), int(_menu_xy[3][_c]));
      lcd.println(_menu_t[1][_c]);
    }
  }
}

void shineLight(uint8_t _quad, uint16_t color_a, bool color_b) {
  int _s;
  int _s2;
  int _e;
  int _e2;
  if (_quad == 1){
    if (color_b) {
      _s = 104;
      _e = 14;
    } else {
      _s = 89;
      _e = 29;
    }
    for (int _x=_s; _x>=_e; _x-=30) {
      lcd.drawLine(119, 119, 0, _x, color_a);
      delay(5);
    }
    if (!color_b){lcd.drawLine(119, 119, 0, 0, color_a);}
    delay(5);
    for (int _x=_e; _x<=_s; _x+=30) {
      lcd.drawLine(119, 119, _x, 0, color_a);
      delay(5);
    }
  } else if (_quad == 2) {
    if (color_b) {
      _s = 119;
      _s2 = 15;
      _e = 224;
      _e2 = 105;
    } else {
      _s = 134;
      _s2 = 30;
      _e = 209;
      _e2 = 90;
    }
    for (int _x=_s; _x<=_e; _x+=30) {
      lcd.drawLine(120, 119, _x, 1, color_a);
      delay(5);
    }
    if (!color_b){lcd.drawLine(120, 119, 239, 1, color_a);}
    delay(5);
    for (int _x=_s2; _x<=_e2; _x+=30) {
      lcd.drawLine(120, 119, 239, _x, color_a);
      delay(5);
    }
  } else if (_quad == 3) {
    if (color_b) {
      _s = 135;
      _e = 225;
    } else {
      _s = 150;
      _e = 210;
    }
    for (int _x=_s; _x<=_e; _x+=30) {
      lcd.drawLine(120, 120, 240, _x, color_a);
      delay(5);
    }
    if (!color_b){lcd.drawLine(120, 120, 240, 240, color_a);}
    delay(5);
    for (int _x=_e; _x>=_s; _x-=30) {
      lcd.drawLine(120, 120, _x, 240, color_a);
      delay(5);
    }
  } else if (_quad == 4) {
    if (color_b) {
      _s = 105;
      _s2 = 224;
      _e = 15;
      _e2 = 134;
    } else {
      _s = 90;
      _s2 = 209;
      _e = 30;
      _e2 = 149;
    }
    for (int _x=_s; _x>=_e; _x-=30) {
      lcd.drawLine(119, 120, _x, 239, color_a);
      delay(5);
    }
    if (!color_b){lcd.drawLine(119, 120, 1, 239, color_a);}
    delay(5);
    for (int _x=_s2; _x>=_e2; _x-=30) {
      lcd.drawLine(119, 120, 1, _x, color_a);
      delay(5);
    }
  }
}

void scanMenu(uint16_t _color) {
  drawShape(uvPurple, "start");
  mainMenu("start", 3, _black);
  drawShape(_black, "shrink");
  mainMenu("full", 2, _black);
  drawCross(_black, "reduce");
  drawCross(uvPurple, "thin");
  shineLight(1, uvPurple, false);
  delay(100);
  shineLight(3, uvPurple, false);
  delay(100);
  shineLight(2, uvPurple, false);
  delay(100);
  shineLight(4, uvPurple, false);
  delay(100);
  for (int _i = 1; _i <= 4; _i++) {
    shineLight(_i, _black, false);
    delay(100);
  }
  drawCross(uvPurple, "thin");
  drawCross(uvPurple, "horz");
  for (uint8_t _i = 0; _i <= 3; _i++) {
    lcd.drawRoundRect((3 - _i), (63 - _i), (233 + (_i * 2)), (112 + (2 * _i)), (57 + _i), _color);
    lcd.drawCircle(119, 119, (55 + _i), _color);
    lcd.drawLine(0, (118 + _i), 240, (118 + _i), _color);
  }
  lcd.fillCircle(119, 240, 10, _white);
  lcd.fillCircle(119, 0, 10, uvPurple);
  for (uint8_t _i = 0; _i <= 88; _i += 22) {
    lcd.drawLine(119, 240, (75 + _i), 210, _white);
    lcd.drawLine(119, 0, (75 + _i), 30, uvPurple);
  }
  lcd.setTextColor(_color); lcd.setTextSize(2); lcd.setCursor(13, 108); lcd.println("HOLD"); lcd.setCursor(13, 138); lcd.println("EXIT");
  lcd.setTextColor(uvPurple); lcd.setCursor(75, 48); lcd.println("12345"); 
  lcd.setCursor(175, 48); lcd.println("10"); lcd.setCursor(183, 100); 
  lcd.println("365"); lcd.setTextSize(1); lcd.setCursor(47, 48); 
  lcd.println("Live: "); lcd.setCursor(148, 48); lcd.println("UVI: "); 
  lcd.setCursor(112, 75); lcd.println("Avg:"); lcd.setCursor(180, 75); 
  lcd.println("NM"); lcd.setTextSize(3); lcd.setCursor(85, 103); 
  lcd.println("8888"); lcd.setTextSize(1); lcd.setTextColor(_white); 
  lcd.setCursor(65, 190); lcd.println("Live: "); lcd.setCursor(112, 165); 
  lcd.println("Avg:"); lcd.setCursor(180, 165); lcd.println("NM"); 
  lcd.setTextSize(2); lcd.setCursor(98, 195); lcd.println("12345"); 
  lcd.setCursor(183, 145); lcd.println("600"); lcd.setTextSize(3); 
  lcd.setCursor(85, 145); lcd.println("8888");
}
