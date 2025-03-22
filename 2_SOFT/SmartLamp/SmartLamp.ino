

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

#include "config.h"

extern AsyncWebServer asyncServer();






void setup() {
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);//Включаем нагрузку
  Serial.begin(115200);
  delay(5000);
  Serial.println("Ready");
  initLittleFS();
  connectToWiFi(); // Подключаемся к Wi-Fi

  // Запуск веб-сервера
  handleWebRequests();

//Запускаем MQTT
  loadMqttSetting(); //Настройки загрцжаются из файла при инициализации FS
  mqttClientConnect();




}

int mqttReconnectTimer = 0;
int sendToBroker = 0;
void loop() {
  
  if(millis() - mqttReconnectTimer > 5000){
    mqttReconnect();
    mqttReconnectTimer = millis();
    
  }

  if(millis() - sendToBroker > 500){
    senddataToBroker();
    sendToBroker = millis();
  }
   
  // put your main code here, to run repeatedly:
// updateDNS();
 checkMqttrLoop();
}

