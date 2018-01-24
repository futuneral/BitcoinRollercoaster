#ifndef _BTC_COINBASE_H_
#define _BTC_COINBASE_H_
#include "btc_network.h"


class Btc_Coinbase{
public:
  WiFiClientSecure client;
  
  virtual boolean connect();
  virtual String read();
  virtual float parse(String json);
  boolean connected();
  float readRate();
  
};
#endif
