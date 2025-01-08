#include "WebServer.h"
#include "passwordPage.h"
#include "wrongPasswordPage.h"
#include "mainPage.h"
#include "settingPage.h"
#include "mqtt.h"
#include "WiFiManager.h"
#include "config.h"
// Пароль для доступа
const char* passwordCorrect = "Humster";  
uint8_t isPaswordGood = 0;
String enteredPassword = "";


// Переменная состояния нагрузки (включена/выключена)
bool loadOn = false;

void controlLoad(bool state);

AsyncWebServer asyncServer(80); // Объявление объекта
String mqttServer = "MyServer.com";
void handleWebRequests() {
/*  
  // Обработка GET запроса для главной страницы
  asyncServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", htmlPasswordPage); // Отправка страницы из памяти
  });

  // Обработка POST запроса для ввода пароля
  asyncServer.on("/setPassword", HTTP_POST, [](AsyncWebServerRequest *request){
    String passwordReceived = "";
    
    // Считываем параметры формы
    if (request->hasParam("password", true)) {
      passwordReceived = request->getParam("password", true)->value();
    }

    // Проверка пароля
    if (passwordReceived == passwordCorrect) {
      enteredPassword = passwordReceived;
      request->send(200, "text/html", "<h1>Password Correct</h1><p>You have successfully entered the correct password.</p>");
    } else {
      request->send(200, "text/html", "<h1>Incorrect Password</h1><p>Please try again.</p>");
    }
  });
*/



//////////
  // Обработка GET запроса для главной страницы
  asyncServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Проверяем, введен ли правильный пароль
    if (enteredPassword == passwordCorrect) {
      request->send(200, "text/html", htmlMainPage); // Отправляем главную страницу
    } else {
      request->send(200, "text/html", htmlPasswordPage); // Если пароль неправильный, отправляем страницу пароля
    }
  });

  // Обработка POST запроса для ввода пароля
  asyncServer.on("/setPassword", HTTP_POST, [](AsyncWebServerRequest *request) {
    String passwordReceived = "";
    bool noPasswordChecked = false;
    //Сначала проверем вход без пароля
    if (request->hasParam("noPassword", true)) {
      noPasswordChecked = true; // Если чекбокс отмечен, параметр передается
      isPaswordGood = 1;
      request->send(200, "text/html", htmlMainPage); // Отправляем главную страницу
      return;
    }

    if (request->hasParam("password", true)) {
      passwordReceived = request->getParam("password", true)->value();
    }

    if (passwordReceived == passwordCorrect) {
      enteredPassword = passwordReceived;
      isPaswordGood = 1;
      request->send(200, "text/html", htmlMainPage); // Отправляем главную страницу
      //request->send(200, "text/html", "<h1>Password Correct</h1><p>You have successfully entered the correct password.</p>");
    } else {
      request->send(200, "text/html", htmlWrongPasswordPage);
    }
  });

  // Обработка запроса на переключение состояния нагрузки
  asyncServer.on("/toggleLoad", HTTP_GET, [](AsyncWebServerRequest *request) {
    if(!isPaswordGood){
      request->redirect("/");
      return;
    }
      

    if (request->hasParam("state")) {
      String state = request->getParam("state")->value();
      if (state == "on") {
        controlLoad(true);
      } else {
        controlLoad(false);
      }
      request->send(200, "text/plain", "OK");
    } else {
      request->send(400, "text/plain", "Bad Request");
    }
  });




  // Отправляем страницу настроек
  // Данные подставляются "на лету"
  asyncServer.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Изменить Настройки");
    if(!isPaswordGood){
      request->redirect("/");
      return;
    }
      

//Здесь заполняем поля страницы значениями 
request->send_P(200, "text/html", htmlSettingPage, [](const String &var) -> String {
    // MQTT settings placeholders
    if (var == "PLACEHOLDER_MQTT_SERVER") {
        return mqttSettings.server;
    } 
    else if (var == "PLACEHOLDER_MQTT_PORT") {
        return String(mqttSettings.port);
    } else if (var == "PLACEHOLDER_USER_NAME") {
        return mqttSettings.username;
    } else if (var == "PLACEHOLDER_MQTT_PASSWORD") {
        return mqttSettings.password;
    } else if (var == "PLACEHOLDER_CLIENT_ID") {
        return mqttSettings.clientId;
    } else if (var == "PLACEHOLDER_MQTT_SUBSCRIBE_TOPIC") {
        return mqttSettings.topicSubscribe;
    } else if (var == "PLACEHOLDER_MQTT_PUBLISH_TOPIC") {
        return mqttSettings.topicPublish;
    } else if (var == "PLACEHOLDER_MQTT_KEEP_ALIVE") {
        return String(mqttSettings.keepAlive);
    } else if (var == "PLACEHOLDER_MQTT_QOS") {
        String qosValue = String(mqttSettings.qos);
        if (qosValue == "0") {
            return "<option value=\"0\" selected>0 - Максимум один раз</option>"
                   "<option value=\"1\">1 - Как минимум один раз</option>"
                   "<option value=\"2\">2 - Точно один раз</option>";
        } else if (qosValue == "1") {
            return "<option value=\"0\">0 - Максимум один раз</option>"
                   "<option value=\"1\" selected>1 - Как минимум один раз</option>"
                   "<option value=\"2\">2 - Точно один раз</option>";
        } else if (qosValue == "2") {
            return "<option value=\"0\">0 - Максимум один раз</option>"
                   "<option value=\"1\">1 - Как минимум один раз</option>"
                   "<option value=\"2\" selected>2 - Точно один раз</option>";
        }
        return "<option value=\"0\">0 - Максимум один раз</option>"
               "<option value=\"1\">1 - Как минимум один раз</option>"
               "<option value=\"2\">2 - Точно один раз</option>";
    } else if (var == "PLACEHOLDER_MQTT_RETAIN") {
        return mqttSettings.retain ? "<option value=\"true\" selected>Включено</option>"
                                    "<option value=\"false\">Выключено</option>"
                                  : "<option value=\"true\">Включено</option>"
                                    "<option value=\"false\" selected>Выключено</option>";
    } else if (var == "PLACEHOLDER_MQTT_CLEAN_SESSION") {
        return mqttSettings.cleanSession ? "<option value=\"true\" selected>Да</option>"
                                          "<option value=\"false\">Нет</option>"
                                        : "<option value=\"true\">Да</option>"
                                          "<option value=\"false\" selected>Нет</option>";
    }

    // WiFi settings placeholders
    else if (var == "PLACEHOLDER_WIFI_USE_STATIC_IP_CLIENT") {
        return wifiSettings.useStaticIpClient ? "checked" : "";
    } else if (var == "PLACEHOLDER_WIFI_CLIENT_IP") {
        return wifiSettings.staticIPClient;
    } else if (var == "PLACEHOLDER_WIFI_SSID_CLIENT") {
        return wifiSettings.ssidClient;
    } else if (var == "PLACEHOLDER_WIFI_PASSWORD_CLIENT") {
        return wifiSettings.passwordClient;
    } else if (var == "PLACEHOLDER_WIFI_USE_STATIC_IP_SERVER") {
        return wifiSettings.useStaticIpAP ? "checked" : "";
    } else if (var == "PLACEHOLDER_WIFI_AP_IP") {
        return wifiSettings.staticIPHost;
    } else if (var == "PLACEHOLDER_WIFI_SSID_AP") {
        return wifiSettings.ssidAP;
    } else if (var == "PLACEHOLDER_WIFI_PASSWORD_AP") {
        return wifiSettings.passwordAP;
    } else if (var == "PLACEHOLDER_DEVICE_NAME") {
        return wifiSettings.deviceName;
    } else if (var == "PLACEHOLDER_HOST_NAME") {
        return wifiSettings.hostName;
    }

    return String();
});
 });

//Читаем настройкиб Обработка полученного ответа
asyncServer.on("/saveMQTTSettings", HTTP_POST,handleSaveMqttSettings);
asyncServer.on("/saveNetworkSettings", HTTP_POST,handleSaveNetwotkSettings);

  // Обработка запроса на изменение пароля
  asyncServer.on("/changePassword", HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.println("Изменить пароль");
    //Здесь написать код для изменения пароля
    //...
    request->redirect("/settings");

return;
  });

  // Обработка запроса на возврат к заводским установкам
  asyncServer.on("/returnNetworkSettingsDefault", HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.println("Возврат к заводским настройкам");
    //Здесь написать код для возврата к заводским настройкам
    //...
    request->redirect("/settings");

return;
  });

  // Запуск сервера
  asyncServer.begin();
}

/**/
// Функция управления нагрузкой
void controlLoad(bool state) {
  loadOn = state;
  // Здесь можно добавить код для управления физической нагрузкой, например, включение/выключение реле
  if (loadOn) {
    Serial.println("Нагрузка включена");
    digitalWrite(16, LOW);

    // Включение нагрузки
  } else {
    Serial.println("Нагрузка выключена");
    digitalWrite(16, HIGH);
    // Выключение нагрузки
  }
}


  


