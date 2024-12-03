#include "WiFiManager.h" // Подключаем заголовочный файл
#include "config.h"
#include <ESP8266mDNS.h>


// Имя устройства в сети
const char* deviceName = "mydevice";
/*
WiFiSettings_t WiFiSettingsDefault = {
    "YourSSID",           // SSID
    "YourPassword",       // Пароль
    false,                // Использовать динамический IP
    "192.168.1.100",      // Статический IP
    "192.168.1.1",        // Шлюз
    "255.255.255.0",      // Маска подсети
    "8.8.8.8",            // Основной DNS
    "8.8.4.4"             // Дополнительный DNS
};
// Инициализация структуры

void initWiFiSettings() {
    strncpy(wifiSettings.ssid, "YourSSID", sizeof(wifiSettings.ssid) - 1);
    strncpy(wifiSettings.password, "YourPassword", sizeof(wifiSettings.password) - 1);
    wifiSettings.useStaticIP = false;
    strncpy(wifiSettings.staticIP, "192.168.1.100", sizeof(wifiSettings.staticIP) - 1);
    strncpy(wifiSettings.gateway, "192.168.1.1", sizeof(wifiSettings.gateway) - 1);
    strncpy(wifiSettings.subnet, "255.255.255.0", sizeof(wifiSettings.subnet) - 1);
    strncpy(wifiSettings.dns1, "8.8.8.8", sizeof(wifiSettings.dns1) - 1);
    strncpy(wifiSettings.dns2, "8.8.4.4", sizeof(wifiSettings.dns2) - 1);
    strncpy(wifiSettings.hostname, "SmartDevice", sizeof(wifiSettings.hostname) - 1);
}

 if (settings.useStaticIP) {
        IPAddress ip, gw, subnet, dns1, dns2;
        ip.fromString(settings.staticIP);
        gw.fromString(settings.gateway);
        subnet.fromString(settings.subnet);
        dns1.fromString(settings.dns1);
        dns2.fromString(settings.dns2);
        
        WiFi.config(ip, gw, subnet, dns1, dns2);
    } else {
        WiFi.config(0U, 0U, 0U); // DHCP
    }
*/
// Функция подключения к Wi-Fi
void connectToWiFi(const char* ssid, const char* password) {
//  initWiFiSettings();

  WiFi.mode(WIFI_STA); // Режим клиента
  Serial.println("Режим клиента");
  Serial.println(ssid);
  Serial.println(password);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 200) { // Пытаемся подключиться 20 раз
    delay(500);
    Serial.print(".");
    attempts++;
  }



  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to Wi-Fi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect. Starting Access Point...");
    startAccessPoint();
  }

    // Запуск mDNS
  if (MDNS.begin(deviceName)) {
    Serial.println("mDNS успешно запущен.");
    Serial.print("Доступно по адресу: ");
    Serial.print(deviceName);
    Serial.println(".local");
  } else {
    Serial.println("Ошибка запуска mDNS.");
  }
}

// Функция для создания точки доступа
void startAccessPoint() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(mySsid, myPassword); // Создаем точку доступа с паролем

  Serial.println("Access Point started.");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

      // Запуск mDNS
  if (MDNS.begin(deviceName)) {
    Serial.println("mDNS успешно запущен.");
    Serial.print("Доступно по адресу: ");
    Serial.print(deviceName);
    Serial.println(".local");
  } else {
    Serial.println("Ошибка запуска mDNS.");
  }
}

// Функция перезагрузки устройства
void restartDevice() {
  Serial.println("Restarting device...");
  ESP.restart();
}

/**/
void updateDNS(void){
  MDNS.update();
}

/******* Обработка данных со страницы настройки ************************/
void handleSaveNetwotkSettings(AsyncWebServerRequest *request) {
    if (request->hasParam("useStaticIpClient", true)) {
        wifiSettings.useStaticIpClient = true;
    } else {
        wifiSettings.useStaticIpClient = false;
    }

    if (request->hasParam("clientIP", true)) {
        String clientIpParam = request->getParam("clientIP", true)->value();
        strncpy(wifiSettings.clientIP, clientIpParam.c_str(), sizeof(wifiSettings.clientIP) - 1);
        wifiSettings.clientIP[sizeof(wifiSettings.clientIP) - 1] = '\0';
    }

    if (request->hasParam("useStaticIpServer", true)) {
        wifiSettings.useStaticIpServer = true;
    } else {
        wifiSettings.useStaticIpServer = false;
    }

    if (request->hasParam("apIP", true)) {
        String apIpParam = request->getParam("apIP", true)->value();
        strncpy(wifiSettings.apIP, apIpParam.c_str(), sizeof(wifiSettings.apIP) - 1);
        wifiSettings.apIP[sizeof(wifiSettings.apIP) - 1] = '\0';
    }

    if (request->hasParam("deviceName", true)) {
        String deviceNameParam = request->getParam("deviceName", true)->value();
        strncpy(wifiSettings.deviceName, deviceNameParam.c_str(), sizeof(wifiSettings.deviceName) - 1);
        wifiSettings.deviceName[sizeof(wifiSettings.deviceName) - 1] = '\0';
    }

    if (request->hasParam("hostName", true)) {
        String hostNameParam = request->getParam("hostName", true)->value();
        strncpy(wifiSettings.hostName, hostNameParam.c_str(), sizeof(wifiSettings.hostName) - 1);
        wifiSettings.hostName[sizeof(wifiSettings.hostName) - 1] = '\0';
    }

   

    saveMqttSettings(mqttSettings);
    request->redirect("/settings");// Перенаправить пользователя на страницу с настройками после сохранения
}