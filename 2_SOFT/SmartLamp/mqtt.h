#ifndef _MQTT_H
#define _MQTT_H
#include <stdint.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>

extern PubSubClient client;

struct MqttSettings {
    uint8_t isFerstStart;
    char server[100];         // Адрес MQTT-сервера
    uint16_t port;            // Порт MQTT-сервера
    char username[50];        // Имя пользователя для аутентификации
    char password[50];        // Пароль для аутентификации
    char clientId[50];        // Идентификатор клиента
    char topicSubscribe[100]; // Тема для подписки
    char topicPublish[100];   // Тема для публикации
    uint16_t keepAlive;       //становки временного интервала, через который клиент должен отправлять сообщения "пинг" (PINGREQ) серверу (брокеру)
    int qos;                  // Уровень качества обслуживания (QoS)
    bool retain;              // Флаг Retain
    bool cleanSession;        // Чистая сессия
    char willTopic[100];      // Тема для сообщения последней доброй воли
    char willPayload[100];    // Тело сообщения последней доброй воли
    int willQos;              // Уровень QoS для сообщения последней доброй воли
    bool willRetain;          // Флаг Retain для сообщения последней доброй воли

};
extern MqttSettings mqttSettings;

void loadMqttSetting(void);
void handleSaveMqttSettings(AsyncWebServerRequest *request);
void connectToMqtt();
void callback(char* topic, uint8_t* payload, unsigned int length);

#endif
