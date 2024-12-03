#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h> // Подключение библиотеки для работы с Wi-Fi
#include <ESPAsyncWebServer.h>

typedef struct {
    uint8_t isFerstStart;    //Маркер
    char ssidAP[32];           // Название сети Wi-Fi (SSID) при работе в режиме точки доступа
    char passwordAP[64];       // Пароль Wi-Fi при работе в режиме точки доступа
    char ssidClient[32];           // Название сети Wi-Fi (SSID) при работе в режиме клиента
    char passwordClient[64];       // Пароль Wi-Fi при работе в режиме клиента

    bool useStaticIpClient ;        // Флаг использования статического IP (true - статический, false - динамический)
    char staticIPClient[16];       // Статический IP-адрес (например, "192.168.1.100")
    char staticGatewayClient[16];        // Адрес шлюза (например, "192.168.1.1")
    char staticSubnetClient[16];         // Маска подсети (например, "255.255.255.0")
    bool useStaticIpAP ;        // Флаг использования статического IP (true - статический, false - динамический)
    char staticIPHost[16];       // Статический IP-адрес (например, "192.168.1.100")
    char staticGatewayHost[16];        // Адрес шлюза (например, "192.168.1.1")
    char staticSubnetHost[16];         // Маска подсети (например, "255.255.255.0")

    char dns1[16];           // Основной DNS-сервер (например, "8.8.8.8")
    char dns2[16];           // Дополнительный DNS-сервер (например, "8.8.4.4")
	char deviceName[50];
    char hostName[50];        // Имя хоста (hostname) устройства
}WiFiSettings_t;

extern WiFiSettings_t wifiSettings;

// Декларация функций
void initWiFiSettings();
void handleSaveNetwotkSettings(AsyncWebServerRequest *request);
void connectToWiFi();
void startAccessPoint();
void restartDevice();
void updateDNS(void);
#endif // WIFI_MANAGER_H
