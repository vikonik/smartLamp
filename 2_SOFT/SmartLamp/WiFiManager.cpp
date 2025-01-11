#include "WiFiManager.h" // Подключаем заголовочный файл
#include "config.h"
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include "mqtt.h"
//extern MqttSettings_t mqttSettings;


// Имя устройства в сети
const char* deviceName = "mydevice";
WiFiSettings_t wifiSettings;

WiFiSettings_t wifiSettingsDefault = {
    123,
    "SSID_AP",           // SSID
    "00000000",       // Пароль
    "Vikonik",           // SSID
    "88115221421",       // Пароль

    false,                // Использовать динамический IP
    "192.168.0.123",      // Статический IP
    "192.168.0.1",        // Шлюз
    "255.255.255.0",      // Маска подсети

    false,                // Использовать динамический IP
    "192.168.4.1",      // Статический IP
    "192.168.4.1",        // Шлюз
    "255.255.255.0",      // Маска подсети

    "8.8.8.8",            // Основной DNS
    "8.8.4.4",             // Дополнительный DNS

    "deviceName",
    "hostName"
};



/*****************************/
// Шаблон для вывода значений структуры
template <typename T>
void printStruct(const T& data) {
    Serial.println("Structure Content:");

    // Используем специальный блок кода для каждой структуры с помощью макросов
    printStructFields(data);
}

// Макрос для генерации функции вывода полей структуры
#define PRINT_STRUCT_FIELD(field) \
    Serial.print(#field ": ");   \
    Serial.println(data.field);

// Функция для вывода всех полей структуры
template <typename T>
void printStructFields(const T& data) {//Такую же структуру нужно написать для вывода настроек MQTT
    // Список полей структуры необходимо добавлять вручную
    PRINT_STRUCT_FIELD(isFerstStart);
    PRINT_STRUCT_FIELD(ssidAP);
    PRINT_STRUCT_FIELD(passwordAP);
    PRINT_STRUCT_FIELD(ssidClient);
    PRINT_STRUCT_FIELD(passwordClient);
    PRINT_STRUCT_FIELD(useStaticIpClient);
    PRINT_STRUCT_FIELD(staticIPClient);
    PRINT_STRUCT_FIELD(staticGatewayClient);
    PRINT_STRUCT_FIELD(staticSubnetClient);
    PRINT_STRUCT_FIELD(useStaticIpAP);
    PRINT_STRUCT_FIELD(staticIPHost);
    PRINT_STRUCT_FIELD(staticGatewayHost);
    PRINT_STRUCT_FIELD(staticSubnetHost);
    PRINT_STRUCT_FIELD(dns1);
    PRINT_STRUCT_FIELD(dns2);
    PRINT_STRUCT_FIELD(deviceName);
    PRINT_STRUCT_FIELD(hostName);
}

template <typename T>
void printStructMqttSettings(const T& data) {//Такую же структуру нужно написать для вывода настроек MQTT
    // Список полей структуры необходимо добавлять вручную
    PRINT_STRUCT_FIELD(isFerstStart);
    PRINT_STRUCT_FIELD(server);
    PRINT_STRUCT_FIELD(port);
    PRINT_STRUCT_FIELD(username);
    PRINT_STRUCT_FIELD(password);
    PRINT_STRUCT_FIELD(clientId);
    PRINT_STRUCT_FIELD(topicSubscribe);
    PRINT_STRUCT_FIELD(topicPublish);
    PRINT_STRUCT_FIELD(keepAlive);
    PRINT_STRUCT_FIELD(qos);
    PRINT_STRUCT_FIELD(retain);
    PRINT_STRUCT_FIELD(cleanSession);
    PRINT_STRUCT_FIELD(willTopic);
    PRINT_STRUCT_FIELD(willPayload);
    PRINT_STRUCT_FIELD(willQos);
    PRINT_STRUCT_FIELD(willRetain);
}
/****************************/
// Инициализация структуры

void initWiFiSettings() {

  // loadSettings(wifiSettings, WiFi_STRUCT_ADDR);
  //   printStruct(wifiSettings);
  // if(wifiSettings.isFerstStart != wifiSettingsDefault.isFerstStart){
  //   Serial.println("WiFi_STRUCT_ADDR: " + String(WiFi_STRUCT_ADDR));
  //   printStruct(wifiSettingsDefault);
  //   saveSettings(wifiSettingsDefault,WiFi_STRUCT_ADDR);  
  // }
  // loadSettings(wifiSettings, WiFi_STRUCT_ADDR);

  printSettingToUART();
}

//Выводим все настройки в UART
void printSettingToUART(void){
  Serial.println("WiFi Settings:");
  printStruct(wifiSettings);
  Serial.println("MQTT settings:");
  printStructMqttSettings(mqttSettings);
  Serial.print("InputPassword:");
  Serial.println(inputPassword.password);
  Serial.print("InputWithout Password:");
  Serial.println(inputPassword.noPasswordChecked);  
}
/*
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
void connectToWiFi() {
  initWiFiSettings();

  WiFi.mode(WIFI_STA); // Режим клиента
  Serial.println("Режим клиента");
Serial.println("Client SSID: " + String(wifiSettings.ssidClient));
Serial.println("Client Password: " + String(wifiSettings.passwordClient));
  WiFi.begin(wifiSettings.ssidClient, wifiSettings.passwordClient);

  Serial.print("Connecting to Wi-Fi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Пытаемся подключиться 20 раз
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
    /*
  if (MDNS.begin(deviceName)) {
    Serial.println("mDNS успешно запущен.");
    Serial.print("Доступно по адресу: ");
    Serial.print(deviceName);
    Serial.println(".local");
  } else {
    Serial.println("Ошибка запуска mDNS.");
  }
*/
   
}

// Функция для создания точки доступа
void startAccessPoint() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(wifiSettings.ssidAP, wifiSettings.passwordAP); // Создаем точку доступа с паролем

  Serial.println("Access Point started.");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());

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
    // Проверка и установка флага использования статического IP для клиента
    if (request->hasParam("useStaticIpClient", true)) {
        wifiSettings.useStaticIpClient = request->getParam("useStaticIpClient", true)->value() == "on";
    } else {
        wifiSettings.useStaticIpClient = false;
    }

    // Проверка и установка IP-адреса для клиента
    if (request->hasParam("clientIP", true)) {
        String clientIpParam = request->getParam("clientIP", true)->value();
        strncpy(wifiSettings.staticIPClient, clientIpParam.c_str(), sizeof(wifiSettings.staticIPClient) - 1);
        wifiSettings.staticIPClient[sizeof(wifiSettings.staticIPClient) - 1] = '\0';
    }

    // Проверка и установка SSID и пароля для клиента
    if (request->hasParam("wifiClientSSID", true)) {
        String ssidParam = request->getParam("wifiClientSSID", true)->value();
        strncpy(wifiSettings.ssidClient, ssidParam.c_str(), sizeof(wifiSettings.ssidClient) - 1);
        wifiSettings.ssidClient[sizeof(wifiSettings.ssidClient) - 1] = '\0';
    }

    if (request->hasParam("wifiClientPassword", true)) {
        String passwordParam = request->getParam("wifiClientPassword", true)->value();
        strncpy(wifiSettings.passwordClient, passwordParam.c_str(), sizeof(wifiSettings.passwordClient) - 1);
        wifiSettings.passwordClient[sizeof(wifiSettings.passwordClient) - 1] = '\0';
    }

    // Проверка и установка флага использования статического IP для точки доступа
    if (request->hasParam("useStaticIpServer", true)) {
        wifiSettings.useStaticIpAP = request->getParam("useStaticIpServer", true)->value() == "on";
    } else {
        wifiSettings.useStaticIpAP = false;
    }

    // Проверка и установка IP-адреса для точки доступа
    if (request->hasParam("apIP", true)) {
        String apIpParam = request->getParam("apIP", true)->value();
        strncpy(wifiSettings.staticIPHost, apIpParam.c_str(), sizeof(wifiSettings.staticIPHost) - 1);
        wifiSettings.staticIPHost[sizeof(wifiSettings.staticIPHost) - 1] = '\0';
    }

    // Проверка и установка SSID и пароля для точки доступа
    if (request->hasParam("wifiApSSID", true)) {
        String ssidParam = request->getParam("wifiApSSID", true)->value();
        strncpy(wifiSettings.ssidAP, ssidParam.c_str(), sizeof(wifiSettings.ssidAP) - 1);
        wifiSettings.ssidAP[sizeof(wifiSettings.ssidAP) - 1] = '\0';
    }

    if (request->hasParam("wifiApPassword", true)) {
        String passwordParam = request->getParam("wifiApPassword", true)->value();
        strncpy(wifiSettings.passwordAP, passwordParam.c_str(), sizeof(wifiSettings.passwordAP) - 1);
        wifiSettings.passwordAP[sizeof(wifiSettings.passwordAP) - 1] = '\0';
    }

    // Проверка и установка имени устройства
    if (request->hasParam("deviceName", true)) {
        String deviceNameParam = request->getParam("deviceName", true)->value();
        strncpy(wifiSettings.deviceName, deviceNameParam.c_str(), sizeof(wifiSettings.deviceName) - 1);
        wifiSettings.deviceName[sizeof(wifiSettings.deviceName) - 1] = '\0';
    }

    // Проверка и установка имени хоста
    if (request->hasParam("hostName", true)) {
        String hostNameParam = request->getParam("hostName", true)->value();
        strncpy(wifiSettings.hostName, hostNameParam.c_str(), sizeof(wifiSettings.hostName) - 1);
        wifiSettings.hostName[sizeof(wifiSettings.hostName) - 1] = '\0';
    }

    // Сохранение обновленных настроек в память EEPROM
    saveSettings(wifiSettings, "/wifiSettings.dat");

    // Перенаправление пользователя на страницу с настройками после сохранения
    request->redirect("/settings");
}
