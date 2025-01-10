#include <iterator>
#include "config.h"
#include "mqtt.h"
#include "WiFiManager.h"

extern WiFiSettings_t wifiSettingsDefault;
extern MqttSettings_t mqttSettingsDefailt;

Password_t inputPassword;
Password_t inputPasswordDefault={"Humster",true};
// Настройки Wi-Fi
// const char* ssid = "Vikonik";          // Имя вашей сети Wi-Fi
// const char* password = "88115221421";  // Пароль от Wi-Fi

// const char* mySsid = "SmartLamp_AP";          // Имя вашей сети Wi-Fi
// const char* myPassword = "00000000";  // Пароль от Wi-Fi

// Настройки MQTT (в будущем, когда будем реализовывать MQTT)
const char* mqtt_server = "broker_address";
const int mqtt_port = 1883;              // Порт MQTT, по умолчанию 1883
const char* mqtt_user = "mqtt_user";     // Имя пользователя MQTT
const char* mqtt_password = "mqtt_password"; // Пароль MQTT



// Другие настройки можно добавлять здесь...

/**/


void initLittleFS(void){

     if (!LittleFS.begin()) {
        Serial.println("Ошибка монтирования LittleFS!");
        while(1);
    } 

// Проверка на наличие файлов настроек
    if (!LittleFS.exists("/mqttSettings.dat") || !LittleFS.exists("/wifiSettings.dat") || !LittleFS.exists("/passwordSettings.dat")) {
        // Если файлов нет, это первый запуск — заполняем значениями по умолчанию

        Serial.println("Первый запуск или файлы не найдены. Заполняем настройки по умолчанию.");

        // Сохраняем настройки в файлы
        saveSettings(mqttSettingsDefailt, "/mqttSettings.dat");
        saveSettings(wifiSettingsDefault, "/wifiSettings.dat");
        saveSettings(inputPasswordDefault, "/passwordSettings.dat");

    } else {
        // Если файлы существуют, загружаем их
        Serial.println("Загружаем настройки из файлов.");
        loadSettings(mqttSettings, "/mqttSettings.dat");
        loadSettings(wifiSettings, "/wifiSettings.dat");
        loadSettings(inputPassword, "/passwordSettings.dat");        
    }    
}

/*
Возврат к заводским настройкам
*/
void factoryReset(void){
        Serial.println("Восстанавливаем заводские настройки.");
        saveSettings(mqttSettingsDefailt, "/mqttSettings.dat");
        saveSettings(wifiSettingsDefault, "/wifiSettings.dat");
        saveSettings(inputPasswordDefault, "/passwordSettings.dat");
        Serial.println("Загружаем настройки из файлов.");
        loadSettings(mqttSettings, "/mqttSettings.dat");
        loadSettings(wifiSettings, "/wifiSettings.dat");
        loadSettings(inputPassword, "/passwordSettings.dat");          
}


