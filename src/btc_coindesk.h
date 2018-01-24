#ifndef _BTC_COINDESK_H_
#define _BTC_COINDESK_H_
#include "btc_network.h"

class Btc_Coindesk{
public:
  WiFiClient client;
  
  virtual boolean connect();
  virtual String read();
  virtual float parse(String json);
  boolean connected();
  float readRate();
  
};
#endif
