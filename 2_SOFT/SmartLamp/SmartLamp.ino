


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>

//#undef HTTP_ANY
//#include <ESP8266WebServer.h>

#include "config.h"
#include "WiFiManager.h"

#include "WebServer.h"
#include "mqtt.h"

extern AsyncWebServer asyncServer();






void setup() {
  pinMode(16, OUTPUT);
  Serial.begin(115200);
  delay(2000);
  Serial.println("Ready");
  connectToWiFi(); // Подключаемся к Wi-Fi

  // Запуск веб-сервера
  handleWebRequests();

//Запускаем MQTT
  loadMqttSetting();
  client.setServer(mqttSettings.server, mqttSettings.port);
  client.setCallback(callback);
  client.setKeepAlive(mqttSettings.keepAlive);  // Указывает, что клиент должен отправлять PINGREQ каждые 60 секунд
  //connectToMqtt();



}

void loop() {
  // put your main code here, to run repeatedly:
// updateDNS();

}

