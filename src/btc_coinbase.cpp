#include "btc_network.h"
#include "btc_coinbase.h"
#include <ArduinoJson.h>
#include "config.h"

boolean Btc_Coinbase::connect(){
  char server[] = "api.coinbase.com";
  if (client.connect(server, 443)) {
    Serial.println("connected to server");
    // Make a HTTP request:
//    client.println("GET /v2/prices/BTC-GBP/spot/ HTTP/1.1");
//    client.println("GET /v2/prices/BTC-USD/spot/ HTTP/1.1");
    client.println("GET /v2/prices/BTC-CAD/spot/ HTTP/1.1");
    client.println("Host: api.coinbase.com");
    client.println("CB-VERSION:  2017-05-31");
    client.println("Connection: close");
    client.println();

    return true;
  }else{
    return false;
  }
  
}

String Btc_Coinbase::read(){
  String json = "";
  boolean httpBody = false;
  boolean jsonBody = false;
  int count = 0;
  while (client.available()) {
    String line = client.readStringUntil('\r');
    if (!httpBody && line.charAt(1) == '{') {
      httpBody = true;
    }
    if (httpBody) {
      json += line;
      jsonBody = true;
    }
  }
  if(jsonBody){
    return json;
  }else{
    return "";
  }
  
}

float Btc_Coinbase::parse(String json){
    DynamicJsonBuffer jsonBuffer(1000);
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
      Serial.println("JSON parsing failed!");
      return 0;
    }
    float data = root["data"]["amount"];    
    Serial.println(data);
    return data;
}

boolean Btc_Coinbase::connected(){
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();
      delay(REFRESH_DELAY);
      connect();
      return false;
    }else{
      return true;
    }
}

float Btc_Coinbase::readRate(){
      String json = read();
      if(json.length() > 0){
        float rate = parse(json);
        return rate;
      }else{
        return -1.0f;
      }
}

