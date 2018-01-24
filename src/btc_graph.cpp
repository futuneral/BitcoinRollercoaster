#include "btc_graph.h"
#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <gfxfont.h>
#include <Fonts/FreeSansBold12pt7b.h>
//#include "FreeSansBold12pt7bPound.h"
extern Adafruit_SSD1306 display;
extern float history[];

void Btc_Graph::begin(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.setTextColor(WHITE);
  showConnectionScreen();
  
}

void Btc_Graph::connected(){
  display.clearDisplay();
  setTextParams(NULL, 1, 0, 32);
  display.print("Connected!");
  display.display();
}

void Btc_Graph::setTextParams(const GFXfont *font, int size, int x, int y){
  display.setFont(font);
  display.setTextSize(size);
  display.setCursor(x, y);
}

void Btc_Graph::showConnectionScreen(){
  setTextParams(NULL, 1, 0, 0);
  display.print("Connect to:");

  setTextParams(NULL, 1, 0, 16);
  display.print("\"BtcGuy\" WiFi AP");
  
  setTextParams(NULL, 1, 0, 32);
  display.print("Navigate to:");

  setTextParams(NULL, 1, 0, 48);
  display.print("192.168.4.1");
  display.display();
}

void Btc_Graph::drawGraph(){
  float min =  history[0];
  float max = history[0];
  for(int i=0;i<HISTORY_SIZE;i++){
    if(history[i] < min){
      min = history[i];
    }
    if(history[i] > max){
      max = history[i];
    }
  }

  float ratio = (max - min) / GRAPH_HEIGHT;
  float stepSize = GRAPH_WIDTH / HISTORY_SIZE;
  for(int i=1;i<HISTORY_SIZE;i++){
    display.drawLine(GRAPH_WIDTH - (i-1)*stepSize, SCREEN_HEIGHT - (history[i-1] - min)/ratio, GRAPH_WIDTH - i*stepSize, SCREEN_HEIGHT - (history[i] - min)/ratio, WHITE);
  }
}

void Btc_Graph::drawGraphPillars(){
  const int PILLAR_WIDTH = 4;
  float min =  history[0];
  float max = history[0];
  for(int i=0;i<HISTORY_SIZE;i++){
    if(history[i] < min){
      min = history[i];
    }
    if(history[i] > max){
      max = history[i];
    }
  }

  float ratio = (max - min) / GRAPH_HEIGHT;
  float stepSize = GRAPH_WIDTH / HISTORY_SIZE;
  for(int i=1;i<HISTORY_SIZE;i++){
    int height = (history[i-1] - min)/ratio;
//Bar graph
    display.fillRect(GRAPH_WIDTH - (i-1)*stepSize -PILLAR_WIDTH, SCREEN_HEIGHT - height - 1 , PILLAR_WIDTH, height + 1, WHITE);
// Line graph
//    display.drawLine(GRAPH_WIDTH - (i-1)*stepSize, SCREEN_HEIGHT - (history[i-1] - min)/ratio, GRAPH_WIDTH - i*stepSize, SCREEN_HEIGHT - (history[i] - min)/ratio, WHITE);
  }
}


void Btc_Graph::drawScreen(){
  float rate = history[0];
  float lastRate = history[HISTORY_SIZE - 1];
  float delta = rate - lastRate;
  float deltaP = 100 * ((rate - lastRate) / lastRate);
  
  display.clearDisplay();

  if(delta > 0){
    display.fillTriangle(0, 7, 8, 7, 4, 1, WHITE);
  }else if(delta < 0){
    display.fillTriangle(0, 1, 8, 1, 4, 7, WHITE);
  }
  

  setTextParams(NULL, 1, 20, 0);
  if(delta < 0){
    display.print("-");
  }
  display.print("C$");
//  display.print("$");
//  display.print((char)156); // £ only works on default fonts :(
  display.print(abs(delta));
  display.print(" (");
  display.print(deltaP);
  display.print("%)");

  setTextParams(&FreeSansBold12pt7b, 1, 0, 34);
  display.print("$"); // in FreeSansBold12pt7bPound.h this character is overriden with pound sign
  display.print(rate);

  drawGraphPillars();

  display.display();
}
