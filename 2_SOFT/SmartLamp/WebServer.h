#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

// Настройка пароля
extern const char* passwordCorrect; 
extern String enteredPassword;



// Прототипы функций
void handleWebRequests();

#endif
