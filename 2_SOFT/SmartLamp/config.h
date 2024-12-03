#ifndef CONFIG_H
#define CONFIG_H
#include <EEPROM.h> // Для работы с EEPROM
#include "mqtt.h"

#define   MQTT_STRUCT_ADDR "MQTT_STRUCT_ADDR"
#define   WiFi_STRUCT_ADDR "WiFi_STRUCT_ADDR"

extern const char* ssid;
extern const char* password;
extern const char* mySsid;
extern const char* myPassword;
extern const char* mqtt_server;
extern const char* mqtt_user;
extern const char* mqtt_password;


/*
Ошибка возникает потому, что компилятор не понимает, 
что T — это параметр шаблона. Это происходит из-за неправильного использования шаблона в заголовочном файле. 
Шаблонные функции должны быть определены (а не только объявлены) в заголовочном файле, чтобы компилятор мог их инстанцировать при компиляции.
функцию saveSettings нужно полностью определить в заголовочном файле config.h
*/
#include <Preferences.h>

// Объявляем объект Preferences для работы с flash-памятью
extern Preferences preferences;

// Функция для сохранения структуры в flash
template <typename T>
void saveSettings(const T &settings, const char* key) {
    preferences.begin("settings", false); // Открываем область памяти с именем "settings"
    
    // Записываем данные структуры в flash-память по ключу
    preferences.putBytes(key, &settings, sizeof(T));
    
    preferences.end(); // Закрываем область памяти
    Serial.println("Settings saved for key: " + String(key));
}

// Функция для загрузки структуры из flash
template <typename T>
bool loadSettings(T &settings, const char* key) {
    preferences.begin("settings", true); // Открываем область памяти с именем "settings" в режиме только для чтения

    if (preferences.isKey(key)) {
        // Читаем данные структуры из flash-памяти по ключу
        preferences.getBytes(key, &settings, sizeof(T));
        preferences.end();
        Serial.println("Settings loaded for key: " + String(key));
        return true;
    } else {
        preferences.end();
        Serial.println("Error: Key not found for key: " + String(key));
        return false;
    }
}


#endif // CONFIG_H
