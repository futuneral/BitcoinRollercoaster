#ifndef _BTC_GRAPH_H_
#define _BTC_GRAPH_H_
#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>

class Btc_Graph{

public:
//  Adafruit_SSD1306 display;
  void connected();
  void begin();
  void setTextParams(const GFXfont *font, int size, int x, int y);
  void showConnectionScreen();
  void drawGraph();
  void drawGraphPillars();
  void drawScreen();

};
#endif
