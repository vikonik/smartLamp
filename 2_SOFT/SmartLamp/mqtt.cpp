#include "mqtt.h"
#include "config.h"

#include <PubSubClient.h>



//Надо для работы MQTT
WiFiClient espClient;
PubSubClient mqttClient(espClient);

MqttSettings_t mqttSettingsDefailt = {
  123,                    //Просто маркер
  "mqtt.example.com",     // server
  1883,                   // port
  "username",             // username
  "password",             // password
  "clientId",             // clientId
  "topic/sub",            // topicSubscribe
  "topic/pub",            // topicPublish
  60,                     // keepAlive
  1,                      // qos
  true,                   // retain
  true,                   // cleanSession
  "lastWillTopic",        // willTopic
  "Device disconnected",  // willPayload
  1,                      // willQos
  false                   // willRetain
};

MqttSettings_t mqttSettings;



/**/
void loadMqttSetting(void) {
  //  loadSettings(mqttSettings, MQTT_STRUCT_ADDR);//0 это адрес начала
  //   if(mqttSettings.isFerstStart != mqttSettingsDefailt.isFerstStart){
  //     saveSettings(mqttSettingsDefailt,MQTT_STRUCT_ADDR);
  //   }
  //   loadSettings(mqttSettings,MQTT_STRUCT_ADDR);

  //  printStruct(mqttSettings);
}

/*
Сохраним настройки
*/
void handleSaveMqttSettings(AsyncWebServerRequest* request) {
  if (request->hasParam("mqttServer", true)) {
    String serverParam = request->getParam("mqttServer", true)->value();
    strncpy(mqttSettings.server, serverParam.c_str(), sizeof(mqttSettings.server) - 1);
    mqttSettings.server[sizeof(mqttSettings.server) - 1] = '\0';
  }

  if (request->hasParam("mqttPort", true)) {
    mqttSettings.port = request->getParam("mqttPort", true)->value().toInt();
  }

  if (request->hasParam("mqttUsername", true)) {
    String usernameParam = request->getParam("mqttUsername", true)->value();
    strncpy(mqttSettings.username, usernameParam.c_str(), sizeof(mqttSettings.username) - 1);
    mqttSettings.username[sizeof(mqttSettings.username) - 1] = '\0';
  }

  if (request->hasParam("mqttPassword", true)) {
    String passwordParam = request->getParam("mqttPassword", true)->value();
    strncpy(mqttSettings.password, passwordParam.c_str(), sizeof(mqttSettings.password) - 1);
    mqttSettings.password[sizeof(mqttSettings.password) - 1] = '\0';
  }

  if (request->hasParam("mqttClientId", true)) {
    String clientIdParam = request->getParam("mqttClientId", true)->value();
    strncpy(mqttSettings.clientId, clientIdParam.c_str(), sizeof(mqttSettings.clientId) - 1);
    mqttSettings.clientId[sizeof(mqttSettings.clientId) - 1] = '\0';
  }

  if (request->hasParam("mqttSubscribe", true)) {
    String subscribeParam = request->getParam("mqttSubscribe", true)->value();
    strncpy(mqttSettings.topicSubscribe, subscribeParam.c_str(), sizeof(mqttSettings.topicSubscribe) - 1);
    mqttSettings.topicSubscribe[sizeof(mqttSettings.topicSubscribe) - 1] = '\0';
  }

  if (request->hasParam("mqttPublish", true)) {
    String publishParam = request->getParam("mqttPublish", true)->value();
    strncpy(mqttSettings.topicPublish, publishParam.c_str(), sizeof(mqttSettings.topicPublish) - 1);
    mqttSettings.topicPublish[sizeof(mqttSettings.topicPublish) - 1] = '\0';
  }

  if (request->hasParam("mqttKeepAlive", true)) {
    mqttSettings.keepAlive = request->getParam("mqttKeepAlive", true)->value().toInt();
  }

  if (request->hasParam("mqttQoS", true)) {
    mqttSettings.qos = request->getParam("mqttQoS", true)->value().toInt();
  }

  if (request->hasParam("mqttRetain", true)) {
    mqttSettings.retain = request->getParam("mqttRetain", true)->value() == "true";
  }

  if (request->hasParam("mqttCleanSession", true)) {
    mqttSettings.cleanSession = request->getParam("mqttCleanSession", true)->value() == "true";
  }

  if (request->hasParam("mqttWillTopic", true)) {
    String willTopicParam = request->getParam("mqttWillTopic", true)->value();
    strncpy(mqttSettings.willTopic, willTopicParam.c_str(), sizeof(mqttSettings.willTopic) - 1);
    mqttSettings.willTopic[sizeof(mqttSettings.willTopic) - 1] = '\0';
  }

  if (request->hasParam("mqttWillPayload", true)) {
    String willPayloadParam = request->getParam("mqttWillPayload", true)->value();
    strncpy(mqttSettings.willPayload, willPayloadParam.c_str(), sizeof(mqttSettings.willPayload) - 1);
    mqttSettings.willPayload[sizeof(mqttSettings.willPayload) - 1] = '\0';
  }

  if (request->hasParam("mqttWillQos", true)) {
    mqttSettings.willQos = request->getParam("mqttWillQos", true)->value().toInt();
  }

  if (request->hasParam("mqttWillRetain", true)) {
    mqttSettings.willRetain = request->getParam("mqttWillRetain", true)->value() == "true";
  }

  saveSettings(mqttSettings, "/mqttSettings.dat");
  request->redirect("/settings");  // Перенаправить пользователя на страницу с настройками после сохранения
}

/**/
void connectToMqtt() {
  int cnt = 0;
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    Serial.print("Connecting to broker: ");
    Serial.print(mqttSettings.server);
    Serial.print(":");
    Serial.println(mqttSettings.port);

    if (mqttClient.connect(
          mqttSettings.clientId,
          mqttSettings.username,
          mqttSettings.password,
          mqttSettings.willTopic,
          mqttSettings.willQos,
          mqttSettings.willRetain,
          mqttSettings.willPayload)) {
      Serial.println("Connected to MQTT");
      mqttClient.subscribe(mqttSettings.topicSubscribe);  // Подписка на тему
      mqttClient.publish(mqttSettings.topicPublish, "Connect");
    } else {
      cnt++;
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
    if (cnt > 5) return;
  }
}

/**/
void mqttReconnect() {

  if (!mqttClient.connected()) {
    Serial.println("MQTT reconnect");
    if (mqttClient.connect(
          mqttSettings.clientId,
          mqttSettings.username,
          mqttSettings.password,
          mqttSettings.willTopic,
          mqttSettings.willQos,
          mqttSettings.willRetain,
          mqttSettings.willPayload)) {
      Serial.println("Connected to MQTT");
      mqttClient.subscribe(mqttSettings.topicSubscribe);  // Подписка на тему
      mqttClient.publish(mqttSettings.topicPublish, "Reconnect");
    }
  }
}

/**/
void checkMqttrLoop() {
  if (mqttClient.connected()) {
    mqttClient.loop();
  }
}
/**/
void mqttClientConnect() {
  mqttClient.setServer(mqttSettings.server, mqttSettings.port);
  mqttClient.setCallback(callback);
  mqttClient.setKeepAlive(mqttSettings.keepAlive);  // Указывает, что клиент должен отправлять PINGREQ каждые 60 секунд
  connectToMqtt();
}

/**/
void callback(char* topic, uint8_t* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Преобразование payload в строку
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Обработка команды
  if (String(topic) == mqttSettings.topicSubscribe) {
    if (message == "ON") {
      // Включить устройство
      Serial.println("Нагрузка включена MQTT");
      digitalWrite(16, HIGH);
    } else if (message == "OFF") {
      // Выключить устройство
      Serial.println("Нагрузка выключена MQTT");
      digitalWrite(16, LOW);
    } else {
      Serial.println("Unknown command");
    }
  }
}

/**/
char buf[128];
void senddataToBroker() {

  sprintf(buf, "%s", digitalRead(16) ? "ON":"OFF");

  mqttClient.publish(mqttSettings.topicPublish, buf);
  // Serial.println(buf);
}