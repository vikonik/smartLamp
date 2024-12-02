#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h> // Подключение библиотеки для работы с Wi-Fi

typedef struct WiFiSettings {
    uint8_t isFerstStart;    //Маркер
    char ssid[32];           // Название сети Wi-Fi (SSID)
    char password[64];       // Пароль Wi-Fi
    bool useStaticIP;        // Флаг использования статического IP (true - статический, false - динамический)
    char staticIP[16];       // Статический IP-адрес (например, "192.168.1.100")
    char gateway[16];        // Адрес шлюза (например, "192.168.1.1")
    char subnet[16];         // Маска подсети (например, "255.255.255.0")
    char dns1[16];           // Основной DNS-сервер (например, "8.8.8.8")
    char dns2[16];           // Дополнительный DNS-сервер (например, "8.8.4.4")
    char hostname[50];        // Имя хоста (hostname) устройства
}WiFiSettings_t;
extern WiFiSettings_t WiFiSettings;

// Декларация функций
void initWiFiSettings();
void connectToWiFi(const char* ssid, const char* password);
void startAccessPoint();
void restartDevice();
void updateDNS(void);
#endif // WIFI_MANAGER_H
