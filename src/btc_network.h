#ifndef _BTC_NETWORK_H_
#define _BTC_NETWORK_H_

#include "ESP8266WiFi.h"

class Btc_Network{
public:
  WiFiClient client;
  
  virtual boolean connect();
  virtual String read();
  virtual float parse(String json);
};
#endif
