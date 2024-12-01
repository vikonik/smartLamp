#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h> // Подключение библиотеки для работы с Wi-Fi

// Декларация функций
void connectToWiFi(const char* ssid, const char* password);
void startAccessPoint();
void restartDevice();

#endif // WIFI_MANAGER_H
