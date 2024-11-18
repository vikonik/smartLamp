


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>
//#undef HTTP_ANY
//#include <ESP8266WebServer.h>

#include "config.h"
#include "WiFiManager.h"

#include "WebServer.h"

extern AsyncWebServer asyncServer();




void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password); // Подключаемся к Wi-Fi

  // Запуск веб-сервера
  handleWebRequests();
}

void loop() {
  // put your main code here, to run repeatedly:

}
