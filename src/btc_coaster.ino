 #define min(a,b) ((a)<(b)?(a):(b))

#include "config.h"
#include "btc_network.h"
#include "btc_coinbase.h"
#include "btc_graph.h"
#include "ESP8266WiFi.h"
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <Servo.h>


float history[HISTORY_SIZE];
WiFiClient client;
float lastRate = 0;
float lastAngle = 0;
Servo cart;
//Btc_Coindesk net;
Btc_Coinbase net;
Btc_Graph graph;
Adafruit_SSD1306 display(-1);
int demoCount = 0;


void setup() {
  Serial.begin(115200);
  Serial.print("Start: ");
  graph.begin();
  cart.attach(CART_PIN);
  rotateCart((int)MAX_ANGLE);

  if(!DEMO_MODE){
    WiFiManager wifiManager;
    wifiManager.autoConnect("BtcGuy");
    Serial.println(WiFi.localIP());
    graph.connected();
    net.connect();
  }
}

void loop() {
  process();
}

void process(){
  if(DEMO_MODE){
        float rate = 4000.0f + 100.0f * sin((float)demoCount/3 )  ;
  
        push(rate);
        graph.drawScreen();
        positionCart();
        demoCount++;

        delay(2000);
    
  }else{
    if(net.connected()){
      float rate = net.readRate();
      if(rate >= 0){
        push(rate);
        graph.drawScreen();
        positionCart();
      }
    }
  }
}

void positionCart(){
  cart.attach(13);
  float rate = history[0];
  float lastRate = history[HISTORY_SIZE - 1];

  float delta = 100 * ((rate - lastRate) / lastRate);
  Serial.print("Rate: ");
  Serial.println(rate);
  Serial.print("lastRate: ");
  Serial.println(lastRate);
  Serial.print("Delta: ");
  Serial.println(delta);
  
  float angle = delta * DEGREE_PER_PERCENT;
  if(angle > MAX_ANGLE){
    angle = MAX_ANGLE;
  }else if(angle < -MAX_ANGLE){
    angle = -MAX_ANGLE;
  }
  angle = angle + MAX_ANGLE;

  interpolateAngle(lastAngle, angle);
  
  lastAngle = angle;
  delay(1000);
  cart.detach();
}

void rotateCart(int angle){
  cart.write(angle + MECHANICAL_OFFSET);
}

void interpolateAngle(float start, float finish){
  int count = (int)abs(finish - start);
  float currentAngle = start;
  float angleStep = finish > start ? 1.0f : -1.0f;
  for(int i=0;i<count;i++){
    rotateCart((int)currentAngle);
    currentAngle += angleStep;
    delay((int)(1000.0f / SPEED_DEG_PER_S));
  }
}


void push(float rate){
  if(history[0] == 0){
    for(int i=0;i<HISTORY_SIZE;i++){
      history[i] = rate;
    }
  }

  for(int i=HISTORY_SIZE-1; i>0;i--){
    history[i] = history[i-1];
  }
  history[0] = rate;
}



