#include "btc_network.h"
#include "btc_coindesk.h"
#include <ArduinoJson.h>
#include "config.h"

boolean Btc_Coindesk::connect(){
  char server[] = "api.coindesk.com";
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /v1/bpi/currentprice.json HTTP/1.1");
    client.println("Host: api.coindesk.com");
    client.println("Connection: close");
    client.println();

    return true;
  }else{
    return false;
  }
  
}

String Btc_Coindesk::read(){
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

float Btc_Coindesk::parse(String json){
    DynamicJsonBuffer jsonBuffer(1000);
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
      Serial.println("JSON parsing failed!");
      return 0;
    }
    float data = root["bpi"]["USD"]["rate_float"];    
    Serial.println(data);
    return data;
}

boolean Btc_Coindesk::connected(){
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

float Btc_Coindesk::readRate(){
      String json = read();
      if(json.length() > 0){
        float rate = parse(json);
        return rate;
      }else{
        return -1.0f;
      }
}

