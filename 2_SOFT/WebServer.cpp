#include "WebServer.h"
#include "passwordPage.h"
#include "mainPage.h"

// Пароль для доступа
const char* passwordCorrect = "admin123";  
String enteredPassword = "";


// Переменная состояния нагрузки (включена/выключена)
bool loadOn = false;

void controlLoad(bool state);

AsyncWebServer asyncServer(80); // Объявление объекта

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
    
    if (request->hasParam("password", true)) {
      passwordReceived = request->getParam("password", true)->value();
    }

    if (passwordReceived == passwordCorrect) {
      enteredPassword = passwordReceived;
      request->send(200, "text/html", htmlMainPage); // Отправляем главную страницу
      //request->send(200, "text/html", "<h1>Password Correct</h1><p>You have successfully entered the correct password.</p>");
    } else {
      request->send(200, "text/html", "<h1>Incorrect Password</h1><p>Please try again.</p>");
    }
  });

  // Обработка запроса на переключение состояния нагрузки
  asyncServer.on("/toggleLoad", HTTP_GET, [](AsyncWebServerRequest *request) {
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

  // Страница настроек
  asyncServer.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", "<h1>Страница настроек</h1>");
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
    // Включение нагрузки
  } else {
    Serial.println("Нагрузка выключена");
    // Выключение нагрузки
  }
}


