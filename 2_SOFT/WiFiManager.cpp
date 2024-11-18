#include "WiFiManager.h" // Подключаем заголовочный файл
#include "config.h"
// Функция подключения к Wi-Fi
void connectToWiFi(const char* ssid, const char* password) {
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
}

// Функция для создания точки доступа
void startAccessPoint() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(mySsid, myPassword); // Создаем точку доступа с паролем

  Serial.println("Access Point started.");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());
}

// Функция перезагрузки устройства
void restartDevice() {
  Serial.println("Restarting device...");
  ESP.restart();
}
